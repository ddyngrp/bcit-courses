using System;
using System.Collections;
using System.ComponentModel;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

namespace ManagedOffice
{
	/// <summary>
	/// A class which represents a COM event sink
	/// </summary>
	[ClassInterface(ClassInterfaceType.None)]
	public abstract class ComEventSink : IDisposable
	{
		private EventHandlerList _events;
		private int _connectionCookie;
		private IConnectionPoint _connectionPoint;
		private Hashtable _unmappedEventKeys;
		private WeakReference _owner;

		/// <summary>
		/// Constructor
		/// </summary>
		protected ComEventSink()
		{
		}
		
		/// <summary>
		/// Finalizer
		/// </summary>
		~ComEventSink()
		{
			Debug.WriteLine(string.Format("Finalize {0}", this.GetType()));
			Dispose(false);
		}
		
		/// <summary>
		/// Cleans up the COM object references.
		/// </summary>
		public void Dispose()
		{
			Dispose(true);
			GC.SuppressFinalize(this);
		}
		
		/// <summary>
		/// Cleans up the COM object references.
		/// </summary>
		/// <param name="disposing">
		/// <see langword="true"/> if this was called from the
		/// <see cref="IDisposable"/> interface.
		/// </param>
		protected virtual void Dispose(bool disposing)
		{
			if (disposing)
			{
				_owner = null;
				_unmappedEventKeys = null;
				
				if (null != _events)
				{
					_events.Dispose();
					_events = null;
				}
			}
			
			if (null != _connectionPoint)
			{
				if (0 != _connectionCookie)
				{
					_connectionPoint.Unadvise(_connectionCookie);
					_connectionCookie = 0;
				}
				
				while( Marshal.ReleaseComObject(_connectionPoint) > 0 );
				_connectionPoint = null;
			}
		}
		
		/// <summary>
		/// Returns a value indicating whether this
		/// event sink is connected to a COM object.
		/// </summary>
		public bool IsConnected
		{
			get { return 0 != _connectionCookie; }
		}
		
		/// <summary>
		/// Gets or sets the reference to the
		/// owner <see cref="COMWrapper"/>
		/// </summary>
		internal WeakReference Owner
		{
			get { return _owner; }
			set { _owner = value; }
		}
		
		/// <summary>
		/// Returns the sender object for events.
		/// </summary>
		protected object Sender
		{
			get
			{
				if (null == _owner || !_owner.IsAlive) return this;
				
				COMWrapper wrapper= _owner.Target as COMWrapper;
				if (null == wrapper) return (null == _owner.Target ? this : _owner.Target);
				
				return wrapper.GetTransparentProxy();
			}
		}
		
		/// <summary>
		/// Adds a handler to the specified event.
		/// </summary>
		/// <param name="key">
		/// The event key.
		/// </param>
		/// <param name="value">
		/// The event handler delegate.
		/// </param>
		/// <exception cref="ArgumentNullException">
		/// <para><paramref name="key"/> is <see langword="null"/></para>
		/// <para>-or-</para>
		/// <para><paramref name="value"/> is <see langword="null"/></para>
		/// </exception>
		internal void AddEventHandler(object key, Delegate value)
		{
			if (null == key) throw new ArgumentNullException("key");
			if (null == value) throw new ArgumentNullException("value");
			
			lock(this)
			{
				if (null == _events) _events = new EventHandlerList();
				_events.AddHandler(key, value);
			}
		}
		
		/// <summary>
		/// Removes a handler from the specified event.
		/// </summary>
		/// <param name="key">
		/// The event key.
		/// </param>
		/// <param name="value">
		/// The event handler delegate.
		/// </param>
		/// <exception cref="ArgumentNullException">
		/// <para><paramref name="key"/> is <see langword="null"/></para>
		/// <para>-or-</para>
		/// <para><paramref name="value"/> is <see langword="null"/></para>
		/// </exception>
		internal void RemoveEventHandler(object key, Delegate value)
		{
			if (null == key) throw new ArgumentNullException("key");
			if (null == value) throw new ArgumentNullException("value");
			
			lock(this)
			{
				if (null == _events) return;
				_events.RemoveHandler(key, value);
			}
		}
		
		/// <summary>
		/// Raises the specified event
		/// </summary>
		/// <param name="key">The event key</param>
		/// <param name="args">The event arguments</param>
		/// <exception cref="ArgumentNullException">
		/// <paramref name="key"/> is <see langword="null"/>.
		/// </exception>
		/// <remarks>
		/// If the event object is an <see cref="EventHandler"/>,
		/// and no arguments are specified, <see cref="Sender"/>
		/// and <see cref="EventArgs.Empty"/> will be passed.
		/// </remarks>
		protected void RaiseEvent(object key, params object[] args)
		{
			if (null == key) throw new ArgumentNullException("key");
			if (null == _events) return;
			
			if (key is string) key = GetUnmappedEventKey((string)key);
			Delegate d = _events[key];
			if (null == d) return;
			
			if (d is EventHandler && (null == args || 0 == args.Length))
				args = new object[] { this.Sender, EventArgs.Empty };
			
			d.DynamicInvoke(args);
		}
		
		/// <summary>
		/// Returns a key for an event with no corresponding
		/// static object variable.
		/// </summary>
		/// <param name="eventName">
		/// The name of the event.
		/// </param>
		/// <returns>
		/// The event key.
		/// </returns>
		private object GetUnmappedEventKey(string eventName)
		{
			if (null == _unmappedEventKeys || !_unmappedEventKeys.ContainsKey(eventName)) 
				return eventName;
			
			return _unmappedEventKeys[eventName];
		}
		
		/// <summary>
		/// Adds a key for an event with no corresponding
		/// static object variable.
		/// </summary>
		/// <param name="eventName">
		/// The name of the event.
		/// </param>
		/// <param name="key">
		/// The event key.
		/// </param>
		internal void AddUnmappedEventKey(string eventName, object key)
		{
            if (null == _unmappedEventKeys)
                _unmappedEventKeys = new Hashtable(
					CaseInsensitiveHashCodeProvider.Default,
					CaseInsensitiveComparer.Default);
			
			_unmappedEventKeys[eventName] = key;
			Debug.WriteLine(string.Format("Event {0} does not have a corresponding static field {0}Event.", eventName));
		}
		
		/// <summary>
		/// Connects this event sink to a COM object.
		/// </summary>
		/// <param name="connectionPoint">
		/// The connection point to connect to.
		/// </param>
		/// <exception cref="ArgumentNullException">
		/// <paramref name="connectionPoint"/> is <see langword="null"/>.
		/// </exception>
		internal void Connect(IConnectionPoint connectionPoint)
		{
			if (null == connectionPoint) throw new ArgumentNullException("connectionPoint");
			
			if (0 == _connectionCookie)
			{
				int connectionCookie;
				connectionPoint.Advise(this, out connectionCookie);
				_connectionCookie = connectionCookie;
				_connectionPoint = connectionPoint;
			}
		}
		
		/// <summary>
		/// Disconnects this event sink from a COM object.
		/// </summary>
		internal void Disconnect()
		{
			if (null != _connectionPoint)
			{
				if (0 != _connectionCookie)
				{
					_connectionPoint.Unadvise(_connectionCookie);
					_connectionCookie = 0;
				}
				
				while( Marshal.ReleaseComObject(_connectionPoint) > 0 );
				_connectionPoint = null;
			}
			
			_owner = null;
		}
	}
}
