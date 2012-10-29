package MVCTest.data;

import java.awt.Color;

public class NamedColor {
	
	private String name;
	private Color color;
	
	public NamedColor(String name, Color color) {
		this.name = name;
		this.color = color;
	}

	/**
	 * @return Returns the color.
	 */
	public Color getColor() {
		return color;
	}

	/**
	 * @param color The color to set.
	 */
	public void setColor(Color color) {
		this.color = color;
	}

	/**
	 * @return Returns the name.
	 */
	public String getName() {
		return name;
	}

	/**
	 * @param name The name to set.
	 */
	public void setName(String name) {
		this.name = name;
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
	    String result = "NamedColor ( "
	        + super.toString() + "\t"
	        + "name = " + this.name + "\t"
	        + "color = " + this.color + "\t"
	        + " )";
	    
	    return result;
	}

	
}
