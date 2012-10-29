using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Xml;
using System.IO;

namespace XMLdotNET.XPathEvaluator
{
    public partial class XpathEval : Form
    {
        public XpathEval()
      
        {    
            InitializeComponent();
        }
        
        //Examples:
        //              //Employee[lastname='Davolio']
        //               /MyDataSet/NorthwindEmployees//Employee[lastname='Davolio']

        #region My Functions

        // **********************************************************************
        // Refresh the UI with the results of the XPath expression
        private void LoadButton_Click(object sender, EventArgs e)
        {
            LoadDocument(FileName.Text);
            EvalButton.Enabled = true;
        }
        // **********************************************************************
        
        // Refresh the UI with the results of the XPath expression
        private void LoadDocument(string xmlFile)
        {
            // Load and show the XML source
            StreamReader reader = new StreamReader(xmlFile);
            string buf = reader.ReadToEnd();
            reader.Close();

            SourceFile.Text = buf;
        }
        // **********************************************************************

        // **********************************************************************
		// Fire the evaluation procedure
		private void EvalButton_Click(object sender, System.EventArgs e)
		{
			EvaluateExpression(FileName.Text, XPathExpression.Text);
		}
		// **********************************************************************

        // **********************************************************************
        // Evaluate the XPath expression
        private void EvaluateExpression(string xmlFile, string xpathExpr)
        {
            // Load the XMLDOM
            XmlDocument doc = new XmlDocument();
            doc.Load(xmlFile);

            // Select the context node
            XmlNode root = doc.SelectSingleNode(ContextNode.Text);

            // Run the query
            string buf = "";
            int nodeCount = 0;
            XmlNodeList nodes = null;
            try
            {
                nodes = root.SelectNodes(xpathExpr);
                nodeCount = nodes.Count;
            }
            catch { }
            if (nodes == null || nodeCount <= 0)
                buf = "<results>No nodes selected</results>";
            else
                buf = BuildOutputString(nodes);

            ShowResults(buf, nodeCount);
            return;
        }
        // **********************************************************************

        // **********************************************************************
        // Build the output string starting from the XPath node set
        private string BuildOutputString(XmlNodeList nodes)
        {
            StringBuilder sb = new StringBuilder("");
            StringWriter sw = new StringWriter(sb);
            XmlTextWriter writer = new XmlTextWriter(sw);
            writer.Formatting = Formatting.Indented;

            writer.WriteStartElement("results");
            foreach (XmlNode n in nodes)
            {
                LoopThroughChildren(writer, n);
            }
            writer.WriteEndElement();
            writer.Close();

            return sw.ToString();
        }
        // **********************************************************************

        // **********************************************************************
        // Recursively loop over a node subtree
        private void LoopThroughChildren(XmlTextWriter writer, XmlNode rootNode)
        {
            // Write the start tag
            if (rootNode.NodeType == XmlNodeType.Element)
            {
                writer.WriteStartElement(rootNode.Name);

                // Write any attributes 
                foreach (XmlAttribute a in rootNode.Attributes)
                    writer.WriteAttributeString(a.Name, a.Value);

                // Write any child nodes
                foreach (XmlNode n in rootNode.ChildNodes)
                    LoopThroughChildren(writer, n);

                // Write the end tag
                writer.WriteEndElement();
            }
            else
                // Write any text
                if (rootNode.NodeType == XmlNodeType.Text)
                    writer.WriteString(rootNode.Value);
        }
        // **********************************************************************

        // **********************************************************************
        // Refresh the UI with the results of the XPath expression
        private void ShowResults(string buf, int count)
        {
            Results.Text = buf;

            // update the status bar too
            appStatus.Text = String.Format("{0} node(s) found.", count);
        }
        // **********************************************************************
      

        #endregion


    }
}