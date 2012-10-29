import java.util.*;

public class LinkedListExample {
	public static void main(String[] args) {
		LinkedList<String> list = new LinkedList<String>();
		list.add("is");
		list.add("is");
		list.add("a");
		list.add("a");
		list.addLast("test");
		list.addFirst("This");
		CollectionUtil.display(list);
	}
}
