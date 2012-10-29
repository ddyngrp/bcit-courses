using System;
using System.Collections;
using System.Text;

using COMP2690_Ass03.util;
using COMP2690_Ass03.data;

namespace COMP2690_Ass03
{
    class Program
    {
        static void Main(string[] args)
        {
            // General instructions for the user.
            string instructions = "The syntax of the command is incorrect.\n\n" + 
                "To use this program requires you to input a file name as an argument.\n" +
                "For example \"sportsresults c:\\path\\filename.txt\"\n";

            // Check to see if the number of arguments supplied is valid.
            if (args.Length > 1 || args.Length == 0)
            {
                Console.WriteLine(instructions);
            }
            else
            {
                // create a new file reader object
                ReadFile fileReader = new ReadFile();

                // read and process the raw sports data from the file
                ArrayList sportsList = processResults(new ArrayList(fileReader.readFile(args[0])));

                // display the results of the sports matches
                displayResults(sportsList);
            }
        }

        /// <summary>
        /// Depending on the sport contained in each line, this will
        /// create the appropriate sports object and add it to the sports ArrayList.
        /// </summary>
        /// <param name="fileContents">ArrayList of CSV values representing sports games</param>
        /// <returns>ArrayList sports objects</returns>
        private static ArrayList processResults(ArrayList fileContents)
        {
            ArrayList sports = new ArrayList(); // an ArrayList that will contain sports objects.

            // iterates through the ArrayList and creates
            foreach (string line in fileContents)
            {
                // Add objects to the sports list depending on what they are
                if (line.ToLower().Contains("tennis".ToLower()))
                {
                    sports.Add(new Tennis(line));
                }
                else if (line.ToLower().Contains("hockey".ToLower()))
                {
                    sports.Add(new Hockey(line));
                }
            }

            return sports;
        }

        /// <summary>
        /// Display the results of all the sports matches.
        /// </summary>
        /// <param name="sports">ArrayList of sports objects</param>
        private static void displayResults(ArrayList sports)
        {
            foreach (Object sport in sports)
            {
                Console.WriteLine(sport);
            }
        }
    }
}
