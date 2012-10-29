namespace XMLdotNET.XMLDataReader
{
    partial class TestXMLDataReader
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
            this.ResultsListBox = new System.Windows.Forms.ListBox();
            this.ButtonLoadData = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // ResultsListBox
            // 
            this.ResultsListBox.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ResultsListBox.ItemHeight = 14;
            this.ResultsListBox.Location = new System.Drawing.Point(8, 11);
            this.ResultsListBox.Name = "ResultsListBox";
            this.ResultsListBox.Size = new System.Drawing.Size(736, 116);
            this.ResultsListBox.TabIndex = 3;
            // 
            // ButtonLoadData
            // 
            this.ButtonLoadData.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ButtonLoadData.Location = new System.Drawing.Point(656, 147);
            this.ButtonLoadData.Name = "ButtonLoadData";
            this.ButtonLoadData.Size = new System.Drawing.Size(80, 23);
            this.ButtonLoadData.TabIndex = 2;
            this.ButtonLoadData.Text = "Load Data...";
            this.ButtonLoadData.Click += new System.EventHandler(this.ButtonLoadData_Click);
            // 
            // TestXMLDataReader
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(752, 181);
            this.Controls.Add(this.ResultsListBox);
            this.Controls.Add(this.ButtonLoadData);
            this.Name = "TestXMLDataReader";
            this.Text = "Reading OLE DB result sets as XML ...";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox ResultsListBox;
        private System.Windows.Forms.Button ButtonLoadData;
    }
}