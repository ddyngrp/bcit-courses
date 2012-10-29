using System;
using System.Collections;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

namespace ManagedOffice
{
	/// <summary>
	/// A class which provides events for a COM object
	/// </summary>
	/// <remarks>
	/// late-bound COM events
	/// </remarks>
	internal sealed class ComEventProvider : IDisposable
	{
		private IConnectionPointContainer _connectionPointContainer;
		private IConnectionPoint _connectionPoint;
		private ComEventSink _eventSink;
		private Type _eventSinkType;
		private Guid _connectionPointGuid;
		private Hashtable _eventKeys;
		private WeakReference _owner;
		
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="target">
		/// The target COM object
		/// </param>
		/// <param name="interceptType">
		/// The intercepted type.
		/// </param>
		/// <param name="owner">
		/// The owner <see cref="COMWrapper"/>
		/// </param>
		/// <exception cref="ArgumentNullException">
		/// <para><paramref name="target"/> is <see langword="null"/></para>
		/// <para>-or-</para>
		/// <para><paramref name="interceptType"/> is <see langword="null"/></para>
		/// </exception>
		/// <exception cref="NotImplementedException">
		/// <paramref name="interceptType"/> does not define the
		/// <see cref="ComEventsAttribute"/> attribute.
		/// </exception>
		public ComEventProvider(object target, Type interceptType, COMWrapper owner)
		{
			if (null == target) throw new ArgumentNullException("target");
			if (null == interceptType) throw new ArgumentNullException("interceptType");
			
			ComEventsAttribute value = ComEventsAttribute.GetAttribute(interceptType);
			if (null == value) throw new NotImplementedException("Event provider attribute not found.");
			
			_connectionPointContainer = (IConnectionPointContainer)target;
			_eventSinkType = value.EventSinkType;
			_connectionPointGuid = value.EventsGuid;
			
			if (null != owner) _owner = new WeakReference(owner);
		}
		
		/// <summary>
		/// Finalizer
		/// </summary>
		~ComEventProvider()
		{
			Debug.WriteLine("Finalize ComEventProvider");
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
		private void Dispose(bool disposing)
		{
			lock(this)
			{
				if (null != _eventSink)
				{
					_eventSink.Dispose();
					_eventSink = null;
				}
				
				if (null != _connectionPoint)
				{
					while( Marshal.ReleaseComObject(_connectionPoint) > 0 );
					_connectionPoint = null;
				}
				
				if (null != _connectionPointContainer)
				{
					while( Marshal.ReleaseComObject(_connectionPointContainer) > 0 );
					_connectionPointContainer = null;
				}
			}
		}
		
		/// <summary>
		/// Initialize the event sink.
		/// </summary>
		private void Initialize()
		{
			if (null == _connectionPointContainer)
				throw new ObjectDisposedException("ComEventProvider");
			
			IConnectionPoint connectionPoint;
			Guid pointGuid = _connectionPointGuid;
			_connectionPointContainer.FindConnectionPoint(ref pointGuid, out connectionPoint);
			_connectionPoint = connectionPoint;
			
			_eventSink = (ComEventSink)Activator.CreateInstance(_eventSinkType);
			_eventSink.Connect(_connectionPoint);
			_eventSink.Owner = _owner;
		}
		
		/// <summary>
		/// Returns the key for the specified event.
		/// </summary>
		/// <param name="eventName">
		/// The name of the event.
		/// </param>
		/// <returns>
		/// The event key.
		/// </returns>
		/// <remarks>
		/// The event sink class should have a static readonly object
		/// field called {EventName}Event, which is used as the
		/// key for the event. If it doesn't, a new object will be
		/// created and used as the key.
		/// </remarks>
		private object GetEventKey(string eventName)
		{
			if (null != _eventKeys && _eventKeys.ContainsKey(eventName))
				return _eventKeys[eventName];
			
			object key = null;
			FieldInfo field = _eventSinkType.GetField(eventName + "Event", 
				BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);
			
			if (null != field) key = field.GetValue(_eventSink);
			if (null == key) 
			{
				key = new object();
				_eventSink.AddUnmappedEventKey(eventName, key);
			}
			
			if (null == _eventKeys)
                _eventKeys = new Hashtable(
                    CaseInsensitiveHashCodeProvider.Default,
                    CaseInsensitiveComparer.Default);
			
			_eventKeys[eventName] = key;
			return key;
		}
		
		/// <summary>
		/// Adds an event handler.
		/// </summary>
		/// <param name="eventName">
		/// The name of the event.
		/// </param>
		/// <param name="value">
		/// The event handler delegate.
		/// </param>
		public void AddEventHandler(string eventName, Delegate value)
		{
			lock(this)
			{
				if (null == _eventSink) Initialize();
				_eventSink.AddEventHandler(GetEventKey(eventName), value);
			}
		}
		
		/// <summary>
		/// Removes an event handler.
		/// </summary>
		/// <param name="eventName">
		/// The name of the event.
		/// </param>
		/// <param name="value">
		/// The event handler delegate.
		/// </param>
		public void RemoveEventHandler(string eventName, Delegate value)
		{
			lock(this)
			{
				if (null == _eventSink) return;
				_eventSink.RemoveEventHandler(GetEventKey(eventName), value);
			}
		}
	}
}
