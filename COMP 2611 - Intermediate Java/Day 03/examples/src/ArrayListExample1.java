import java.util.ArrayList;

public class ArrayListExample1 {
	public static void main(String[] args) {
		ArrayList<String> list = new ArrayList<String>();
		list.add("This");
		list.add("is");
		list.add("is");
		list.add("a");
		list.add("a");
		list.add("test");
		display(list);
	}

	static void display(ArrayList<String> list) {
		System.out.println("The size is: " + list.size());
		for (int i = 0; i < list.size(); i++) {
			String s = list.get(i);
			System.out.println(s); // didn't because we are just calling toString
		}
	}
}
