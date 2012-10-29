import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ConsoleUtil {

	public static String getText(String prompt) {
		String string = "";
		InputStreamReader reader = new InputStreamReader(System.in);
		BufferedReader input = new BufferedReader(reader);
		System.out.print(prompt);
		System.out.flush();
		try {
			string = input.readLine();
		} catch (IOException e) { // Check for I/O errors
			System.out.println("An IOException hs occured");
			return "";
		}
		return string.trim();
	}
}
