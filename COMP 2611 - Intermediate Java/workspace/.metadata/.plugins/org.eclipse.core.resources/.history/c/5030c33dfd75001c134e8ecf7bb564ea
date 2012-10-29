package a00123456.data;

/**
 * User: Fred
 * Date: 15/09/2007
 * Time: 23:40:56
 */
public class Address {
	private String street;
	private String city;
	private String province;
	private String postalCode;
	private String country;

	public Address() {
	}

	/**
	 * @param street
	 * @param city
	 * @param province
	 * @param postalCode
	 * @param country
	 */
	public Address(String street, String city, String province, String postalCode, String country) {
		this.street = street;
		this.city = city;
		this.province = province;
		this.postalCode = postalCode;
		this.country = country;
	}
	
	public Address(String[] data) {
		this(data[0], data[1], data[2], data[3], data[4]);
	}

	public String getStreet() {
		return street;
	}

	public void setStreet(String street) {
		this.street = street;
	}

	public String getCity() {
		return city;
	}

	public void setCity(String city) {
		this.city = city;
	}

	public String getProvince() {
		return province;
	}

	public void setProvince(String province) {
		this.province = province;
	}

	public String getPostalCode() {
		return postalCode;
	}

	public void setPostalCode(String postalCode) {
		this.postalCode = postalCode;
	}

	public String getCountry() {
		return country;
	}

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
