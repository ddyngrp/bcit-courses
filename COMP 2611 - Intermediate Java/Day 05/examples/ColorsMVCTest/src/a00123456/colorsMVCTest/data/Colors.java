package a00123456.colorsMVCTest.data;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Observable;
import java.awt.Color;

public class Colors extends Observable {

	private static Colors theInstance;
	private ArrayList colors;
	
	private Colors() {
		colors = new ArrayList();
		
		loadColors();
	}
	
	public static Colors getTheInstance() {
		if (theInstance == null) {
			theInstance = new Colors();
		}
		return theInstance;
	}

	private void loadColors() {
		colors.add(new NamedColor("Black", Color.BLACK));
		colors.add(new NamedColor("Blue", Color.BLUE));
		colors.add(new NamedColor("Cyan", Color.CYAN));
		colors.add(new NamedColor("Dark Gray", Color.DARK_GRAY));
		colors.add(new NamedColor("Gray", Color.GRAY));
		colors.add(new NamedColor("Green", Color.GREEN));
		colors.add(new NamedColor("Light Gray", Color.LIGHT_GRAY));
		colors.add(new NamedColor("Magenta", Color.MAGENTA));
		colors.add(new NamedColor("Orange", Color.ORANGE));
		colors.add(new NamedColor("Pink", Color.PINK));
		colors.add(new NamedColor("Red", Color.RED));
		colors.add(new NamedColor("White", Color.WHITE));
		colors.add(new NamedColor("Yellow", Color.YELLOW));
	}
	
	public Iterator getIterator() {
		return colors.iterator();
	}
}
