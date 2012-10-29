using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace COMP2690_Ass05
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new NewsReader());
        }
    }
}