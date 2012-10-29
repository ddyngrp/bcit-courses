namespace COMP2690_Ass06
{
    partial class MainForum
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
            this.components = new System.ComponentModel.Container();
            this.lstAccounts = new System.Windows.Forms.ListBox();
            this.btnDeposit = new System.Windows.Forms.Button();
            this.btnWithdraw = new System.Windows.Forms.Button();
            this.btnBalance = new System.Windows.Forms.Button();
            this.btnTransfer = new System.Windows.Forms.Button();
            this.grpAction = new System.Windows.Forms.GroupBox();
            this.lblAccounts = new System.Windows.Forms.Label();
            this.btnTransactionHistory = new System.Windows.Forms.Button();
            this.transactionTimer = new System.Windows.Forms.Timer(this.components);
            this.grpAction.SuspendLayout();
            this.SuspendLayout();
            // 
            // lstAccounts
            // 
            this.lstAccounts.FormattingEnabled = true;
            this.lstAccounts.IntegralHeight = false;
            this.lstAccounts.Location = new System.Drawing.Point(15, 25);
            this.lstAccounts.Name = "lstAccounts";
            this.lstAccounts.Size = new System.Drawing.Size(120, 122);
            this.lstAccounts.TabIndex = 1;
            this.lstAccounts.SelectedIndexChanged += new System.EventHandler(this.lstAccounts_SelectedIndexChanged);
            // 
            // btnDeposit
            // 
            this.btnDeposit.Location = new System.Drawing.Point(6, 19);
            this.btnDeposit.Name = "btnDeposit";
            this.btnDeposit.Size = new System.Drawing.Size(103, 23);
            this.btnDeposit.TabIndex = 0;
            this.btnDeposit.Text = "Deposit";
            this.btnDeposit.UseVisualStyleBackColor = true;
            this.btnDeposit.Click += new System.EventHandler(this.btnDeposit_Click);
            // 
            // btnWithdraw
            // 
            this.btnWithdraw.Location = new System.Drawing.Point(6, 48);
            this.btnWithdraw.Name = "btnWithdraw";
            this.btnWithdraw.Size = new System.Drawing.Size(103, 23);
            this.btnWithdraw.TabIndex = 1;
            this.btnWithdraw.Text = "Withdraw";
            this.btnWithdraw.UseVisualStyleBackColor = true;
            this.btnWithdraw.Click += new System.EventHandler(this.btnWithdraw_Click);
            // 
            // btnBalance
            // 
            this.btnBalance.Location = new System.Drawing.Point(6, 106);
            this.btnBalance.Name = "btnBalance";
            this.btnBalance.Size = new System.Drawing.Size(103, 23);
            this.btnBalance.TabIndex = 3;
            this.btnBalance.Text = "Balance";
            this.btnBalance.UseVisualStyleBackColor = true;
            this.btnBalance.Click += new System.EventHandler(this.btnBalance_Click);
            // 
            // btnTransfer
            // 
            this.btnTransfer.Location = new System.Drawing.Point(6, 77);
            this.btnTransfer.Name = "btnTransfer";
            this.btnTransfer.Size = new System.Drawing.Size(103, 23);
            this.btnTransfer.TabIndex = 2;
            this.btnTransfer.Text = "Transfer";
            this.btnTransfer.UseVisualStyleBackColor = true;
            this.btnTransfer.Click += new System.EventHandler(this.btnTransfer_Click);
            // 
            // grpAction
            // 
            this.grpAction.Controls.Add(this.btnDeposit);
            this.grpAction.Controls.Add(this.btnTransfer);
            this.grpAction.Controls.Add(this.btnWithdraw);
            this.grpAction.Controls.Add(this.btnBalance);
            this.grpAction.Location = new System.Drawing.Point(141, 9);
            this.grpAction.Name = "grpAction";
            this.grpAction.Size = new System.Drawing.Size(115, 138);
            this.grpAction.TabIndex = 2;
            this.grpAction.TabStop = false;
            this.grpAction.Text = "Account Action";
            // 
            // lblAccounts
            // 
            this.lblAccounts.AutoSize = true;
            this.lblAccounts.Location = new System.Drawing.Point(12, 9);
            this.lblAccounts.Name = "lblAccounts";
            this.lblAccounts.Size = new System.Drawing.Size(52, 13);
            this.lblAccounts.TabIndex = 0;
            this.lblAccounts.Text = "&Accounts";
            // 
            // btnTransactionHistory
            // 
            this.btnTransactionHistory.Location = new System.Drawing.Point(73, 153);
            this.btnTransactionHistory.Name = "btnTransactionHistory";
            this.btnTransactionHistory.Size = new System.Drawing.Size(120, 23);
            this.btnTransactionHistory.TabIndex = 3;
            this.btnTransactionHistory.Text = "Transaction History";
            this.btnTransactionHistory.UseVisualStyleBackColor = true;
            this.btnTransactionHistory.Click += new System.EventHandler(this.btnTransactionHistory_Click);
            // 
            // transactionTimer
            // 
            this.transactionTimer.Enabled = true;
            this.transactionTimer.Interval = 5000;
            this.transactionTimer.Tick += new System.EventHandler(this.transactionTimer_Tick);
            // 
            // MainForum
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(269, 188);
            this.Controls.Add(this.btnTransactionHistory);
            this.Controls.Add(this.lblAccounts);
            this.Controls.Add(this.grpAction);
            this.Controls.Add(this.lstAccounts);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "MainForum";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Bank Machine";
            this.Load += new System.EventHandler(this.MainForum_Load);
            this.grpAction.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox lstAccounts;
        private System.Windows.Forms.Button btnDeposit;
        private System.Windows.Forms.Button btnWithdraw;
        private System.Windows.Forms.Button btnBalance;
        private System.Windows.Forms.Button btnTransfer;
        private System.Windows.Forms.GroupBox grpAction;
        private System.Windows.Forms.Label lblAccounts;
        private System.Windows.Forms.Button btnTransactionHistory;
        private System.Windows.Forms.Timer transactionTimer;
    }
}

