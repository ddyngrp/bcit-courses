using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace XMLdotNET
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
            //Application.Run(new frmXML());
            //Application.Run(new XMLdotNET.XMLSamples.LoadingXMLDocumentAsynchronously());
            //Application.Run(new XMLdotNET.XMLHotDOM.TestHotDOM());
            //Application.Run(new XMLdotNET.XPathEvaluator.XpathEval());
            //Application.Run(new XMLdotNET.XMLDataReader.TestXMLDataReader());
            //Application.Run(new XMLdotNET.ReadXML.ReadXML());
            //Application.Run(new XMLdotNET.WriteXML.WriteXML());
            Application.Run(new XMLdotNET.DiffGram.DiffGram());
        }
    }
}