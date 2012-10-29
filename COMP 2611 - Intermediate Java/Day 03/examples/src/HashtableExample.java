import java.util.*;

public class HashtableExample {

	public static void main(String[] args) {
		int numElements = 7;
		String keys[] = { "Ant", "Dog", "Cat", "Pig", "Cow", "Hen", "Fly" };
		String color[] = { "black", "white", "blue", "pink", "orange", "red",
				"black" };
		Hashtable<String, String> table = new Hashtable<String, String>();
		for (int i = 0; i < numElements; i++) {
			table.put(keys[i], color[i]);
		}
		
		System.out.println(table); // dump the contents
		String key = ConsoleUtil.getText("Pick an animal- " + 
				CollectionUtil.print(keys, ", ") + ": ");
		String value = (String) (table.get(key));
		if (value != null) {
			System.out.println(key + ": " + value);
		}
	}

}
