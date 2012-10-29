import java.util.*;

public class ToArrayExample {
	
	public static void main(String[] args) {
		ArrayList<String> items = new ArrayList<String>();
		items.add("Orange");
		items.add("Green");
		items.add("White");
		String[] colours = items.toArray(new String[0]);
		CollectionUtil.display(colours);
	}
}
