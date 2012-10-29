namespace WeekThree
{
    partial class LinkLabel
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
            this.driveLinkLabel = new System.Windows.Forms.LinkLabel();
            this.BCITlinkLabel = new System.Windows.Forms.LinkLabel();
            this.linkLabel3 = new System.Windows.Forms.LinkLabel();
            this.SuspendLayout();
            // 
            // driveLinkLabel
            // 
            this.driveLinkLabel.AutoSize = true;
            this.driveLinkLabel.Location = new System.Drawing.Point(45, 60);
            this.driveLinkLabel.Name = "driveLinkLabel";
            this.driveLinkLabel.Size = new System.Drawing.Size(22, 13);
            this.driveLinkLabel.TabIndex = 0;
            this.driveLinkLabel.TabStop = true;
            this.driveLinkLabel.Text = "C:\\";
            this.driveLinkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.driveLinkLabel_LinkClicked);
            // 
            // BCITlinkLabel
            // 
            this.BCITlinkLabel.AutoSize = true;
            this.BCITlinkLabel.Location = new System.Drawing.Point(45, 92);
            this.BCITlinkLabel.Name = "BCITlinkLabel";
            this.BCITlinkLabel.Size = new System.Drawing.Size(31, 13);
            this.BCITlinkLabel.TabIndex = 1;
            this.BCITlinkLabel.TabStop = true;
            this.BCITlinkLabel.Text = "BCIT";
            this.BCITlinkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.BCITlinkLabel_LinkClicked);
            // 
            // linkLabel3
            // 
            this.linkLabel3.AutoSize = true;
            this.linkLabel3.Location = new System.Drawing.Point(45, 132);
            this.linkLabel3.Name = "linkLabel3";
            this.linkLabel3.Size = new System.Drawing.Size(90, 13);
            this.linkLabel3.TabIndex = 2;
            this.linkLabel3.TabStop = true;
            this.linkLabel3.Text = "NotepadlinkLabel";
            this.linkLabel3.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel3_LinkClicked);
            // 
            // LinkLabel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 266);
            this.Controls.Add(this.linkLabel3);
            this.Controls.Add(this.BCITlinkLabel);
            this.Controls.Add(this.driveLinkLabel);
            this.Name = "LinkLabel";
            this.Text = "LinkLabel";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.LinkLabel driveLinkLabel;
        private System.Windows.Forms.LinkLabel BCITlinkLabel;
        private System.Windows.Forms.LinkLabel linkLabel3;
    }
}