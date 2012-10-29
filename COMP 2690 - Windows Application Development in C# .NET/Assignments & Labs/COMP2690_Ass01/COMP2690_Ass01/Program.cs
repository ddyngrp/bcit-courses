using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Ass01
{
    class Program
    {
        static void Main(string[] args)
        {
            int x;
            // Write the column headers
            Console.WriteLine("number\t" + "square\t" + "cube");

            // Loop through 0 through 10 and print out the cubed and squared numbers
            for (int i = 0; i <= 10; i++)
            {
                x = i; // setting the value of x to the current iteration through the loop

                // setting up a do while loop do that we can square and cube x
                int k = 0;
                do
                {
                    Console.Write(x + "\t");    // writing the value of x & tabbing
                    x *= i;                     // multiplying x by i
                    k++;
                } while (k < 3);

                Console.WriteLine();            // writing a new line
            }
            Console.Read();
        }
    }
}
