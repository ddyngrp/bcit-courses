/**
 * Project: lab04
 * File: Guest.java
 * Date: 8-Oct-07
 * Time: 8:40:57 PM
 */

package a00683006.data;

import java.util.StringTokenizer;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Guest {
	
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
	 * Takes a comma separated string and sets the object's variables
	 * to equal the elements within that string if they pass some basic
	 * integrity tests.
	 * @param fileData
	 */
	public Guest(String fileData) throws DataException {
		StringTokenizer st=new StringTokenizer(fileData, ",");
		
		// Throws a new DataException if the number of elements isn't 4
		if (st.countTokens() == 4) {
			// uses replaceAll regular expressions to clean the data a bit
			setLastName(st.nextToken().replaceAll("[^a-zA-Z]", ""));
			setFirstName(st.nextToken().replaceAll("[^a-zA-Z]", ""));
			setPhoneNumber(st.nextToken().replaceAll("[^0-9\\- ()]", "").trim());
			setEmailAddress(st.nextToken().replaceAll("[\"]", "").trim());
		}
		else if (st.countTokens() < 4) {
			throw new DataException("[" + fileData + "] " +
					"does not contain enough data elements. Expected 4, got " + st.countTokens());
		}
		else {
			throw new DataException("[" + fileData + "] " +
					"has too many data elements. Expected 4, got " + st.countTokens());			
		}
			
	}
	
	/**
	 * @param lastName
	 * @param firstName
	 * @param address
	 * @param phoneNumber
	 * @param emailAddress
	 */
	public Guest(String lastName, String firstName, String phoneNumber,
			String emailAddress) throws DataException{
		setLastName(lastName);
		setFirstName(firstName);
		setPhoneNumber(phoneNumber);
		setEmailAddress(emailAddress);
	}
	
	/**
	 * @param guest
	 */
	public Guest(String[] guest) throws DataException {
		this(guest[0], guest[1], guest[2], guest[3]);
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
	 * Sets the phone number if it proves to be valid, otherwise throws a
	 * DataException
	 * @param phoneNumber the phoneNumber to set
	 */
	public void setPhoneNumber(String phoneNumber) throws DataException {
		// Test if the phone number is long enough after removing extra characters
		if (phoneNumber.replaceAll("[^0-9]", "").length() >= 10) {
			this.phoneNumber = phoneNumber;
		}
		else {
			throw new DataException("[" + phoneNumber + "] " +
					"does not appear to be a valid phone number");
		}
	}

	/**
	 * @return the emailAddress
	 */
	public String getEmailAddress() {
		return emailAddress;
	}

	/**
	 * Tests to see if the email address is valid, otherwise throws a DataException
	 * @param emailAddress the emailAddress to set
	 */
	public void setEmailAddress(String emailAddress) throws DataException {
		// Test if the email address is valid, otherwise throw a DataException
		if (emailAddress.contains("@") && emailAddress.contains(".")
				&& emailAddress.length() >= 6) {
			this.emailAddress = emailAddress;
		}
		else {
			throw new DataException("[" + emailAddress + "] " + 
					"does not appear to be a valid email address");
		}
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
	        + ")";
	
	    return retValue;
	}	
}