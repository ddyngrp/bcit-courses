using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Lab03
{
    class Program
    {
        static void Main(string[] args)
        {
            int result;
            int x;
            int y;

            Console.WriteLine("Excercise #1");

            if (getIntFromUser("\nPlease enter an integer: ", out result))
            {
                Console.Write("You entered: " + result);
            }
            else
            {
                Console.Write("You entered NOTHING!!!");
            }

            getIntFromUser("\nPlease enter a whole number: ", out result);
            x = result;
            getIntFromUser("\nPlease enter a whole number: ", out result);
            y = result;

            Console.Read();
        }

        private static void DoSomeMath(int x, int y)
        {
        }

        /// <summary>
        /// Gets an integer from the user. Keeps prompting until the user either
        /// enters a valid integer or blank.
        /// </summary>
        /// <param name="prompt">Message with which to prompt the user. Makes
        /// this method reusable in any console application.</param>
        /// <param name="result">(OUT) The integer entered by the user.</param>
        /// <returns>true if the user entered an integer; false if the user
        /// entered nothing (empty string)</returns>
        private static bool getIntFromUser(string prompt, out int result)
        {
            string input;

            do
            {
                Console.Write(prompt);
                input = Console.ReadLine();

                if (input == "") break;	// Allow user to exit.

            } while (int.TryParse(input, out result) == false);

            if (input == "")
            {
                result = 0;
                return false;
            }
            else
            {
                result = Convert.ToInt32(input);
                return true;
            }
        }
    }
}
