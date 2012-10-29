/**
 * Project: assignment02
 * File: Payment.java
 * Date: 1-Oct-07
 * Time: 7:39:45 PM
 */
package a00683006.bedz.data;

/**
 * Holds payment information.
 * @author Steffen L. Norgren, A00683006
 * 
 */
public class Payment {
	
	private PaymentType paymentType;
	private String creditCardNumber;
	private int expiryMonth;
	private int expiryYear;
	private String nameOnCard;
	private float roomCharge;
	private float roomTax;
	private float total;
	private float amount;
	
	/**
	 * Default constructor
	 */
	public Payment() {
	}
	
	/**
	 * Overloaded constructor to set some null and default values
	 * as we currently do not have instructions or data on how to deal
	 * with Payments.
	 * @param value
	 */
	public Payment(float value) {
		setPaymentType(null);
		setCreditCardNumber(null);
		setExpiryMonth(0);
		setExpiryYear(0);
		setNameOnCard(null);
		setRoomCharge(0);
		setRoomTax(0);
		setTotal(0);
		setAmount(0);		
	}

	/**
	 * Creates a payment using the following parameters.
	 * @param paymentType
	 * @param creditCardNumber
	 * @param expiryMonth
	 * @param expiryYear
	 * @param nameOnCard
	 * @param roomCharge
	 * @param roomTax
	 * @param total
	 * @param amount
	 */
	public Payment(PaymentType paymentType, String creditCardNumber,
			int expiryMonth, int expiryYear, String nameOnCard,
			float roomCharge, float roomTax, float total, float amount) {
		setPaymentType(paymentType);
		setCreditCardNumber(creditCardNumber);
		setExpiryMonth(expiryMonth);
		setExpiryYear(expiryYear);
		setNameOnCard(nameOnCard);
		setRoomCharge(roomCharge);
		setRoomTax(roomTax);
		setTotal(total);
		setAmount(amount);
	}

	/**
	 * @return the paymentType
	 */
	public PaymentType getPaymentType() {
		return paymentType;
	}

	/**
	 * @param paymentType the paymentType to set
	 */
	public void setPaymentType(PaymentType paymentType) {
		this.paymentType = paymentType;
	}

	/**
	 * @return the creditCardNumber
	 */
	public String getCreditCardNumber() {
		return creditCardNumber;
	}

	/**
	 * @param creditCardNumber the creditCardNumber to set
	 */
	public void setCreditCardNumber(String creditCardNumber) {
		this.creditCardNumber = creditCardNumber;
	}

	/**
	 * @return the expiryMonth
	 */
	public int getExpiryMonth() {
		return expiryMonth;
	}

	/**
	 * @param expiryMonth the expiryMonth to set
	 */
	public void setExpiryMonth(int expiryMonth) {
		this.expiryMonth = expiryMonth;
	}

	/**
	 * @return the expiryYear
	 */
	public int getExpiryYear() {
		return expiryYear;
	}

	/**
	 * @param expiryYear the expiryYear to set
	 */
	public void setExpiryYear(int expiryYear) {
		this.expiryYear = expiryYear;
	}

	/**
	 * @return the nameOnCard
	 */
	public String getNameOnCard() {
		return nameOnCard;
	}

	/**
	 * @param nameOnCard the nameOnCard to set
	 */
	public void setNameOnCard(String nameOnCard) {
		this.nameOnCard = nameOnCard;
	}

	/**
	 * @return the roomCharge
	 */
	public float getRoomCharge() {
		return roomCharge;
	}

	/**
	 * @param roomCharge the roomCharge to set
	 */
	public void setRoomCharge(float roomCharge) {
		this.roomCharge = roomCharge;
	}

	/**
	 * @return the roomTax
	 */
	public float getRoomTax() {
		return roomTax;
	}

	/**
	 * @param roomTax the roomTax to set
	 */
	public void setRoomTax(float roomTax) {
		this.roomTax = roomTax;
	}

	/**
	 * @return the total
	 */
	public float getTotal() {
		return total;
	}

	/**
	 * @param total the total to set
	 */
	public void setTotal(float total) {
		this.total = total;
	}

	/**
	 * @return the amount
	 */
	public float getAmount() {
		return amount;
	}

	/**
	 * @param amount the amount to set
	 */
	public void setAmount(float amount) {
		this.amount = amount;
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
	    
	    retValue = "Payment{"
	        + "paymentType=" + this.paymentType + TAB
	        + "creditCardNumber='" + this.creditCardNumber + "'" + TAB
	        + "expiryMonth=" + this.expiryMonth + TAB
	        + "expiryYear=" + this.expiryYear + TAB
	        + "nameOnCard='" + this.nameOnCard + "'" + TAB
	        + "roomCharge=" + this.roomCharge + TAB
	        + "roomTax=" + this.roomTax + TAB
	        + "total=" + this.total + TAB
	        + "amount=" + this.amount
	        + "}";
	
	    return retValue;
	}
	
}
