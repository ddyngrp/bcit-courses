package a00123456.data;

/**
 * © Copyright 2007 Eastman Kodak Company. All rights reserved.
 * User: scirka
 * Date: 15/09/2007
 * Time: 23:15:58
 */
public class Guest {
	private String lastName;
	private String firstName;
	private Address address;
	private String phoneNumber;
	private String emailAddress;

	public Guest() {
	}

	/**
	 * @param lastName
	 * @param firstName
	 * @param address
	 * @param phoneNumber
	 * @param emailAddress
	 */
	public Guest(String lastName, String firstName, String phoneNumber, String emailAddress) {
		this.lastName = lastName;
		this.firstName = firstName;
		this.phoneNumber = phoneNumber;
		this.emailAddress = emailAddress;
	}
	
	public Guest(String[] data) {
		this(data[0], data[1], data[2], data[3]);
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public Address getAddress() {
		return address;
	}

	public void setAddress(Address address) {
		this.address = address;
	}

	public String getPhoneNumber() {
		return phoneNumber;
	}

	public void setPhoneNumber(String phoneNumber) {
		this.phoneNumber = phoneNumber;
	}

	public String getEmailAddress() {
		return emailAddress;
	}

	public void setEmailAddress(String emailAddress) {
		this.emailAddress = emailAddress;
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
	    
	    retValue = "Guest ( "
	        + "lastName = " + this.lastName + TAB
	        + "firstName = " + this.firstName + TAB
	        + "address = " + this.address + TAB
	        + "phoneNumber = " + this.phoneNumber + TAB
	        + "emailAddress = " + this.emailAddress + TAB
	        + " )";
	
	    return retValue;
	}

	
}
