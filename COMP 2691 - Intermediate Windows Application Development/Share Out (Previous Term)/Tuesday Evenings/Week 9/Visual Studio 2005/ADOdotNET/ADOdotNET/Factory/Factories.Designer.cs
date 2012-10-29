namespace ADOdotNET.Factory
{
    partial class Factories
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
            this.provList = new System.Windows.Forms.DataGrid();
            ((System.ComponentModel.ISupportInitialize)(this.provList)).BeginInit();
            this.SuspendLayout();
            // 
            // provList
            // 
            this.provList.DataMember = "";
            this.provList.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.provList.Location = new System.Drawing.Point(21, 12);
            this.provList.Name = "provList";
            this.provList.Size = new System.Drawing.Size(767, 159);
            this.provList.TabIndex = 0;
            // 
            // Factories
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 193);
            this.Controls.Add(this.provList);
            this.Name = "Factories";
            this.Text = "Factories";
            this.Load += new System.EventHandler(this.Factories_Load);
            ((System.ComponentModel.ISupportInitialize)(this.provList)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGrid provList;
    }
}