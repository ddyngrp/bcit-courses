import java.io.*;
import javax.swing.*;

public class TestObjectStreamForArray {
  public static void main(String[] args) 
      throws ClassNotFoundException, IOException {
    int[] numbers = {1, 2, 3, 4, 5};
    String[] strings = {"John", "Jim", "Jake"};
    JButton[] buttons = {new JButton("OK"), new JButton("Cancel")};
  
    // Create an output stream for file array.dat
    ObjectOutputStream output = 
      new ObjectOutputStream(new FileOutputStream("array.dat", true));
    
    // Write arrays to the object output stream
    output.writeObject(numbers);
    output.writeObject(strings);
    output.writeObject(buttons);
    
    // Close the stream
    output.close();
    
    // Create an input stream for file array.dat
    ObjectInputStream input = 
      new ObjectInputStream(new FileInputStream("array.dat"));

    int[] newNumbers = (int[])(input.readObject());
    String[] newStrings = (String[])(input.readObject());
    JButton[] newButtons = (JButton[])(input.readObject());
    
    // Display arrays
    for (int i = 0; i < newNumbers.length; i++)
      System.out.print(newNumbers[i] + " ");
    System.out.println();
    
    for (int i = 0; i < newStrings.length; i++)
      System.out.print(newStrings[i] + " ");
    System.out.println();
    
    for (int i = 0; i < newButtons.length; i++)
      System.out.print(newButtons[i].getText() + " ");
  }
}