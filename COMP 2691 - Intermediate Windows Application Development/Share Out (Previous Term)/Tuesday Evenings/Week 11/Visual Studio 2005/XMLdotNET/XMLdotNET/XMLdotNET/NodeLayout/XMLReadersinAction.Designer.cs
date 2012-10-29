namespace XMLdotNET.NodeLayout
{
    partial class XMLReadersinAction
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
            this.OutputConsole = new System.Windows.Forms.TextBox();
            this.ButtonLoad = new System.Windows.Forms.Button();
            this.FileName = new System.Windows.Forms.TextBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // OutputConsole
            // 
            this.OutputConsole.AcceptsReturn = true;
            this.OutputConsole.AcceptsTab = true;
            this.OutputConsole.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.OutputConsole.Font = new System.Drawing.Font("Lucida Console", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.OutputConsole.Location = new System.Drawing.Point(12, 50);
            this.OutputConsole.Multiline = true;
            this.OutputConsole.Name = "OutputConsole";
            this.OutputConsole.ReadOnly = true;
            this.OutputConsole.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.OutputConsole.Size = new System.Drawing.Size(512, 184);
            this.OutputConsole.TabIndex = 11;
            this.OutputConsole.WordWrap = false;
            // 
            // ButtonLoad
            // 
            this.ButtonLoad.Location = new System.Drawing.Point(428, 10);
            this.ButtonLoad.Name = "ButtonLoad";
            this.ButtonLoad.Size = new System.Drawing.Size(88, 24);
            this.ButtonLoad.TabIndex = 10;
            this.ButtonLoad.Text = "Go";
            this.ButtonLoad.Click += new System.EventHandler(this.ButtonLoad_Click);
            // 
            // FileName
            // 
            this.FileName.Location = new System.Drawing.Point(12, 12);
            this.FileName.Name = "FileName";
            this.FileName.Size = new System.Drawing.Size(408, 20);
            this.FileName.TabIndex = 9;
            this.FileName.Text = "data.xml";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 273);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(528, 22);
            this.statusStrip1.TabIndex = 12;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(38, 17);
            this.toolStripStatusLabel1.Text = "Ready";
            // 
            // XMLReadersinAction
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(528, 295);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.OutputConsole);
            this.Controls.Add(this.ButtonLoad);
            this.Controls.Add(this.FileName);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "XMLReadersinAction";
            this.Text = "XMLReaders in Action";
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        internal System.Windows.Forms.TextBox OutputConsole;
        internal System.Windows.Forms.Button ButtonLoad;
        internal System.Windows.Forms.TextBox FileName;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
    }
}