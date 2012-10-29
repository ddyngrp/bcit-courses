using System;

namespace ManagedOffice
{
	/// <summary>
	/// An attribute to specifiy the ProgID of the
	/// COM class to create. (As suggested by
	/// Kristen Wegner)
	/// </summary>
	[AttributeUsage(AttributeTargets.Interface, Inherited=false, AllowMultiple=false)]
	public sealed class ComProgIdAttribute : Attribute
	{
		private string _value;
		
		/// <summary>
		/// Extracts the attribute from the specified type.
		/// </summary>
		/// <param name="interfaceType">
		/// The interface type.
		/// </param>
		/// <returns>
		/// The <see cref="ComProgIdAttribute"/>.
		/// </returns>
		/// <exception cref="ArgumentNullException">
		/// <paramref name="interfaceType"/> is <see langword="null"/>.
		/// </exception>
		public static ComProgIdAttribute GetAttribute(Type interfaceType)
		{
			if (null == interfaceType) throw new ArgumentNullException("interfaceType");
			
			Type attributeType = typeof(ComProgIdAttribute);
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
			return (ComProgIdAttribute)attributes[0];
		}
		
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="value">
		/// The COM ProgID.
		/// </param>
		public ComProgIdAttribute(string value)
		{
			_value = value;
		}
		
		/// <summary>
		/// Returns the COM ProgID
		/// </summary>
		public string Value
		{
			get { return _value; }
		}
	}
}
