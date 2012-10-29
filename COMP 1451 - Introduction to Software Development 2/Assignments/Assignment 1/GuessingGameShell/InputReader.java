import java.util.Scanner;

/**
 * Class InputReader reads numbers typed at the keyboard. This version uses
 * the Scanner class from JDK 1.5.
 * 
 * 
 * @version    August 2005
 * @author     Colleen Penrowley 
 */
public class InputReader
{
    private Scanner scanner;

    /**
     * Create a new InputReader to read a coordinate pair.
     */
    public InputReader()
    {
        scanner = new Scanner(System.in);
    }

    /**
     * This method prompts the user for two numbers and returns a CoordinatePair with the 
     * first input as row and the second as column. If the user types a non-numeric value for
     * either coordinate, both will be set to -1. 
     */
    public CoordinatePair getCoordinates()
    {
        CoordinatePair coords = new CoordinatePair();
        System.out.println("Coordinates start from zero.");
        System.out.print("Type your choice of coordinates (row column) with a space between >");
        try {
            coords.setRow(scanner.nextInt());
            coords.setColumn(scanner.nextInt());    
        }
        catch(java.util.InputMismatchException exc) { // will catch non-numeric input
            scanner.nextLine();             // clear the buffer
            coords.setRow(-1);              // set values that we can check later
            coords.setColumn(-1);
        }
        return coords;
    }
    
    
}
