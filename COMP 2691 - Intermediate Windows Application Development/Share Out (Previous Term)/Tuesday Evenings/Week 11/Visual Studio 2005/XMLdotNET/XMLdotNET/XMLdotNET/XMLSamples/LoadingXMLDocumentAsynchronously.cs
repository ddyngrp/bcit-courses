using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Xml;

namespace XMLdotNET.XMLSamples
{
    public partial class LoadingXMLDocumentAsynchronously : Form
    {


        IAsyncResult iar;
        private delegate void XmlDomAsyncLoaderCallback();
        
        public LoadingXMLDocumentAsynchronously()
        {
            InitializeComponent();
        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            
            XmlDomAsyncLoaderCallback x = new XmlDomAsyncLoaderCallback(LoadXmlDocument);
            iar = this.BeginInvoke(x);

            toolStripStatusLabel1.Text = "Loading document...";
      

            this.Refresh(); 
        }
        private void LoadXmlDocument()
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(InputFile.Text);

            this.EndInvoke(iar);

            toolStripStatusLabel1.Text = "Document loaded.";
            Output.Text = doc.OuterXml;
            Output.ReadOnly = false;
            return;
        }
    }
}