import java.util.*;
import java.io.*;

/**
 * This program uses a set to print all unique words in System.in.
 */
public class SetTest {
	public static void main(String[] args) {
		// set to HashSet, LinkedHashSet or TreeSet
		Set<String> words = new HashSet<String>();
		long totalTime = 0;

		try {
			BufferedReader in = new BufferedReader(new InputStreamReader(
					System.in));
			String line;
			while ((line = in.readLine()) != null) {
				StringTokenizer tokenizer = new StringTokenizer(line);
				while (tokenizer.hasMoreTokens()) {
					String word = tokenizer.nextToken();
					long callTime = System.currentTimeMillis();
					words.add(word);
					callTime = System.currentTimeMillis() - callTime;
					totalTime += callTime;
				}
			}
		} catch (IOException e) {
			System.out.println("Error " + e);
		}

		Iterator iter = words.iterator();
		while (iter.hasNext()) {
			System.out.println(iter.next());
		}
		
		System.out.println(words.size() + " distinct words. " + totalTime
				+ " milliseconds.");
	}
}
