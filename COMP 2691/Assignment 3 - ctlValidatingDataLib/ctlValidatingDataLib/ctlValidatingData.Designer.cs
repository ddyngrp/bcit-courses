namespace ctlValidatingDataLib
{
    partial class ctlValidatingData
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

        #region Component Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBoxCtl = new System.Windows.Forms.GroupBox();
            this.lblMMYY = new System.Windows.Forms.Label();
            this.lblValidTo = new System.Windows.Forms.Label();
            this.txtValidTo = new System.Windows.Forms.TextBox();
            this.lblAmount = new System.Windows.Forms.Label();
            this.txtAmount = new System.Windows.Forms.TextBox();
            this.lblIssue = new System.Windows.Forms.Label();
            this.txtIssue = new System.Windows.Forms.TextBox();
            this.lblValidFrom = new System.Windows.Forms.Label();
            this.txtValidFrom = new System.Windows.Forms.TextBox();
            this.lblCreditCard = new System.Windows.Forms.Label();
            this.txtCreditCard = new System.Windows.Forms.TextBox();
            this.lblEmail = new System.Windows.Forms.Label();
            this.txtEmail = new System.Windows.Forms.TextBox();
            this.lblLastName = new System.Windows.Forms.Label();
            this.txtLastName = new System.Windows.Forms.TextBox();
            this.lblFirstName = new System.Windows.Forms.Label();
            this.txtFirstName = new System.Windows.Forms.TextBox();
            this.groupBoxCtl.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxCtl
            // 
            this.groupBoxCtl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBoxCtl.Controls.Add(this.lblMMYY);
            this.groupBoxCtl.Controls.Add(this.lblValidTo);
            this.groupBoxCtl.Controls.Add(this.txtValidTo);
            this.groupBoxCtl.Controls.Add(this.lblAmount);
            this.groupBoxCtl.Controls.Add(this.txtAmount);
            this.groupBoxCtl.Controls.Add(this.lblIssue);
            this.groupBoxCtl.Controls.Add(this.txtIssue);
            this.groupBoxCtl.Controls.Add(this.lblValidFrom);
            this.groupBoxCtl.Controls.Add(this.txtValidFrom);
            this.groupBoxCtl.Controls.Add(this.lblCreditCard);
            this.groupBoxCtl.Controls.Add(this.txtCreditCard);
            this.groupBoxCtl.Controls.Add(this.lblEmail);
            this.groupBoxCtl.Controls.Add(this.txtEmail);
            this.groupBoxCtl.Controls.Add(this.lblLastName);
            this.groupBoxCtl.Controls.Add(this.txtLastName);
            this.groupBoxCtl.Controls.Add(this.lblFirstName);
            this.groupBoxCtl.Controls.Add(this.txtFirstName);
            this.groupBoxCtl.Location = new System.Drawing.Point(8, 3);
            this.groupBoxCtl.Name = "groupBoxCtl";
            this.groupBoxCtl.Size = new System.Drawing.Size(394, 208);
            this.groupBoxCtl.TabIndex = 0;
            this.groupBoxCtl.TabStop = false;
            // 
            // lblMMYY
            // 
            this.lblMMYY.AutoSize = true;
            this.lblMMYY.Location = new System.Drawing.Point(335, 126);
            this.lblMMYY.Name = "lblMMYY";
            this.lblMMYY.Size = new System.Drawing.Size(50, 13);
            this.lblMMYY.TabIndex = 7;
            this.lblMMYY.Text = "(MM/YY)";
            // 
            // lblValidTo
            // 
            this.lblValidTo.AutoSize = true;
            this.lblValidTo.Location = new System.Drawing.Point(202, 126);
            this.lblValidTo.Name = "lblValidTo";
            this.lblValidTo.Size = new System.Drawing.Size(49, 13);
            this.lblValidTo.TabIndex = 6;
            this.lblValidTo.Text = "Valid To:";
            // 
            // txtValidTo
            // 
            this.txtValidTo.Location = new System.Drawing.Point(257, 123);
            this.txtValidTo.Name = "txtValidTo";
            this.txtValidTo.Size = new System.Drawing.Size(72, 20);
            this.txtValidTo.TabIndex = 6;
            this.txtValidTo.Validating += new System.ComponentModel.CancelEventHandler(this.txtValidTo_Validating);
            // 
            // lblAmount
            // 
            this.lblAmount.AutoSize = true;
            this.lblAmount.Location = new System.Drawing.Point(13, 178);
            this.lblAmount.Name = "lblAmount";
            this.lblAmount.Size = new System.Drawing.Size(46, 13);
            this.lblAmount.TabIndex = 9;
            this.lblAmount.Text = "Amount:";
            // 
            // txtAmount
            // 
            this.txtAmount.Location = new System.Drawing.Point(121, 175);
            this.txtAmount.Name = "txtAmount";
            this.txtAmount.Size = new System.Drawing.Size(72, 20);
            this.txtAmount.TabIndex = 9;
            this.txtAmount.Validating += new System.ComponentModel.CancelEventHandler(this.txtAmount_Validating);
            // 
            // lblIssue
            // 
            this.lblIssue.AutoSize = true;
            this.lblIssue.Location = new System.Drawing.Point(13, 152);
            this.lblIssue.Name = "lblIssue";
            this.lblIssue.Size = new System.Drawing.Size(75, 13);
            this.lblIssue.TabIndex = 8;
            this.lblIssue.Text = "Issue Number:";
            // 
            // txtIssue
            // 
            this.txtIssue.Location = new System.Drawing.Point(121, 149);
            this.txtIssue.Name = "txtIssue";
            this.txtIssue.Size = new System.Drawing.Size(72, 20);
            this.txtIssue.TabIndex = 8;
            // 
            // lblValidFrom
            // 
            this.lblValidFrom.AutoSize = true;
            this.lblValidFrom.Location = new System.Drawing.Point(13, 126);
            this.lblValidFrom.Name = "lblValidFrom";
            this.lblValidFrom.Size = new System.Drawing.Size(59, 13);
            this.lblValidFrom.TabIndex = 5;
            this.lblValidFrom.Text = "Valid From:";
            // 
            // txtValidFrom
            // 
            this.txtValidFrom.Location = new System.Drawing.Point(121, 123);
            this.txtValidFrom.Name = "txtValidFrom";
            this.txtValidFrom.Size = new System.Drawing.Size(72, 20);
            this.txtValidFrom.TabIndex = 5;
            // 
            // lblCreditCard
            // 
            this.lblCreditCard.AutoSize = true;
            this.lblCreditCard.Location = new System.Drawing.Point(13, 100);
            this.lblCreditCard.Name = "lblCreditCard";
            this.lblCreditCard.Size = new System.Drawing.Size(102, 13);
            this.lblCreditCard.TabIndex = 4;
            this.lblCreditCard.Text = "Credit Card Number:";
            // 
            // txtCreditCard
            // 
            this.txtCreditCard.Location = new System.Drawing.Point(121, 97);
            this.txtCreditCard.Name = "txtCreditCard";
            this.txtCreditCard.Size = new System.Drawing.Size(208, 20);
            this.txtCreditCard.TabIndex = 4;
            this.txtCreditCard.Validating += new System.ComponentModel.CancelEventHandler(this.txtCreditCard_Validating);
            // 
            // lblEmail
            // 
            this.lblEmail.AutoSize = true;
            this.lblEmail.Location = new System.Drawing.Point(13, 74);
            this.lblEmail.Name = "lblEmail";
            this.lblEmail.Size = new System.Drawing.Size(76, 13);
            this.lblEmail.TabIndex = 3;
            this.lblEmail.Text = "Email Address:";
            // 
            // txtEmail
            // 
            this.txtEmail.Location = new System.Drawing.Point(121, 71);
            this.txtEmail.Name = "txtEmail";
            this.txtEmail.Size = new System.Drawing.Size(208, 20);
            this.txtEmail.TabIndex = 3;
            this.txtEmail.Validating += new System.ComponentModel.CancelEventHandler(this.txtEmail_Validating);
            // 
            // lblLastName
            // 
            this.lblLastName.AutoSize = true;
            this.lblLastName.Location = new System.Drawing.Point(13, 48);
            this.lblLastName.Name = "lblLastName";
            this.lblLastName.Size = new System.Drawing.Size(61, 13);
            this.lblLastName.TabIndex = 2;
            this.lblLastName.Text = "Last Name:";
            // 
            // txtLastName
            // 
            this.txtLastName.Location = new System.Drawing.Point(121, 45);
            this.txtLastName.Name = "txtLastName";
            this.txtLastName.Size = new System.Drawing.Size(208, 20);
            this.txtLastName.TabIndex = 2;
            // 
            // lblFirstName
            // 
            this.lblFirstName.AutoSize = true;
            this.lblFirstName.Location = new System.Drawing.Point(13, 22);
            this.lblFirstName.Name = "lblFirstName";
            this.lblFirstName.Size = new System.Drawing.Size(60, 13);
            this.lblFirstName.TabIndex = 1;
            this.lblFirstName.Text = "First Name:";
            // 
            // txtFirstName
            // 
            this.txtFirstName.Location = new System.Drawing.Point(121, 19);
            this.txtFirstName.Name = "txtFirstName";
            this.txtFirstName.Size = new System.Drawing.Size(208, 20);
            this.txtFirstName.TabIndex = 1;
            // 
            // ctlValidatingData
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBoxCtl);
            this.Name = "ctlValidatingData";
            this.Size = new System.Drawing.Size(411, 220);
            this.groupBoxCtl.ResumeLayout(false);
            this.groupBoxCtl.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxCtl;
        private System.Windows.Forms.Label lblAmount;
        private System.Windows.Forms.TextBox txtAmount;
        private System.Windows.Forms.Label lblIssue;
        private System.Windows.Forms.TextBox txtIssue;
        private System.Windows.Forms.Label lblValidFrom;
        private System.Windows.Forms.TextBox txtValidFrom;
        private System.Windows.Forms.Label lblCreditCard;
        private System.Windows.Forms.TextBox txtCreditCard;
        private System.Windows.Forms.Label lblEmail;
        private System.Windows.Forms.TextBox txtEmail;
        private System.Windows.Forms.Label lblLastName;
        private System.Windows.Forms.TextBox txtLastName;
        private System.Windows.Forms.Label lblFirstName;
        private System.Windows.Forms.TextBox txtFirstName;
        private System.Windows.Forms.Label lblMMYY;
        private System.Windows.Forms.Label lblValidTo;
        private System.Windows.Forms.TextBox txtValidTo;

    }
}
