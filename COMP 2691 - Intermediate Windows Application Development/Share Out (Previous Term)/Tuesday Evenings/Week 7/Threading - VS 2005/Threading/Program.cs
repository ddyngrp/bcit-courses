using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Threading
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
            // Application.Run(new frmBackgroundWorker());
            // Application.Run(new Threading.ADONetSamples.Async.Callback() );
            //  Application.Run(new Threading.ADONetSamples.Async.Callback_NotThreadSafe());
            Application.Run(new Threading.ADONetSamples.Async.MultipleCommands());
        }
    }
}