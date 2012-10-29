import java.util.*;

public class HashMapExample {
	public static void main(String[] args) {
		HashMap<String, String> map = new HashMap<String, String>();
		map.put("one", "uno");
		map.put("two", "deux");
		map.put("two", "dos");
		map.put("three", "tres");
		map.put("four", "cuatro");
		map.put("five", "cinco");
		map.put("six", "seis");
		
		// note that map does not implement the Collection interface
		// we need to get the keySet, the valueSet or the entrySet
		Collection c = map.entrySet();
		
		CollectionUtil.display(c);
	}
}
