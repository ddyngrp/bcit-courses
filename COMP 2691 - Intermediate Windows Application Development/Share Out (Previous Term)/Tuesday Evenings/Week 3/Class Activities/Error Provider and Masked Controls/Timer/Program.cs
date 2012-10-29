using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Timer
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
            Application.Run(new frmErrorProvider());
            // Application.Run(new frmMaskedTextBox());
        }
    }
}