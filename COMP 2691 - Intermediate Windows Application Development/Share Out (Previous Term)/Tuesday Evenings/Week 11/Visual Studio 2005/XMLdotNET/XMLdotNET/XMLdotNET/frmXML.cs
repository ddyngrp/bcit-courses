using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Xml.XPath;

namespace XMLdotNET
{
    public partial class frmXML : Form
    {
        public frmXML()
        {
            InitializeComponent();
        }

        private void btnLab1_Click(object sender, EventArgs e)
        {
            //Declare and create new XmlDocument 
            XmlDocument xmlDoc = new XmlDocument();
            XmlElement el;
            int childCounter;
            int grandChildCounter;

            //Create the xml declaration first 
            xmlDoc.AppendChild(xmlDoc.CreateXmlDeclaration("1.0", "utf-8", null));

            //Create the root node and append into doc 
            el = xmlDoc.CreateElement("myRoot");
            xmlDoc.AppendChild(el);
            
            //Child Loop
            for (childCounter = 1; childCounter <= 4; childCounter++)
            {
                XmlElement childelmt;
                XmlAttribute childattr;

                //Create child with ID attribute 
                childelmt = xmlDoc.CreateElement("myChild");
                childattr = xmlDoc.CreateAttribute("ID");
                childattr.Value = childCounter.ToString();
                childelmt.Attributes.Append(childattr);

                //Append element into the root element 
                el.AppendChild(childelmt);
                for (grandChildCounter = 1; grandChildCounter <= 3; grandChildCounter++)
                {
                    //Create grandchildren 
                    childelmt.AppendChild(xmlDoc.CreateElement("GrandChild"));
                }
            }
            //Save to file 
            xmlDoc.Save("XmlDocumentTest.xml");
            lblDisplay.Text = "XmlDocumentTest.xml Created";

        }

        private void btnLab2_Click(object sender, EventArgs e)
        {
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load("XmlDocumentTest.xml");
            RecurseNodes(xmlDoc.DocumentElement);
        }
        public void RecurseNodes(XmlNode node)
        {
            //start recursive loop with level 0 
            RecurseNodes(node, 0);
        }
        public void RecurseNodes(XmlNode node, int level)
        {
            string s;
            s = string.Format("{0} Type:{1} Name:{2} Attr: ",
            new string('-', level), node.NodeType, node.Name);
            foreach (XmlAttribute attr in node.Attributes)
            {
                s += string.Format("{0}={1} ", attr.Name, attr.Value);
            }
            lblDisplay.Text += s + "\n";
            foreach (XmlNode n in node.ChildNodes)
            {
                RecurseNodes(n, level + 1);
            }
        }

        private void btnLab3_Click(object sender, EventArgs e)
        {
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load("XmlDocumentTest.xml");
            XPathNavigator xpathNav = xmlDoc.CreateNavigator();
            xpathNav.MoveToRoot();
            RecurseNavNodes(xpathNav);
        }
        public void RecurseNavNodes(XPathNavigator node)
        {
            //start recursive loop with level 0 
            RecurseNavNodes(node, 0);
        }
        public void RecurseNavNodes(XPathNavigator node, int level)
        {
            string s = null;
            s = string.Format("{0} Type:{1} Name:{2} Attr: ",
                new string('-', level), node.NodeType, node.Name);
            if (node.HasAttributes)
            {
                node.MoveToFirstAttribute();
                do
                {
                    s += string.Format("{0}={1} ", node.Name, node.Value);
                } while (node.MoveToNextAttribute());
                node.MoveToParent();
            }
            lblDisplay.Text += s + "\n";

            if (node.HasChildren)
            {
                node.MoveToFirstChild();
                do
                {
                    RecurseNavNodes(node, level + 1);
                } while (node.MoveToNext());
                node.MoveToParent();
            }
        }

        private void btnLab4_Click(object sender, EventArgs e)
        {
            string s;
            //Declare and create new XmlDocument 
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load("XmlSample.xml");
            XmlNode node;
            node = xmlDoc.GetElementById("ref-3");
            s = string.Format("Type:{0} Name:{1} Attr:",
           node.NodeType, node.Name);
            foreach (XmlAttribute a in node.Attributes)
            {
                s += string.Format("{0}={1} ", a.Name, a.Value);
            }
            lblDisplay.Text = s + "\n";
        }

        private void btnLab5_Click(object sender, EventArgs e)
        {
            string s;
            //Declare and create new XmlDocument 
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load("XmlSample.xml");

            XmlNode node;
            node = xmlDoc.SelectSingleNode("//myChild[@ChildID='ref-3']");
            s = string.Format("Type:{0} Name:{1} Attr:", node.NodeType, node.Name);
            foreach (XmlAttribute a in node.Attributes)
            {
                s += string.Format("{0}={1} ", a.Name, a.Value);
            }
            lblDisplay.Text = s + "\n";

        }

        private void btnLab6_Click(object sender, EventArgs e)
        {
            string s;
            //Declare and create new XmlDocument 
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load("XmlSample.xml");

            XmlNodeList elmts;
            elmts = xmlDoc.GetElementsByTagName("myGrandChild");

            foreach (XmlNode node in elmts)
            {
                s = string.Format("Type:{0} Name:{1}",
                    node.NodeType, node.Name);
                lblDisplay.Text += s + "\n";
            }

        }

        private void btnLab7_Click(object sender, EventArgs e)
        {
            string s;
            //Declare and create new XmlDocument 
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load("XmlSample.xml");
            XmlNodeList elmts;
            elmts = xmlDoc.SelectNodes("//myGrandChild");
            foreach (XmlNode node in elmts)
            {
                s = string.Format("Type:{0} Name:{1}",
                 node.NodeType, node.Name);
                lblDisplay.Text += s + "\n";
            } 
        }


    }
}