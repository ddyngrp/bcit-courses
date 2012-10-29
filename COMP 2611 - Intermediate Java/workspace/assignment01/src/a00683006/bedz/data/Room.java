/**
 * Project: assignment01
 * File: Room.java
 * Date: 24-Sep-07
 * Time: 2:19:33 AM
 */
package a00683006.bedz.data;

/**
 * Holds room information.
 * @author Steffen L. Norgren, A00683006
 * 
 */
public class Room {
	
	private Integer number;
	private float rate;
	private String name;
	private String description;
	private String imageName;
	private int maximumNumberOfGuests;
	
	/**
	 * Default constructor.
	 */
	public Room() {
	}
	
	/**
	 * Creates a room using the following parameters.
	 * @param number
	 * @param rate
	 * @param name
	 * @param description
	 * @param imageName
	 * @param maximumNumberOfGuests
	 */
	public Room(Integer number, float rate, String name, String description, String imageName,
			int maximumNumberOfGuests) {
		setNumber(number);
		setRate(rate);
		setName(name);
		setDescription(description);
		setImageName(imageName);
		setMaximumNumberOfGuests(maximumNumberOfGuests);
	}
	
	/**
	 * @return the number
	 */
	public Integer getNumber() {
		return number;
	}
	/**
	 * @param number the number to set
	 */
	public void setNumber(Integer number) {
		this.number = number;
	}
	/**
	 * @return the rate
	 */
	public float getRate() {
		return rate;
	}
	/**
	 * @param rate the rate to set
	 */
	public void setRate(float rate) {
		this.rate = rate;
	}
	/**
	 * @return the name
	 */
	public String getName() {
		return name;
	}
	/**
	 * @param name the name to set
	 */
	public void setName(String name) {
		this.name = name;
	}
	/**
	 * @return the description
	 */
	public String getDescription() {
		return description;
	}
	/**
	 * @param description the description to set
	 */
	public void setDescription(String description) {
		this.description = description;
	}
	/**
	 * @return the imageName
	 */
	public String getImageName() {
		return imageName;
	}
	/**
	 * @param imageName the imageName to set
	 */
	public void setImageName(String imageName) {
		this.imageName = imageName;
	}
	/**
	 * @return the maximumNumberOfGuests
	 */
	public int getMaximumNumberOfGuests() {
		return maximumNumberOfGuests;
	}
	/**
	 * @param maximumNumberOfGuests the maximumNumberOfGuests to set
	 */
	public void setMaximumNumberOfGuests(int maximumNumberOfGuests) {
		this.maximumNumberOfGuests = maximumNumberOfGuests;
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
	    
	    retValue = "Room{"
	        + "number=" + this.number + TAB
	        + "rate=" + this.rate + TAB
	        + "name='" + this.name + "'" + TAB
	        + "description='" + this.description + "'" + TAB
	        + "imageName='" + this.imageName + "'" + TAB
	        + "maximumNumberOfGuests=" + this.maximumNumberOfGuests
	        + "}";

	    return retValue;
	}
}
