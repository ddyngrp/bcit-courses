import java.util.*;

public class StringTokenizerExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new StringTokenizerExample();
	}
	
	private StringTokenizerExample() {
		String s = "Welcome to comp 2611";
		StringTokenizer st = new StringTokenizer(s);
		while(st.hasMoreTokens()) {
		  System.out.println(st.nextToken());
		}
	}

}
