/**
 * Project: lab02
 * File: Address.java
 * Date: 24-Sep-07
 * Time: 12:51:30 AM
 */
package a00683006.data;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Address {

	private String street;
	private String city;
	private String province;
	private String postalCode;
	private String country;
	
	/**
	 * Default constructor. This does nothing!
	 */
	public Address() {
	}
	
	public Address(String[] ADDRESS_DATA) {
		this.street = ADDRESS_DATA[0];
		this.city = ADDRESS_DATA[1];
		this.province = ADDRESS_DATA[2];
		this.postalCode = ADDRESS_DATA[3];
		this.country = ADDRESS_DATA[4];
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
	public String getProvince() {
		return province;
	}

	/**
	 * @param province the province to set
	 */
	public void setProvince(String province) {
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
	    final String TAB = " ";
	    
	    String retValue = "";
	    
	    retValue = "Address ( "
	        + "street = " + this.street + TAB
	        + "city = " + this.city + TAB
	        + "province = " + this.province + TAB
	        + "postalCode = " + this.postalCode + TAB
	        + "country = " + this.country + TAB
	        + " )";
	
	    return retValue;
	}
}