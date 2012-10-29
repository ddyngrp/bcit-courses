import java.util.HashSet;

public class HashSetExample2 {

	public static void main(String[] args) {
		HashSet<String> set = new HashSet<String>();
		set.add("This");
		set.add("is");
		set.add("is");
		set.add("a");
		set.add("a");
		set.add("test");
		
		CollectionUtil.display(set);
	}
}
