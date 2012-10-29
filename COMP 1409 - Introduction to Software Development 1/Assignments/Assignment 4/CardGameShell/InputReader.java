import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * The InputReader will read a line of text from standard input and return a string.
 * You do not need to change this class.
 * 
 * @author Colleen Penrowley
 * @version Fall 2005
 */

public class InputReader
{
	private BufferedReader reader;

	/**
     * Create a new InputReader that reads text from the text terminal.
     */
	public InputReader()
	{
		reader = new BufferedReader(new InputStreamReader(System.in));
	}

	/**
     * Read one line of input and return it as a String. 
     *
     * @return  A String representing the input, or an empty String 
     *          if an error occurs.
     */
    public String readInputLine()
    {
        // print prompt
        System.out.print("> ");
        String line = "";

        try {
            line = reader.readLine();
        }
        catch(java.io.IOException exc) {
            System.out.println ("Read error: " + exc.getMessage());
        }
        return line;
    }
}
