using System;
using System.Collections.Generic;
using System.Text;

namespace COMP2690_Lab01
{
    class Program
    {
        static void Main(string[] args)
        {
            string inputName;
            string inputPassword;
            const string PASSWORD = "radish";

            Console.Write("I demand that you enter your name post haste: ");
            inputName = Console.ReadLine();

            Console.Write("\nSplendid! Now what's the password? ");
            inputPassword = Console.ReadLine();

            if (inputPassword.ToLower().Trim() == PASSWORD)
            {
                Console.Write("\nHello, " + inputName + ", and welcome.\n");
            }

            Console.Write("\nPress any key to continue...");
            Console.ReadLine();
        }
    }
}
