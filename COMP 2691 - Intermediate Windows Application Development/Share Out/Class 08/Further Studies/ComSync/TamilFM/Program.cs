
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Microsoft.Win32;

namespace TamilFM
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            /// flag to check wheather the new mutex is created or not
            bool fMutexCreated = false;
            /// get unique name
            string strMutexName = typeof(Program).GUID.ToString("B");

            Mutex mutex = null;
            try
            {
                // Create a new mutex object with a unique name
                mutex = new Mutex(false, strMutexName, out fMutexCreated);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error");
                Application.Exit();
            }
            if (fMutexCreated)
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new mainForm());
            }
            else
            {
                Application.Exit();
            }
        }
    }
}