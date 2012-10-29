namespace COMP2690_Ass06
{
    partial class TransactionHistoryForm
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
            this.btnClose = new System.Windows.Forms.Button();
            this.chkShowDetails = new System.Windows.Forms.CheckBox();
            this.txtTransactionHistory = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // btnClose
            // 
            this.btnClose.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnClose.Location = new System.Drawing.Point(322, 468);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(75, 23);
            this.btnClose.TabIndex = 1;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // chkShowDetails
            // 
            this.chkShowDetails.AutoSize = true;
            this.chkShowDetails.Location = new System.Drawing.Point(12, 472);
            this.chkShowDetails.Name = "chkShowDetails";
            this.chkShowDetails.Size = new System.Drawing.Size(88, 17);
            this.chkShowDetails.TabIndex = 0;
            this.chkShowDetails.Text = "Show &Details";
            this.chkShowDetails.UseVisualStyleBackColor = true;
            this.chkShowDetails.CheckedChanged += new System.EventHandler(this.chkShowDetails_CheckedChanged);
            // 
            // txtTransactionHistory
            // 
            this.txtTransactionHistory.Dock = System.Windows.Forms.DockStyle.Top;
            this.txtTransactionHistory.Font = new System.Drawing.Font("Courier New", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtTransactionHistory.Location = new System.Drawing.Point(0, 0);
            this.txtTransactionHistory.Multiline = true;
            this.txtTransactionHistory.Name = "txtTransactionHistory";
            this.txtTransactionHistory.Size = new System.Drawing.Size(409, 448);
            this.txtTransactionHistory.TabIndex = 2;
            // 
            // TransactionHistoryForm
            // 
            this.AcceptButton = this.btnClose;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnClose;
            this.ClientSize = new System.Drawing.Size(409, 503);
            this.Controls.Add(this.txtTransactionHistory);
            this.Controls.Add(this.chkShowDetails);
            this.Controls.Add(this.btnClose);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "TransactionHistoryForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Transaction History";
            this.Load += new System.EventHandler(this.TransactionHistoryForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.CheckBox chkShowDetails;
        private System.Windows.Forms.TextBox txtTransactionHistory;
    }
}