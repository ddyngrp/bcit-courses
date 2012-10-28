using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Lab_3___Thread_Pool
{
    class Program
    {
        static void Main(string[] args)
        {
            WaitCallback callback = new WaitCallback(ShowMyText);
            ThreadPool.QueueUserWorkItem(callback, "Hello");
            ThreadPool.QueueUserWorkItem(callback, "Hi");
            ThreadPool.QueueUserWorkItem(callback, "Heya");
            ThreadPool.QueueUserWorkItem(callback, "Goodbye");
            Console.Read();
        }

        static void ShowMyText(object state)
        {
            string myText = (string)state;
            Console.WriteLine("Thread: {0} - {1}", Thread.CurrentThread.ManagedThreadId, myText);
        }
    }
}
