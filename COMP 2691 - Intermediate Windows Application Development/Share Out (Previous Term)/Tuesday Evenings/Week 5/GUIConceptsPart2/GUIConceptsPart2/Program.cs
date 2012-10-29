using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace GUIConceptsPart2
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
            // This method enables visual styles for the application. 
            // Controls will draw with visual styles if the control and the operating system support it. 
            // To have an effect, EnableVisualStyles()()() must be called before creating any controls in the application; typically, 
            // EnableVisualStyles()()() is the first line in the Main function
            Application.SetCompatibleTextRenderingDefault(false);  // false: New controls can use GDI+. 

            //Application.Run(new ImageListControl());
            //Application.Run(new TreeViewControl());
            //Application.Run(new TreeViewDirectoryStructureForm());
            //Application.Run(new ListViewTestForm());
            //Application.Run(new ListViewControl());
            //Application.Run(new UsingTabsForm());
            //Application.Run(new TabControl());
            Application.Run(new PopulateTreeViewfromDataSetForm());
            //Application.Run(new ADONetSamples.ConnString.FromConfig());
            //Application.Run(new ADONetSamples.Factory.CallDb());
            //Application.Run(new ADONetSamples.Factory.Factories());
            //Application.Run(new ADONetSamples.Readers.MultiResult());
            //Application.Run(new ADONetSamples.Async.Callback());
            //Application.Run(new ADONetSamples.Async.MultipleCommands());
            //Application.Run(new ADONetSamples.Async.NonBlocking());
            //Application.Run(new ADONetSamples.Async.Parallel());
            //Application.Run(new XMLSamples.LoadingXMLDocumentAsynchronously());
            //Application.Run(new ADONetExamples());
        }
    }
}