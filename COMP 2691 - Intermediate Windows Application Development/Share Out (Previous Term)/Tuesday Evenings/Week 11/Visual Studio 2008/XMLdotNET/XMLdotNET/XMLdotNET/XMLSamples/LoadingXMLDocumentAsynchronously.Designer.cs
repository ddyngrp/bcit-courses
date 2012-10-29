namespace XMLdotNET.XMLSamples
{
    partial class LoadingXMLDocumentAsynchronously
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
            this.InputFile = new System.Windows.Forms.TextBox();
            this.btnLoad = new System.Windows.Forms.Button();
            this.Output = new System.Windows.Forms.TextBox();
            this.statusBar = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusBar.SuspendLayout();
            this.SuspendLayout();
            // 
            // InputFile
            // 
            this.InputFile.Location = new System.Drawing.Point(12, 12);
            this.InputFile.Name = "InputFile";
            this.InputFile.Size = new System.Drawing.Size(422, 20);
            this.InputFile.TabIndex = 0;
            this.InputFile.Text = "HugeXmlDocument.xml";
            // 
            // btnLoad
            // 
            this.btnLoad.Location = new System.Drawing.Point(440, 12);
            this.btnLoad.Name = "btnLoad";
            this.btnLoad.Size = new System.Drawing.Size(113, 20);
            this.btnLoad.TabIndex = 1;
            this.btnLoad.Text = "Load...";
            this.btnLoad.UseVisualStyleBackColor = true;
            this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
            // 
            // Output
            // 
            this.Output.Location = new System.Drawing.Point(12, 48);
            this.Output.Multiline = true;
            this.Output.Name = "Output";
            this.Output.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.Output.Size = new System.Drawing.Size(541, 308);
            this.Output.TabIndex = 2;
            // 
            // statusBar
            // 
            this.statusBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusBar.Location = new System.Drawing.Point(0, 361);
            this.statusBar.Name = "statusBar";
            this.statusBar.Size = new System.Drawing.Size(562, 22);
            this.statusBar.TabIndex = 3;
            this.statusBar.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(38, 17);
            this.toolStripStatusLabel1.Text = "Ready";
            // 
            // LoadingXMLDocumentAsynchronously
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(562, 383);
            this.Controls.Add(this.statusBar);
            this.Controls.Add(this.Output);
            this.Controls.Add(this.btnLoad);
            this.Controls.Add(this.InputFile);
            this.Name = "LoadingXMLDocumentAsynchronously";
            this.Text = "Loading XML Document Asynchronously";
            this.statusBar.ResumeLayout(false);
            this.statusBar.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox InputFile;
        private System.Windows.Forms.Button btnLoad;
        private System.Windows.Forms.TextBox Output;
        private System.Windows.Forms.StatusStrip statusBar;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
    }
}