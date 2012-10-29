// *************************************************************************** 
//
//    Applied XML Programming for Microsoft(r) .NET - Dino Esposito
//    Microsoft Press, 2002  ISBN: 0-7356-1801-1
//    
//    Chapter 6
//
//    Builds an XPath expression evaluator...
//    
// ***************************************************************************



using System;
using System.Drawing;
using System.Collections;
using System.Xml;
using System.IO;
using System.Text;
using System.Windows.Forms;
using System.Data;

namespace XPathEval_CS
{
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox FileName;
		private System.Windows.Forms.Button EvalButton;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.TextBox SourceFile;
		private System.Windows.Forms.Splitter splitter1;
		private System.Windows.Forms.TextBox Results;
		private System.Windows.Forms.TextBox XPathExpression;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button LoadButton;
		private System.Windows.Forms.TextBox ContextNode;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.StatusBar appStatus;

		public Form1()
		{
			InitializeComponent();
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.FileName = new System.Windows.Forms.TextBox();
			this.EvalButton = new System.Windows.Forms.Button();
			this.panel1 = new System.Windows.Forms.Panel();
			this.Results = new System.Windows.Forms.TextBox();
			this.splitter1 = new System.Windows.Forms.Splitter();
			this.SourceFile = new System.Windows.Forms.TextBox();
			this.appStatus = new System.Windows.Forms.StatusBar();
			this.XPathExpression = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.LoadButton = new System.Windows.Forms.Button();
			this.ContextNode = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.panel1.SuspendLayout();
			this.SuspendLayout();
			// 
			// FileName
			// 
			this.FileName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.FileName.Location = new System.Drawing.Point(88, 8);
			this.FileName.Name = "FileName";
			this.FileName.Size = new System.Drawing.Size(280, 20);
			this.FileName.TabIndex = 0;
			this.FileName.Text = "data.xml";
			// 
			// EvalButton
			// 
			this.EvalButton.Anchor = (System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right);
			this.EvalButton.Enabled = false;
			this.EvalButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.EvalButton.Location = new System.Drawing.Point(640, 40);
			this.EvalButton.Name = "EvalButton";
			this.EvalButton.Size = new System.Drawing.Size(88, 20);
			this.EvalButton.TabIndex = 4;
			this.EvalButton.Text = "Eval...";
			this.EvalButton.Click += new System.EventHandler(this.EvalButton_Click);
			// 
			// panel1
			// 
			this.panel1.Anchor = (((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
				| System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right);
			this.panel1.BackColor = System.Drawing.SystemColors.Control;
			this.panel1.Controls.AddRange(new System.Windows.Forms.Control[] {
																				 this.Results,
																				 this.splitter1,
																				 this.SourceFile});
			this.panel1.Location = new System.Drawing.Point(8, 72);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(720, 360);
			this.panel1.TabIndex = 2;
			// 
			// Results
			// 
			this.Results.AcceptsReturn = true;
			this.Results.AcceptsTab = true;
			this.Results.BackColor = System.Drawing.Color.White;
			this.Results.Dock = System.Windows.Forms.DockStyle.Fill;
			this.Results.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.Results.Location = new System.Drawing.Point(355, 0);
			this.Results.Multiline = true;
			this.Results.Name = "Results";
			this.Results.ReadOnly = true;
			this.Results.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.Results.Size = new System.Drawing.Size(365, 360);
			this.Results.TabIndex = 1;
			this.Results.Text = "<XPath Results>";
			// 
			// splitter1
			// 
			this.splitter1.Location = new System.Drawing.Point(352, 0);
			this.splitter1.Name = "splitter1";
			this.splitter1.Size = new System.Drawing.Size(3, 360);
			this.splitter1.TabIndex = 1;
			this.splitter1.TabStop = false;
			// 
			// SourceFile
			// 
			this.SourceFile.AcceptsReturn = true;
			this.SourceFile.AcceptsTab = true;
			this.SourceFile.BackColor = System.Drawing.SystemColors.Info;
			this.SourceFile.Cursor = System.Windows.Forms.Cursors.No;
			this.SourceFile.Dock = System.Windows.Forms.DockStyle.Left;
			this.SourceFile.Multiline = true;
			this.SourceFile.Name = "SourceFile";
			this.SourceFile.ReadOnly = true;
			this.SourceFile.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.SourceFile.Size = new System.Drawing.Size(352, 360);
			this.SourceFile.TabIndex = 0;
			this.SourceFile.Text = "<XML Source File>";
			this.SourceFile.WordWrap = false;
			// 
			// appStatus
			// 
			this.appStatus.Location = new System.Drawing.Point(0, 439);
			this.appStatus.Name = "appStatus";
			this.appStatus.Size = new System.Drawing.Size(736, 22);
			this.appStatus.TabIndex = 3;
			this.appStatus.Text = "Ready";
			// 
			// XPathExpression
			// 
			this.XPathExpression.Anchor = ((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right);
			this.XPathExpression.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.XPathExpression.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.XPathExpression.Location = new System.Drawing.Point(88, 40);
			this.XPathExpression.Name = "XPathExpression";
			this.XPathExpression.Size = new System.Drawing.Size(544, 20);
			this.XPathExpression.TabIndex = 2;
			this.XPathExpression.Text = "/MyDataSet/NorthwindEmployees";
			// 
			// label1
			// 
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label1.Location = new System.Drawing.Point(0, 8);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(72, 23);
			this.label1.TabIndex = 5;
			this.label1.Text = "XML Source";
			this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// LoadButton
			// 
			this.LoadButton.Anchor = (System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right);
			this.LoadButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.LoadButton.Location = new System.Drawing.Point(640, 8);
			this.LoadButton.Name = "LoadButton";
			this.LoadButton.Size = new System.Drawing.Size(88, 20);
			this.LoadButton.TabIndex = 3;
			this.LoadButton.Text = "Load...";
			this.LoadButton.Click += new System.EventHandler(this.LoadButton_Click);
			// 
			// ContextNode
			// 
			this.ContextNode.Anchor = ((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right);
			this.ContextNode.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.ContextNode.Location = new System.Drawing.Point(464, 8);
			this.ContextNode.Name = "ContextNode";
			this.ContextNode.Size = new System.Drawing.Size(168, 20);
			this.ContextNode.TabIndex = 1;
			this.ContextNode.Text = "MyDataSet";
			// 
			// label2
			// 
			this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label2.Location = new System.Drawing.Point(376, 8);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(80, 23);
			this.label2.TabIndex = 8;
			this.label2.Text = "Context Node ";
			this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// label3
			// 
			this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.label3.Location = new System.Drawing.Point(0, 40);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(72, 23);
			this.label3.TabIndex = 9;
			this.label3.Text = "Expression";
			this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(736, 461);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.label3,
																		  this.label2,
																		  this.ContextNode,
																		  this.LoadButton,
																		  this.label1,
																		  this.XPathExpression,
																		  this.appStatus,
																		  this.panel1,
																		  this.EvalButton,
																		  this.FileName});
			this.MinimumSize = new System.Drawing.Size(712, 488);
			this.Name = "Form1";
			this.Text = "XPath Evaluator";
			this.panel1.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}


		#region My Functions

		// **********************************************************************
		// Refresh the UI with the results of the XPath expression
		private void LoadButton_Click(object sender, System.EventArgs e)
		{
			LoadDocument(FileName.Text);	
			EvalButton.Enabled = true;
		}
		// **********************************************************************

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
			catch {}
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
			foreach(XmlNode n in nodes)
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
				foreach(XmlAttribute a in rootNode.Attributes)
					writer.WriteAttributeString(a.Name, a.Value);

				// Write any child nodes
				foreach(XmlNode n in rootNode.ChildNodes)
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
