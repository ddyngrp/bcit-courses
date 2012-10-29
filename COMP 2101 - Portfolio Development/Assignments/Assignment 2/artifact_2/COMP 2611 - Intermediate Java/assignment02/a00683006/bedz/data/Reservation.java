/**
 * Project: assignment02
 * File: Reservations.java
 * Date: 24-Sep-07
 * Time: 2:19:57 AM
 */
package a00683006.bedz.data;

/**
 * Holds reservation information
 * @author Steffen L. Norgren, A00683006
 * 
 */
public class Reservation {
	
	private Integer id;
	private Integer roomNumber;
	private Integer guestId;
	private Payment payment;
	
	/**
	 * Default constructor.
	 */
	public Reservation() {
	}
	
	/**
	 * Creates a reservation using the following parameters.
	 * @param id
	 * @param roomNumber
	 * @param guestId
	 * @param payment
	 */
	public Reservation(Integer id, Integer roomNumber, Integer guestId, Payment payment) {
		setId(id);
		setRoomNumber(roomNumber);
		setGuestId(guestId);
		setPayment(payment);
	}

	/**
	 * @return the id
	 */
	public Integer getId() {
		return id;
	}

	/**
	 * @param id the id to set
	 */
	public void setId(Integer id) {
		this.id = id;
	}

	/**
	 * @return the roomNumber
	 */
	public Integer getRoomNumber() {
		return roomNumber;
	}

	/**
	 * @param roomNumber the roomNumber to set
	 */
	public void setRoomNumber(Integer roomNumber) {
		this.roomNumber = roomNumber;
	}

	/**
	 * @return the guestId
	 */
	public Integer getGuestId() {
		return guestId;
	}

	/**
	 * @param guestId the guestId to set
	 */
	public void setGuestId(Integer guestId) {
		this.guestId = guestId;
	}

	/**
	 * @return the payment
	 */
	public Payment getPayment() {
		return payment;
	}

	/**
	 * @param payment the payment to set
	 */
	public void setPayment(Payment payment) {
		this.payment = payment;
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
	    
	    retValue = "Reservation{"
	        + "id=" + this.id + TAB
	        + "roomNumber=" + this.roomNumber + TAB
	        + "guestId=" + this.guestId + TAB
	        + "payment=" + this.payment
	        + "}";
	
	    return retValue;
	}
}
