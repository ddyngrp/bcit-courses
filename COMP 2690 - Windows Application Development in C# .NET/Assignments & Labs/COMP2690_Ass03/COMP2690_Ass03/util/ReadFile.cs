using System;
using System.Collections;
using System.Text;

// Grab this namespace for the StreamReader class.
using System.IO;


namespace COMP2690_Ass03.util
{
    /// <summary>
    /// This is a simple utility class that will read the contents of any
    /// file and return it as an ArrayList.
    /// </summary>
    class ReadFile
    {
        /// <summary>
        /// Just the default constructor.
        /// </summary>
        public ReadFile()
        {
        }

        /// <summary>
        /// Reads the contents of any file and it line-by-line into an ArrayList.
        /// </summary>
        /// <param name="fileName">The path and file name</param>
        /// <returns>An ArrayList representing the file read.</returns>
        public ArrayList readFile(string fileName)
        {
            // This object lets you read from a file.
            StreamReader streamReader;

            // The ArrayList that is returned.
            ArrayList fileContents = new ArrayList();

            if (File.Exists(fileName))
            {
                // Read entire file line-by-line and display to the screen.
                try
                {
                    // Attempt to open the file.  It will throw
                    // an exception if there is a problem opening it, 
                    // hence the try/catch block.
                    streamReader = new StreamReader(fileName);

                    // Peek returns the ASCII value of the next character in 
                    // the file *without* advancing the file position.
                    // 
                    // This lets us see whether we've reached the end of the
                    // file yet.
                    while (streamReader.Peek() > 0)
                    {
                        // Read a line at a time, adding it to the ArrayList.
                        fileContents.Add(streamReader.ReadLine());
                    }

                    // Don't forget to close the file when you're finished with it!
                    streamReader.Close();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("\n" + ex.Message + "\n");
                }

            }
            else
            {
                Console.WriteLine("\nFile not found.\n");
            }

            return fileContents;
        }
    }
}
