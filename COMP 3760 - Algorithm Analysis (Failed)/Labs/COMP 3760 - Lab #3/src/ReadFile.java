import java.io.*;
import java.util.*;

/**
 * This is a universal text file reader. Input the text file to be
 * read and it will return an ArrayList representing the text file
 * line-by-line.
 * @author Steffen L. Norgren, A00683006
 *
 */
public class ReadFile {
	
	/**
	 * Default constructor.
	 */
	public ReadFile() {
	}
	
	/**
	 * This method reads a text file line by line and adds each line to an
	 * ArrayList and returns that list.
	 * @param fileName to be read.
	 * @return ArrayList of textFile contents.
	 */
	public ArrayList<String> textFile(String fileName){
	   	String line = null;
	   	ArrayList<String> textFileData = new ArrayList<String>();
	   	try {
	   		// create a new input stream for the file
	   		FileInputStream fis = new FileInputStream(fileName);
	   		// create a new buffered reader for the file stream so it can be read line by line.
	        BufferedReader reader = new BufferedReader(new InputStreamReader(fis));
	        // reads the file line by line and adds to an ArrayList
	        while((line = reader.readLine()) != null) {
				textFileData.add(line);
			}
	        // close the file
	        reader.close();
		}
		catch (FileNotFoundException error) {
			System.err.println("java.io.FileNotFoundException: " + error.getMessage());
		}
		catch (IOException error) {
		    System.err.println("java.io.IOException: " + error.getMessage());
		}
		return textFileData;
	 }
}