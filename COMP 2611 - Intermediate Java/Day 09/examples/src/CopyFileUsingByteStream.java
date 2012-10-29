// CopyFileUsingByteStream.java: Copy files
import java.io.*;

public class CopyFileUsingByteStream {
  /** Main method
     @param args[0] for sourcefile 
     @param args[1] for target file
    */
  public static void main(String[] args) { 
    // Declare input and output file streams
    FileInputStream fis = null;
    FileOutputStream fos = null;

    // Check usage
    if (args.length != 2) { 
      System.out.println(
        "Usage: java CopyFileUsingByteStream fromfile tofile");
      System.exit(0);
    }

    try { 
      // Create file input stream
      fis = new FileInputStream(new File(args[0]));

      // Create file output stream if the file does not exist
      File file = new File(args[1]);
      if (file.exists()) {
        System.out.println("file " + args[1] + " already exists");
        return;
      }
      else
        fos = new FileOutputStream(args[1]);

      // Display the file size
      System.out.println("The file " + args[0] + " has "+
        fis.available() + " bytes");

      // Continuously read a byte from fis and write it to fos
      int r;
      while ((r = fis.read()) != -1) {
        fos.write((byte)r);
      }
    }
    catch (FileNotFoundException ex) {
      System.out.println("File not found: " + args[0]);
    }
    catch (IOException ex) {
      System.out.println(ex.getMessage());
    }
    finally {
      try {
        // Close files
        if (fis != null) fis.close();
        if (fos != null) fos.close();
      }
      catch (IOException ex) {
        System.out.println(ex);
      }
    }
  }
}