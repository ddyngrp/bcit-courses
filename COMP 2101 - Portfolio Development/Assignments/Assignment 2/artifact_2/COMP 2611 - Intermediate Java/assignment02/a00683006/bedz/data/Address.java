/**
 * Project: assignment02
 * File: Address.java
 * Date: 9-Oct-07
 * Time: 1:55:15 AM
 */
package a00683006.bedz.data;

/**
 * Holds address information.
 * @author Steffen L. Norgren, A00683006
 * 
 */
public class Address {
	
	private String street;
	private String city;
	private Province province;
	private String postalCode;
	private String country;
	
	/**
	 * Default constructor.
	 */
	public Address() {
	}
	
	/**
	 * Creates an address using the following parameters.
	 * @param street
	 * @param city
	 * @param province
	 * @param postalCode
	 * @param country
	 */
	public Address(String street, String city, Province province, String postalCode,
			String country) {
		setStreet(street);
		setCity(city);
		setProvince(province);
		setPostalCode(postalCode);
		setCountry(country);
	}

	/**
	 * @return the street
	 */
	public String getStreet() {
		return street;
	}

	/**
	 * @param street the street to set
	 */
	public void setStreet(String street) {
		this.street = street;
	}

	/**
	 * @return the city
	 */
	public String getCity() {
		return city;
	}

	/**
	 * @param city the city to set
	 */
	public void setCity(String city) {
		this.city = city;
	}

	/**
	 * @return the province
	 */
	public Province getProvince() {
		return province;
	}

	/**
	 * @param province the province to set
	 */
	public void setProvince(Province province) {
		this.province = province;
	}

	/**
	 * @return the postalCode
	 */
	public String getPostalCode() {
		return postalCode;
	}

	/**
	 * @param postalCode the postalCode to set
	 */
	public void setPostalCode(String postalCode) {
		this.postalCode = postalCode;
	}

	/**
	 * @return the country
	 */
	public String getCountry() {
		return country;
	}

	/**
	 * @param country the country to set
	 */
	public void setCountry(String country) {
		this.country = country;
	}

	/**
	 * Constructs a <code>String</code> with all attributes
	 * in name = value format.
	 *
	 * @return a <code>String</code> representation 
	 * of this object.
	 */
	public String toString()
	{
	    final String TAB = ", ";
	    
	    String retValue = "";
	    
	    retValue = "Address{"
	        + "street='" + this.street + "'" + TAB
	        + "city='" + this.city + "'" + TAB
	        + "province='" + this.province + "'" + TAB
	        + "postalCode='" + this.postalCode + "'" + TAB
	        + "country='" + this.country + "'"
	        + "}";

	    return retValue;
	}
}
