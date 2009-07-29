using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Lab_2___Mutexes
{
    class Program
    {
        static void Main(string[] args)
        {
            Mutex oneMutex = null;
            const string MutexName = "RUNMEONLYONCE";

            try // Try and open the Mutex
            {
                oneMutex = Mutex.OpenExisting(MutexName);
            }
            catch (WaitHandleCannotBeOpenedException)
            {
                // Cannot open the mutex because it doesn't exist
            }

            // Create it if it doesn't exist
            if (oneMutex == null)
            {
                oneMutex = new Mutex(true, MutexName);
            }
            else
            {
                // Close the mutex and exit the application
                // because we can only have one instance
                oneMutex.Close();
                return;
            }

            Console.WriteLine("Our Application");
            Console.Read();
        }
    }
}
