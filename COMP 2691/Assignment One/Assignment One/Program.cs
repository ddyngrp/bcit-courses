using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Assignment_One
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

            // If the directory doesn't exist, exit the application
            try
            {
                Application.Run(new FileWatcher());
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message.ToString() + "\nPlease make sure the directory exists.", "Invalid Directory", 
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                Application.Exit();
            }
        }
    }
}
