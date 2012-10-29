using System;
using System.Runtime.InteropServices;

namespace ManagedOffice
{
	/// <summary>
	/// An attribute used to associate the COM event
	/// interfaces with the wrapped interface.
	/// </summary>
	[AttributeUsage(AttributeTargets.Interface, Inherited=false, AllowMultiple=false)]
	public sealed class ComEventsAttribute : Attribute
	{
		private Type _eventSinkType;
		private Guid _eventsGuid;
		
		/// <summary>
		/// Extracts the attribute from the specified type.
		/// </summary>
		/// <param name="interfaceType">
		/// The interface type.
		/// </param>
		/// <returns>
		/// The <see cref="ComEventsAttribute"/>.
		/// </returns>
		/// <exception cref="ArgumentNullException">
		/// <paramref name="interfaceType"/> is <see langword="null"/>.
		/// </exception>
		public static ComEventsAttribute GetAttribute(Type interfaceType)
		{
			if (null == interfaceType) throw new ArgumentNullException("interfaceType");
			
			Type attributeType = typeof(ComEventsAttribute);
			object[] attributes = interfaceType.GetCustomAttributes(attributeType, false);
			
			if (null == attributes || 0 == attributes.Length)
			{
				Type[] interfaces = interfaceType.GetInterfaces();
				for(int i=0; i<interfaces.Length; i++)
				{
					interfaceType = interfaces[i];
					attributes = interfaceType.GetCustomAttributes(attributeType, false);
					if (null != attributes && 0 != attributes.Length) break;
				}
			}
			
			if (null == attributes || 0 == attributes.Length) return null;
			return (ComEventsAttribute)attributes[0];
		}
		
		/// <summary>
		/// Extracts the <see cref="Guid"/> from an interface using
		/// the <see cref="GuidAttribute"/> attribute.
		/// </summary>
		/// <param name="interfaceType">
		/// The interface type.
		/// </param>
		/// <returns>
		/// The <see cref="Guid"/> attached to the interface.
		/// </returns>
		private static Guid GetGuid(Type interfaceType)
		{
			if (null == interfaceType || !interfaceType.IsInterface)
				return Guid.Empty;
			
			object[] attributes = interfaceType.GetCustomAttributes(typeof(GuidAttribute), false);
			if (null == attributes || 0 == attributes.Length) return Guid.Empty;
			
			GuidAttribute guid = (GuidAttribute)attributes[0];
			if (null == guid || null == guid.Value || 0 == guid.Value.Length) return Guid.Empty;
			
			try
			{
				return new Guid(guid.Value);
			}
			catch(FormatException)
			{
			}
			
			return Guid.Empty;
		}
		
		/// <summary>
		/// Extracts the <see cref="Guid"/> from a string.
		/// </summary>
		/// <param name="guid">
		/// The GUID or type name.
		/// </param>
		/// <returns>
		/// The <see cref="Guid"/> extracted from the string.
		/// </returns>
		private static Guid GetGuid(string guid)
		{
			if (null == guid || 0 == guid.Length) return Guid.Empty;
			
			try
			{
				return new Guid(guid);
			}
			catch(FormatException)
			{
			}
			
			Type interfaceType = Type.GetType(guid);
			if (null != interfaceType) return GetGuid(interfaceType);
			
			return Guid.Empty;
		}
		
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="eventSinkType">
		/// The type of the event sink class.
		/// </param>
		/// <param name="eventsGuid">
		/// The <see cref="Guid"/> of the events interface.
		/// </param>
		public ComEventsAttribute(Type eventSinkType, Guid eventsGuid)
		{
			_eventSinkType = eventSinkType;
			_eventsGuid = eventsGuid;
		}
		
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="eventSinkType">
		/// The type of the event sink class.
		/// </param>
		/// <param name="eventsGuid">
		/// The <see cref="Guid"/> of the events interface.
		/// </param>
		public ComEventsAttribute(Type eventSinkType, string eventsGuid)
		{
			_eventSinkType = eventSinkType;
			_eventsGuid = GetGuid(eventsGuid);
		}
		
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="eventSinkType">
		/// The type of the event sink class.
		/// </param>
		/// <param name="eventsGuid">
		/// The <see cref="Guid"/> of the events interface.
		/// </param>
		public ComEventsAttribute(string eventSinkType, Guid eventsGuid)
		{
			_eventSinkType = Type.GetType(eventSinkType);
			_eventsGuid = eventsGuid;
		}
		
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="eventSinkType">
		/// The type of the event sink class.
		/// </param>
		/// <param name="eventsGuid">
		/// The <see cref="Guid"/> of the events interface.
		/// </param>
		public ComEventsAttribute(string eventSinkType, string eventsGuid)
		{
			_eventSinkType = Type.GetType(eventSinkType);
			_eventsGuid = GetGuid(eventsGuid);
		}
		
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="eventSinkType">
		/// The type of the event sink class.
		/// </param>
		/// <param name="interfaceType">
		/// The interface for the events.
		/// </param>
		public ComEventsAttribute(Type eventSinkType, Type interfaceType)
		{
			_eventSinkType = eventSinkType;
			_eventsGuid = GetGuid(interfaceType);
		}
		
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="eventSinkType">
		/// The type of the event sink class.
		/// </param>
		/// <param name="interfaceType">
		/// The interface for the events.
		/// </param>
		public ComEventsAttribute(string eventSinkType, Type interfaceType)
		{
			_eventSinkType = Type.GetType(eventSinkType);
			_eventsGuid = GetGuid(interfaceType);
		}
		
		/// <summary>
		/// Returns the type of the event sink class.
		/// </summary>
		public Type EventSinkType
		{
			get { return _eventSinkType; }
		}
		
		/// <summary>
		/// Returns the <see cref="Guid"/> of the events interface.
		/// </summary>
		public Guid EventsGuid
		{
			get { return _eventsGuid; }
		}
	}
}
