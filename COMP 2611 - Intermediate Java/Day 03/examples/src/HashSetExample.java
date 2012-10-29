import java.util.*;

public class HashSetExample {
	public static void main(String[] args) {
		HashSet set = new HashSet();
		System.out.println(set.add("This") ? "\"This\" added" : "\"This\" rejected");
		System.out.println(set.add("is") ? "\"is\" added" : "\"is\" rejected");
		System.out.println(set.add("is") ? "\"is\" added" : "\"is\" rejected");
		System.out.println(set.add("a") ? "\"a\" added" : "\"a\" rejected");
		System.out.println(set.add("a") ? "\"a\" added" : "\"a\" rejected");
		System.out.println(set.add("test") ? "\"test\" added" : "\"test\" rejected");

		CollectionUtil.display(set);
	}
}
