/**
 * Project: lab02
 * File: Guest.java
 * Date: 24-Sep-07
 * Time: 12:51:21 AM
 */
package a00683006.data;


/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Guest {
	
	private String lastName;
	private String firstName;
	private String phoneNumber;
	private String emailAddress;
	private Address address;
	
	/**
	 * Default constructor. This does nothing!
	 */
	public Guest() {
	}
	
	/**
	 * 
	 * @param GUEST_DATA
	 * @param address
	 */
	public Guest(String[] GUEST_DATA, Address address) {
		this.lastName = GUEST_DATA[0];
		this.firstName = GUEST_DATA[1];
		this.phoneNumber = GUEST_DATA[2];
		this.emailAddress = GUEST_DATA[3];
		this.address = address;
	}

	/**
	 * @return the lastName
	 */
	public String getLastName() {
		return lastName;
	}

	/**
	 * @param lastName the lastName to set
	 */
	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	/**
	 * @return the firstName
	 */
	public String getFirstName() {
		return firstName;
	}

	/**
	 * @param firstName the firstName to set
	 */
	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	/**
	 * @return the phoneNumber
	 */
	public String getPhoneNumber() {
		return phoneNumber;
	}

	/**
	 * @param phoneNumber the phoneNumber to set
	 */
	public void setPhoneNumber(String phoneNumber) {
		this.phoneNumber = phoneNumber;
	}

	/**
	 * @return the emailAddress
	 */
	public String getEmailAddress() {
		return emailAddress;
	}

	/**
	 * @param emailAddress the emailAddress to set
	 */
	public void setEmailAddress(String emailAddress) {
		this.emailAddress = emailAddress;
	}

	/**
	 * @return the address
	 */
	public Address getAddress() {
		return address;
	}

	/**
	 * @param address the address to set
	 */
	public void setAddress(Address address) {
		this.address = address;
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
