using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Xml;
using System.IO;

namespace XMLdotNET.NodeLayout
{
    public partial class XMLReadersinAction : Form
    {
        public XMLReadersinAction()
        {
            InitializeComponent();
        }

        #region Core Code

        // ******************************************************************************
        // Get the name of the file to process and invoke the parser
        private void ButtonLoad_Click(object sender, EventArgs e)
        {
            // Process the file and get the node layout
            string buf = GetXmlFileNodeLayout(FileName.Text);

            // Show the results
            OutputConsole.Text = buf;
        }
        // ******************************************************************************

        // ******************************************************************************
        private string GetXmlFileNodeLayout(string file)
        {
            // Open the stream 
            XmlTextReader reader = new XmlTextReader(file);

            // Initialize from a string
            //string xmlText = "<employee><hired>2001-2-8</hired><salary>150000</salary></employee>";
            //StringReader sr = new StringReader(xmlText);
            //XmlTextReader reader = new XmlTextReader(sr);
            //TextReader strReader = TextReader.Synchronized(sr); 

            // Loop through the nodes and creates the document layout
            // reading start and end element nodes
            StringWriter writer = new StringWriter();
            string tabPrefix = "";

            while (reader.Read())
            {
                // Write the start tag
                if (reader.NodeType == XmlNodeType.Element)
                {
                    tabPrefix = new string('\t', reader.Depth);
                    writer.WriteLine("{0}<{1}>", tabPrefix, reader.Name);
                }
                else
                {
                    // Write the end tag
                    if (reader.NodeType == XmlNodeType.EndElement)
                    {
                        tabPrefix = new string('\t', reader.Depth);
                        writer.WriteLine("{0}</{1}>", tabPrefix, reader.Name);
                    }
                }
            }

            // Write to the output window
            string buf = writer.ToString();
            writer.Close();

            // Close the stream 
            reader.Close();

            return buf;
        }
        // ******************************************************************************






        #endregion


    }
}