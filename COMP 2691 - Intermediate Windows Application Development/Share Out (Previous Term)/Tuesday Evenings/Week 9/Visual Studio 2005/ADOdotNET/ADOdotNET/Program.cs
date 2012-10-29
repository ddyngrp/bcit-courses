using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace ADOdotNET
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
                       
            //Application.Run(new ADOdotNET.Async.Callback_ThreadSafe());
            //Application.Run(new ADOdotNET.Async.Callback_NotThreadSafe());
            //Application.Run(new ADOdotNET.Async.MultipleCommands());
            
            //Application.Run(new ADOdotNET.ConnString.FromConfig());
            
            //Application.Run(new ADOdotNET.Factory.CallDb());
            //Application.Run(new ADOdotNET.Factory.Factories());

            //Application.Run(new ADOdotNET.Readers.MultiResult());
            //Application.Run(new ADOdotNET.ADONetGetData());
            Application.Run(new ADOdotNET.BindingSources());

            Application.Run(new ADOdotNET.Async.Parallel());

        }
    }
}