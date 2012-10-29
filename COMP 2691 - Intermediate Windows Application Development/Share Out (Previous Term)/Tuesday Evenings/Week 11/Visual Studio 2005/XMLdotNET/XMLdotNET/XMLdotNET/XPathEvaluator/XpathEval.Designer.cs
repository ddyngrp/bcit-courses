namespace XMLdotNET.XPathEvaluator
{
    partial class XpathEval
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.ContextNode = new System.Windows.Forms.TextBox();
            this.LoadButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.XPathExpression = new System.Windows.Forms.TextBox();
            this.EvalButton = new System.Windows.Forms.Button();
            this.FileName = new System.Windows.Forms.TextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.SourceFile = new System.Windows.Forms.TextBox();
            this.Results = new System.Windows.Forms.TextBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.appStatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.panel1.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label3
            // 
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(1, 44);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(72, 23);
            this.label3.TabIndex = 17;
            this.label3.Text = "Expression";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // label2
            // 
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(377, 12);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(80, 23);
            this.label2.TabIndex = 16;
            this.label2.Text = "Context Node ";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ContextNode
            // 
            this.ContextNode.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.ContextNode.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ContextNode.Location = new System.Drawing.Point(465, 12);
            this.ContextNode.Name = "ContextNode";
            this.ContextNode.Size = new System.Drawing.Size(168, 20);
            this.ContextNode.TabIndex = 11;
            this.ContextNode.Text = "MyDataSet";
            // 
            // LoadButton
            // 
            this.LoadButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.LoadButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.LoadButton.Location = new System.Drawing.Point(641, 11);
            this.LoadButton.Name = "LoadButton";
            this.LoadButton.Size = new System.Drawing.Size(88, 23);
            this.LoadButton.TabIndex = 13;
            this.LoadButton.Text = "Load...";
            this.LoadButton.Click += new System.EventHandler(this.LoadButton_Click);
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(1, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(72, 23);
            this.label1.TabIndex = 15;
            this.label1.Text = "XML Source";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // XPathExpression
            // 
            this.XPathExpression.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.XPathExpression.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.XPathExpression.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.XPathExpression.Location = new System.Drawing.Point(89, 44);
            this.XPathExpression.Name = "XPathExpression";
            this.XPathExpression.Size = new System.Drawing.Size(544, 20);
            this.XPathExpression.TabIndex = 12;
            this.XPathExpression.Text = "/MyDataSet/NorthwindEmployees";
            // 
            // EvalButton
            // 
            this.EvalButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.EvalButton.Enabled = false;
            this.EvalButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.EvalButton.Location = new System.Drawing.Point(641, 43);
            this.EvalButton.Name = "EvalButton";
            this.EvalButton.Size = new System.Drawing.Size(88, 23);
            this.EvalButton.TabIndex = 14;
            this.EvalButton.Text = "Eval...";
            this.EvalButton.Click += new System.EventHandler(this.EvalButton_Click);
            // 
            // FileName
            // 
            this.FileName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.FileName.Location = new System.Drawing.Point(89, 12);
            this.FileName.Name = "FileName";
            this.FileName.Size = new System.Drawing.Size(280, 20);
            this.FileName.TabIndex = 10;
            this.FileName.Text = "data.xml";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.splitContainer1);
            this.panel1.Location = new System.Drawing.Point(9, 76);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(720, 360);
            this.panel1.TabIndex = 18;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.SourceFile);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.Results);
            this.splitContainer1.Size = new System.Drawing.Size(720, 360);
            this.splitContainer1.SplitterDistance = 277;
            this.splitContainer1.TabIndex = 0;
            // 
            // SourceFile
            // 
            this.SourceFile.AcceptsReturn = true;
            this.SourceFile.AcceptsTab = true;
            this.SourceFile.BackColor = System.Drawing.SystemColors.Info;
            this.SourceFile.Cursor = System.Windows.Forms.Cursors.No;
            this.SourceFile.Dock = System.Windows.Forms.DockStyle.Left;
            this.SourceFile.Location = new System.Drawing.Point(0, 0);
            this.SourceFile.Multiline = true;
            this.SourceFile.Name = "SourceFile";
            this.SourceFile.ReadOnly = true;
            this.SourceFile.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.SourceFile.Size = new System.Drawing.Size(275, 360);
            this.SourceFile.TabIndex = 1;
            this.SourceFile.Text = "<XML Source File>";
            this.SourceFile.WordWrap = false;
            // 
            // Results
            // 
            this.Results.AcceptsReturn = true;
            this.Results.AcceptsTab = true;
            this.Results.BackColor = System.Drawing.Color.White;
            this.Results.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Results.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Results.Location = new System.Drawing.Point(0, 0);
            this.Results.Multiline = true;
            this.Results.Name = "Results";
            this.Results.ReadOnly = true;
            this.Results.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.Results.Size = new System.Drawing.Size(439, 360);
            this.Results.TabIndex = 2;
            this.Results.Text = "<XPath Results>";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.appStatus});
            this.statusStrip1.Location = new System.Drawing.Point(0, 439);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(736, 22);
            this.statusStrip1.TabIndex = 19;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // appStatus
            // 
            this.appStatus.Name = "appStatus";
            this.appStatus.Size = new System.Drawing.Size(38, 17);
            this.appStatus.Text = "Ready";
            // 
            // XpathEval
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(736, 461);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.ContextNode);
            this.Controls.Add(this.LoadButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.XPathExpression);
            this.Controls.Add(this.EvalButton);
            this.Controls.Add(this.FileName);
            this.Name = "XpathEval";
            this.Text = "XPath Evaluator";
            this.panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            this.splitContainer1.ResumeLayout(false);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox ContextNode;
        private System.Windows.Forms.Button LoadButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox XPathExpression;
        private System.Windows.Forms.Button EvalButton;
        private System.Windows.Forms.TextBox FileName;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TextBox SourceFile;
        private System.Windows.Forms.TextBox Results;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel appStatus;


    }
}