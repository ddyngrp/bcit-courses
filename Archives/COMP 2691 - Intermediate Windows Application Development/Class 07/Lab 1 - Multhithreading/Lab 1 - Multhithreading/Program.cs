using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Lab_1___Multhithreading
{
    class Program
    {
        static void Main(string[] args)
        {
            ThreadStart starter = new ThreadStart(Counting);
            Thread[] threads = new Thread[10];

            for (int i = 0; i < 10; ++i)
            {
                threads[i] = new Thread(starter);
                threads[i].Start();
            }

            foreach (Thread thread in threads)
            {
                //thread.Start();
                thread.Join();
            }

            Console.Read();
        }

        static void Counting()
        {
            for (int i = 1; i <= 20; i++)
            {
                Console.WriteLine("Count: {0} - Thread: {1}", i, Thread.CurrentThread.ManagedThreadId);
                Thread.Sleep(10);
            }
        }
    }
}
