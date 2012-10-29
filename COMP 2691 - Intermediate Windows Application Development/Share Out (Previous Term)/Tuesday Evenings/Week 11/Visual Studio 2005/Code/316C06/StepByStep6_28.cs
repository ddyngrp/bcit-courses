using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Xml;

namespace _316C06
{
	/// <summary>
	/// Summary description for StepByStep6_28.
	/// </summary>
	public class StepByStep6_28 : System.Windows.Forms.Form
	{
		internal System.Windows.Forms.ListBox lbNodes;
		internal System.Windows.Forms.Button btnLoadXml;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public StepByStep6_28()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.lbNodes = new System.Windows.Forms.ListBox();
			this.btnLoadXml = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// lbNodes
			// 
			this.lbNodes.Location = new System.Drawing.Point(8, 40);
			this.lbNodes.Name = "lbNodes";
			this.lbNodes.Size = new System.Drawing.Size(432, 303);
			this.lbNodes.TabIndex = 3;
			// 
			// btnLoadXml
			// 
			this.btnLoadXml.Location = new System.Drawing.Point(8, 8);
			this.btnLoadXml.Name = "btnLoadXml";
			this.btnLoadXml.Size = new System.Drawing.Size(112, 23);
			this.btnLoadXml.TabIndex = 2;
			this.btnLoadXml.Text = "Load XML";
			this.btnLoadXml.Click += new System.EventHandler(this.btnLoadXml_Click);
			// 
			// StepByStep6_28
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(448, 357);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.lbNodes,
																		  this.btnLoadXml});
			this.Name = "StepByStep6_28";
			this.Text = "StepByStep6_28";
			this.ResumeLayout(false);

		}
		#endregion
		
		[STAThread]
		static void Main() 
		{
			Application.Run(new StepByStep6_28());
		}
		private void btnLoadXml_Click(object sender, System.EventArgs e)
		{
			// Browse for an XML file
			OpenFileDialog dlgOpen = new OpenFileDialog();
			dlgOpen.Title = "Select a File";
			dlgOpen.Filter = "XML files (*.xml)|*.xml|All Files(*.*)|*.*";
			if(dlgOpen.ShowDialog() == DialogResult.OK)
			{
				// Hook up to the disk file
				XmlTextReader xtr = new XmlTextReader(dlgOpen.FileName);
				xtr.WhitespaceHandling = WhitespaceHandling.None;
				XmlDocument xd = new XmlDocument();
				// Load the file into the XmlDocument
				xd.Load(xtr);
				// Add an item representing the document to the ListBox
				lbNodes.Items.Add("XML Document");
				// Find the root node, and add it together with its children
				XmlNode xnod = xd.DocumentElement;
				AddWithChildren(xnod, 1);
			}
		}

		private void AddWithChildren(XmlNode xnod, Int32 intLevel)
		{
			// Adds a node to the ListBox, together with its children. 
			// intLevel controls the depth of indenting
			XmlNode xnodWorking;
			String strIndent = new String(' ', 2 * intLevel);
			// Get the value of the node (if any)
			String strValue= (String) xnod.Value;
			if(strValue != null)
			{
				strValue = " : " + strValue;
			}
			// Add the node details to the ListBox
			lbNodes.Items.Add(strIndent + xnod.Name + strValue);
			// For an element node, retrieve the attributes
			if(xnod.NodeType == XmlNodeType.Element)
			{
				XmlNamedNodeMap mapAttributes= xnod.Attributes;
				// Add the attrbutes to the ListBox
				foreach(XmlNode xnodAttribute in mapAttributes)
				{
					lbNodes.Items.Add(strIndent + "  " + xnodAttribute.Name + " : " + xnodAttribute.Value);
				}
				// If there are any child nodes, call this procedure recursively
				if(xnod.HasChildNodes)
				{
					xnodWorking = xnod.FirstChild;
					while (xnodWorking != null)
					{
						AddWithChildren(xnodWorking, intLevel + 1);
						xnodWorking = xnodWorking.NextSibling;
					}
				}
			}
		}	
	}
}
