using System;
using System.Diagnostics;
using System.Runtime.Remoting.Proxies;
using System.Runtime.InteropServices;
using System.Runtime.Remoting.Messaging;
using System.Runtime.Remoting;
using System.Reflection;

namespace ManagedOffice
{
	/// <summary>
	/// Wraps a late-bound COM server.
	/// </summary>
	public sealed class COMWrapper : RealProxy, IDisposable
	{
		#region Private Data

		/// <summary>
		/// Holds reference to the actual COM object which is wrapped by this proxy
		/// </summary>
		private object _COMObject;
		
		/// <summary>
		/// Type of the COM object, set on constructor after getting the COM reference
		/// </summary>
		private Type _COMType;

		/// <summary>
		/// The type of which method calls are intercepted and executed on the COM object.
		/// </summary>
		private Type _InterceptType; 
		
		/// <summary>
		/// The class which provides events for this object
		/// </summary>
		private ComEventProvider _ComEventProvider;

		#endregion

		#region Construction
		
		/// <summary>
		/// Creates a COM object and returns the transparent proxy 
		/// which intercepts all calls to the object
		/// </summary>
		/// <param name="type">Interface which defines the method and properties to intercept</param>
		/// <returns>Transparent proxy to the real proxy for the object</returns>
		/// <remarks>
		/// The <paramref name="type"/> must be an interface decorated with
		/// the <see cref="ComProgIdAttribute"/> attribute.
		/// </remarks>
		public static object CreateInstance(Type type)
		{
			if (null == type) throw new ArgumentNullException("type");
			if (!type.IsInterface) throw new ArgumentException("The specified type must be an interface.", "type");
			
			ComProgIdAttribute progID = ComProgIdAttribute.GetAttribute(type);
			if (null == progID || null == progID.Value || 0 == progID.Value.Length)
				throw new ArgumentException("The specified type must define a ComProgId attribute.", "type");
			
			Type comType = Type.GetTypeFromProgID(progID.Value, true);
			object comObject = Activator.CreateInstance(comType);
			if (null == comObject)
			{
				throw new TypeLoadException(
					string.Format("Unable to create an instance of the specified COM server \"{0}\".",
					progID.Value));
			}
			
			COMWrapper wrapper = new COMWrapper(comObject, type);
			return wrapper.GetTransparentProxy();
		}
		
		/// <summary>
		/// Wrap an object and return the transparent proxy which intercepts all calls
		/// to the object
		/// </summary>
		/// <param name="comObject">An object to intercept</param>
		/// <param name="type">Interface which defines the method and properties to intercept</param>
		/// <returns>Transparent proxy to the real proxy for the object</returns>
		public static object Wrap(object comObject, Type type)
		{
			if (null == comObject) throw new ArgumentNullException("comObject");
			if (null == type) throw new ArgumentNullException("type");
			
			COMWrapper wrapper = new COMWrapper(comObject, type);
			return wrapper.GetTransparentProxy();
		}

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="comObject">
		/// The COM object to wrap.
		/// </param>
		/// <param name="type">
		/// The interface type to impersonate.
		/// </param>
		private COMWrapper(object comObject, Type type) : base( type )
		{
			this._COMObject = comObject;
			this._COMType = comObject.GetType();
			this._InterceptType = type;
		}

		#endregion
		
		#region Clean up
		
		/// <summary>
		/// If <see cref="Dispose"/> is not called, we need to make
		/// sure that the COM object is still cleaned up.
		/// </summary>
		~COMWrapper()
		{
			Debug.WriteLine("Finalize " + this._InterceptType.ToString());
			this.Dispose(false);
		}
		
		/// <summary>
		/// Cleans up the COM object.
		/// </summary>
		public void Dispose()
		{
			this.Dispose(true);
			GC.SuppressFinalize(this);
		}

		/// <summary>
		/// Release the COM reference
		/// </summary>
		/// <param name="disposing">
		/// <see langword="true"/> if this was called from the
		/// <see cref="IDisposable"/> interface.
		/// </param>
		private void Dispose(bool disposing)
		{
			if (disposing)
			{
				if (null != this._ComEventProvider)
				{
					this._ComEventProvider.Dispose();
					this._ComEventProvider = null;
				}
			}
			
			if (null != this._COMObject)
			{
				if(Marshal.IsComObject(this._COMObject))
					while( Marshal.ReleaseComObject(this._COMObject) > 0 );
				
				this._COMObject = null;
			}
		}
		
		#endregion
		
		#region Object methods
		
		/// <summary>
		/// Returns a string representing the wrapped object.
		/// </summary>
		/// <returns>
		/// The full name of the intercepted type.
		/// </returns>
		public override string ToString()
		{
			return this._InterceptType.FullName;
		}
		
		/// <summary>
		/// Returns the hash code of the wrapped object.
		/// </summary>
		/// <returns>
		/// The hash code of the wrapped object.
		/// </returns>
		public override int GetHashCode()
		{
			return this._COMObject.GetHashCode();
		}
		
		/// <summary>
		/// Compares this object to another.
		/// </summary>
		/// <param name="value">
		/// The value to compare to.
		/// </param>
		/// <returns>
		/// <see langword="true"/> if the objects are equal.
		/// </returns>
		public override bool Equals(object value)
		{
			if (null != value && RemotingServices.IsTransparentProxy(value))
			{
				COMWrapper wrapper = RemotingServices.GetRealProxy(value) as COMWrapper;
				if (null != wrapper) return this._COMObject == wrapper._COMObject;
			}
			
			return base.Equals(value);
		}
		
		/// <summary>
		/// Returns the base type for a reference type.
		/// </summary>
		/// <param name="byRefType">
		/// The reference type.
		/// </param>
		/// <returns>
		/// The base value type.
		/// </returns>
		/// <exception cref="ArgumentNullException">
		/// <paramref name="byRefType"/> is <see langword="null"/>.
		/// </exception>
		private static Type GetByValType(Type byRefType)
		{
			if (null == byRefType) throw new ArgumentNullException("byRefType");
			
			if (byRefType.IsByRef)
			{
				string name = byRefType.FullName;
				name = name.Substring(0, name.Length - 1);
				byRefType = byRefType.Assembly.GetType(name, true);
			}
			
			return byRefType;
		}
		
		#endregion

		#region Event Handling
		
		/// <summary>
		/// Attaches an event handler to the COM object.
		/// </summary>
		/// <param name="eventName">
		/// The name of the event.
		/// </param>
		/// <param name="handler">
		/// The event handler delegate.
		/// </param>
		/// <exception cref="ArgumentNullException">
		/// <para><paramref name="eventName"/> is <see langword="null"/></para>
		/// <para>-or-</para>
		/// <para><paramref name="handler"/> is <see langword="null"/></para>
		/// </exception>
		private void AttachEventHandler(string eventName, Delegate handler)
		{
			if (null == eventName || 0 == eventName.Length) throw new ArgumentNullException("eventName");
			if (null == handler) throw new ArgumentNullException("handler");
			
			lock(this)
			{
				if (null == _ComEventProvider) 
					_ComEventProvider = new ComEventProvider(_COMObject, _InterceptType, this);
				
				_ComEventProvider.AddEventHandler(eventName, handler);
			}
		}
		
		/// <summary>
		/// Removes an event handler from the COM object.
		/// </summary>
		/// <param name="eventName">
		/// The name of the event.
		/// </param>
		/// <param name="handler">
		/// The event handler delegate.
		/// </param>
		/// <exception cref="ArgumentNullException">
		/// <para><paramref name="eventName"/> is <see langword="null"/></para>
		/// <para>-or-</para>
		/// <para><paramref name="handler"/> is <see langword="null"/></para>
		/// </exception>
		private void RemoveEventHandler(string eventName, Delegate handler)
		{
			if (null == eventName || 0 == eventName.Length) throw new ArgumentNullException("eventName");
			if (null == handler) throw new ArgumentNullException("handler");
			
			lock(this)
			{
				if (null == _ComEventProvider) return;
				_ComEventProvider.RemoveEventHandler(eventName, handler);
			}
		}

		#endregion

		
		/// <summary>
		/// Intercept method calls 
		/// </summary>
		/// <param name="myMessage">
		/// Contains information about the method being called
		/// </param>
		/// <returns>
		/// A <see cref="ReturnMessage"/>.
		/// </returns>
		public override IMessage Invoke(IMessage myMessage)
		{
			IMethodCallMessage callMessage = myMessage as IMethodCallMessage;
			if (null == callMessage)
			{
				Debug.WriteLine("Message type not implemented: " + myMessage.GetType().ToString());
				return null;
			}
			
			MethodInfo method = callMessage.MethodBase as MethodInfo;
			if (null == method)
			{
				Debug.WriteLine("Unrecognized Invoke call: " + callMessage.MethodBase.ToString());
				return null;
			}
			
			object returnValue = null;
			object[] outArgs = null;
			int outArgsCount = 0;
			
			string methodName = method.Name;
			Type returnType = method.ReturnType;
			BindingFlags flags = BindingFlags.InvokeMethod;
			int argCount = callMessage.ArgCount;
			
			object invokeObject;
			Type invokeType;
			Type byValType;
			
			object[] args;
			object arg;
			COMWrapper[] originalArgs;
			COMWrapper wrapper;
			
			ParameterModifier[] argModifiers = null;
			ParameterInfo[] parameters = null;
			ParameterInfo parameter;
			
			if ("Dispose" == methodName && 0 == argCount && typeof(void) == returnType)
			{
				this.Dispose();
			}
			else if ("ToString" == methodName && 0 == argCount && typeof(string) == returnType)
			{
				returnValue = this.ToString();
			}
			else if ("GetType" == methodName && 0 == argCount && typeof(System.Type) == returnType)
			{
				returnValue = this._InterceptType;
			}
			else if ("GetHashCode" == methodName && 0 == argCount && typeof(int) == returnType)
			{
				returnValue = this.GetHashCode();
			}
			else if ("Equals" == methodName && 1 == argCount && typeof(bool) == returnType)
			{
				returnValue = this.Equals(callMessage.Args[0]);
			}
			else if (1 == argCount && typeof(void) == returnType
				&& (methodName.StartsWith("add_") || methodName.StartsWith("remove_")))
			{
				bool removeHandler = methodName.StartsWith("remove_");
				methodName = methodName.Substring(removeHandler ? 7 : 4);
				
				Delegate handler = callMessage.InArgs[0] as Delegate;
				if (null == handler) 
					return new ReturnMessage(new ArgumentNullException("handler"), callMessage);
				
				try
				{
					if (removeHandler)
						RemoveEventHandler(methodName, handler);
					else
						AttachEventHandler(methodName, handler);
				}
				catch(Exception ex)
				{
					return new ReturnMessage(ex, callMessage);
				}
				
			}
			else
			{
				invokeObject = this._COMObject;
				invokeType = this._COMType;
				
				if (methodName.StartsWith("get_"))
				{
					// Property Get
					methodName = methodName.Substring(4);
					flags = BindingFlags.GetProperty;
					args = callMessage.InArgs;
				}
				else if (methodName.StartsWith("set_"))
				{
					// Property Set
					methodName = methodName.Substring(4);
					flags = BindingFlags.SetProperty;
					args = callMessage.InArgs;
				}
				else
				{
					args = callMessage.Args;
					if (null != args && 0 != args.Length)
					{
						// Modifiers for ref / out parameters
						argModifiers = new ParameterModifier[1];
						argModifiers[0] = new ParameterModifier(args.Length);
						
						parameters = method.GetParameters();
						for(int i=0; i<parameters.Length; i++)
						{
							parameter = parameters[i];
							if (parameter.IsOut || parameter.ParameterType.IsByRef)
							{
								argModifiers[0][i] = true;
								outArgsCount++;
							}
						}
						
						if (0 == outArgsCount) argModifiers = null;
					}
				}
				
				// Un-wrap wrapped COM objects before passing to the method
				if (null == args || 0 == args.Length)
				{
					originalArgs = null;
				}
				else
				{
					originalArgs = new COMWrapper[args.Length];
					for(int i=0; i<args.Length; i++)
					{
						if (null != args[i] && RemotingServices.IsTransparentProxy(args[i]))
						{
							wrapper = RemotingServices.GetRealProxy(args[i]) as COMWrapper;
							if (null != wrapper)
							{
								originalArgs[i] = wrapper;
								args[i] = wrapper._COMObject;
							}
						}
						else if (0 != outArgsCount && argModifiers[0][i])
						{
							byValType = GetByValType(parameters[i].ParameterType);
							if (byValType.IsInterface)
							{
								// If we're passing a COM object by reference, and
								// the parameter is null, we need to pass a
								// DispatchWrapper to avoid a type mismatch exception.
								if (null == args[i]) args[i] = new DispatchWrapper(null);
							}
							else if (typeof(Decimal) == byValType)
							{
								// If we're passing a decimal value by reference,
								// we need to pass a CurrencyWrapper to avoid a 
								// type mismatch exception.
								// http://support.microsoft.com/?kbid=837378
								args[i] = new CurrencyWrapper(args[i]);
							}
						}
					}
				}
				
				try
				{
					returnValue = invokeType.InvokeMember(methodName, 
						flags, null, invokeObject, args, argModifiers, null, null);
				}
				catch(Exception ex)
				{
					return new ReturnMessage(ex, callMessage);
				}
				
				// Handle enum and interface return types
				if (null != returnValue)
				{
					if (returnType.IsInterface)
					{
						// Wrap the returned value in an intercepting COM wrapper
						if (Marshal.IsComObject(returnValue))
							returnValue = COMWrapper.Wrap(returnValue, returnType);
						
					}
					else if (returnType.IsEnum)
					{
						// Convert to proper Enum type
						returnValue = Enum.Parse(returnType, returnValue.ToString());
					}
				}
				
				// Handle out args
				if (0 != outArgsCount)
				{
					outArgs = new object[args.Length];
					for(int i=0; i<parameters.Length; i++)
					{
						if (!argModifiers[0][i]) continue;
						
						arg = args[i];
						if (null == arg) continue;
						
						parameter = parameters[i];
						wrapper = null;
						
						byValType = GetByValType(parameter.ParameterType);
						if (typeof(Decimal) == byValType)
						{
							if (arg is CurrencyWrapper) arg = ((CurrencyWrapper)arg).WrappedObject;
						}
						else if (byValType.IsEnum)
						{
							arg = Enum.Parse(byValType, arg.ToString());
						}
						else if (byValType.IsInterface)
						{
							if (Marshal.IsComObject(arg))
							{
								wrapper = originalArgs[i];
								if (null != wrapper && wrapper._COMObject != arg)
								{
									wrapper.Dispose();
									wrapper = null;
								}
								
								if (null == wrapper) wrapper = new COMWrapper(arg, byValType);
								arg = wrapper.GetTransparentProxy();
							}
						}
						
						outArgs[i] = arg;
					}
				}
			}
			
			return new ReturnMessage(returnValue, 
				outArgs, outArgsCount, 
				callMessage.LogicalCallContext, 
				callMessage);
		}
	}
}
