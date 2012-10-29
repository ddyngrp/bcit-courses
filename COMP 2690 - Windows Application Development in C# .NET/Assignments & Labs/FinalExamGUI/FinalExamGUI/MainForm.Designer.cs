namespace FinalExamGUI
{
    partial class MainForm
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
            this.lstWritingUtensils = new System.Windows.Forms.ListBox();
            this.lblItems = new System.Windows.Forms.Label();
            this.lblItemDetails = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // lstWritingUtensils
            // 
            this.lstWritingUtensils.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.lstWritingUtensils.FormattingEnabled = true;
            this.lstWritingUtensils.IntegralHeight = false;
            this.lstWritingUtensils.Location = new System.Drawing.Point(0, 12);
            this.lstWritingUtensils.Name = "lstWritingUtensils";
            this.lstWritingUtensils.Size = new System.Drawing.Size(292, 235);
            this.lstWritingUtensils.TabIndex = 0;
            this.lstWritingUtensils.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.lstWritingUtensils_MouseDoubleClick);
            this.lstWritingUtensils.SelectedIndexChanged += new System.EventHandler(this.lstWritingUtensils_SelectedIndexChanged);
            // 
            // lblItems
            // 
            this.lblItems.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lblItems.AutoSize = true;
            this.lblItems.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblItems.Location = new System.Drawing.Point(4, 255);
            this.lblItems.Name = "lblItems";
            this.lblItems.Size = new System.Drawing.Size(52, 13);
            this.lblItems.TabIndex = 1;
            this.lblItems.Text = "Items: 6";
            // 
            // lblItemDetails
            // 
            this.lblItemDetails.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lblItemDetails.AutoSize = true;
            this.lblItemDetails.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblItemDetails.Location = new System.Drawing.Point(4, 276);
            this.lblItemDetails.Name = "lblItemDetails";
            this.lblItemDetails.Size = new System.Drawing.Size(226, 13);
            this.lblItemDetails.TabIndex = 2;
            this.lblItemDetails.Text = "Blues: 2, Reds: 1, Blacks: 2, Others: 1";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 296);
            this.Controls.Add(this.lblItemDetails);
            this.Controls.Add(this.lblItems);
            this.Controls.Add(this.lstWritingUtensils);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "COMP 2690 Final Exam";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lstWritingUtensils;
        private System.Windows.Forms.Label lblItems;
        private System.Windows.Forms.Label lblItemDetails;
    }
}

