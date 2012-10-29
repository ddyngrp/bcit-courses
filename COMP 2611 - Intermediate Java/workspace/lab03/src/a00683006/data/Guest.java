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
public class Guest implements Comparable<Guest> {
	
	private String lastName;
	private String firstName;
	private Address address;
	private String phoneNumber;
	private String emailAddress;
	
	/**
	 * Default constructor. This does nothing!
	 */
	public Guest() {
	}
	
	/**
	 * @param lastName
	 * @param firstName
	 * @param phoneNumber
	 * @param emailAddress
	 */
	public Guest(String lastName, String firstName, String phoneNumber, String emailAddress) {
		this.lastName = lastName;
		this.firstName = firstName;
		this.phoneNumber = phoneNumber;
		this.emailAddress = emailAddress;
	}
	
	/**
	 * 
	 * @param GUEST_DATA
	 */
	public Guest(String[] GUEST_DATA) {
		this(GUEST_DATA[0], GUEST_DATA[1], GUEST_DATA[2], GUEST_DATA[3]);
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
	
	/**
	 * Compares the current object with the object passed to it.
	 */
	public int compareTo(Guest guestCompare) {
        int cityCompare = address.getCity().compareTo(guestCompare.address.getCity());
        return cityCompare;
    }

	/* (non-Javadoc)
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((address == null) ? 0 : address.hashCode());
		result = prime * result
				+ ((emailAddress == null) ? 0 : emailAddress.hashCode());
		result = prime * result
				+ ((firstName == null) ? 0 : firstName.hashCode());
		result = prime * result
				+ ((lastName == null) ? 0 : lastName.hashCode());
		result = prime * result
				+ ((phoneNumber == null) ? 0 : phoneNumber.hashCode());
		return result;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		final Guest other = (Guest) obj;
		if (address == null) {
			if (other.address != null)
				return false;
		} else if (!address.equals(other.address))
			return false;
		if (emailAddress == null) {
			if (other.emailAddress != null)
				return false;
		} else if (!emailAddress.equals(other.emailAddress))
			return false;
		if (firstName == null) {
			if (other.firstName != null)
				return false;
		} else if (!firstName.equals(other.firstName))
			return false;
		if (lastName == null) {
			if (other.lastName != null)
				return false;
		} else if (!lastName.equals(other.lastName))
			return false;
		if (phoneNumber == null) {
			if (other.phoneNumber != null)
				return false;
		} else if (!phoneNumber.equals(other.phoneNumber))
			return false;
		return true;
	}
}
