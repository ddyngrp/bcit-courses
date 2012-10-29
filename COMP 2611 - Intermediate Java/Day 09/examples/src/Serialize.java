import java.util.*;
import java.io.*;

public class Serialize {
	private static final String FILENAME = "movies.jsr";

	public static void main(String args[]) {
		ArrayList movies = new ArrayList();
		movies.add(new Movie("Drama", "Elizabeth I"));
		movies.add(new Movie("Action", "The Bourne Identity"));
		movies.add(new Movie("Comedy", "Ferris Bueller's Day Off"));
		movies.add(new Movie("Cartoon", "Shrek"));

		// stream the movies out to a file
		ObjectOutputStream out = null;
		try {
			out = new ObjectOutputStream(new FileOutputStream(FILENAME));
			out.writeObject(movies);
		} catch (IOException e) {
			System.out.println(e);
		} finally {
			try {
				out.close();
			} catch (IOException e) { }
		}
	}
}
