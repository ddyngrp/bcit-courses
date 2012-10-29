namespace GUIConceptsPart2.ADONetSamples.ConnString
{
    partial class FromConfig
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
            this.btnGoGetData = new System.Windows.Forms.Button();
            this.CustomerList = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // btnGoGetData
            // 
            this.btnGoGetData.Location = new System.Drawing.Point(36, 27);
            this.btnGoGetData.Name = "btnGoGetData";
            this.btnGoGetData.Size = new System.Drawing.Size(107, 23);
            this.btnGoGetData.TabIndex = 0;
            this.btnGoGetData.Text = "Go get data...";
            this.btnGoGetData.UseVisualStyleBackColor = true;
            this.btnGoGetData.Click += new System.EventHandler(this.btnGoGetData_Click);
            // 
            // CustomerList
            // 
            this.CustomerList.FormattingEnabled = true;
            this.CustomerList.Location = new System.Drawing.Point(36, 70);
            this.CustomerList.Name = "CustomerList";
            this.CustomerList.Size = new System.Drawing.Size(395, 95);
            this.CustomerList.TabIndex = 1;
            // 
            // FromConfig
            // 
            this.ClientSize = new System.Drawing.Size(524, 266);
            this.Controls.Add(this.CustomerList);
            this.Controls.Add(this.btnGoGetData);
            this.Name = "FromConfig";
            this.Text = "From Config";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnGoGetData;
        private System.Windows.Forms.ListBox CustomerList;
    }
}