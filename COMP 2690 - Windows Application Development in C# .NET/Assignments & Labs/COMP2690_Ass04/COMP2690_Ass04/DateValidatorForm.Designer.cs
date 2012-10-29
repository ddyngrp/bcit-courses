namespace COMP2690_Ass04
{
    partial class DateValidatorForm
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
            this.btnCheckDate = new System.Windows.Forms.Button();
            this.txtYear = new System.Windows.Forms.TextBox();
            this.txtDay = new System.Windows.Forms.TextBox();
            this.txtMonth = new System.Windows.Forms.TextBox();
            this.lblYear = new System.Windows.Forms.Label();
            this.lblMonth = new System.Windows.Forms.Label();
            this.lblDay = new System.Windows.Forms.Label();
            this.lblValidation = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnCheckDate
            // 
            this.btnCheckDate.Location = new System.Drawing.Point(167, 84);
            this.btnCheckDate.Name = "btnCheckDate";
            this.btnCheckDate.Size = new System.Drawing.Size(83, 23);
            this.btnCheckDate.TabIndex = 3;
            this.btnCheckDate.Text = "&Check Date";
            this.btnCheckDate.UseVisualStyleBackColor = true;
            this.btnCheckDate.Click += new System.EventHandler(this.btnCheckDate_Click);
            // 
            // txtYear
            // 
            this.txtYear.Location = new System.Drawing.Point(19, 34);
            this.txtYear.Name = "txtYear";
            this.txtYear.Size = new System.Drawing.Size(70, 20);
            this.txtYear.TabIndex = 0;
            // 
            // txtDay
            // 
            this.txtDay.Location = new System.Drawing.Point(171, 34);
            this.txtDay.Name = "txtDay";
            this.txtDay.Size = new System.Drawing.Size(70, 20);
            this.txtDay.TabIndex = 2;
            // 
            // txtMonth
            // 
            this.txtMonth.Location = new System.Drawing.Point(95, 34);
            this.txtMonth.Name = "txtMonth";
            this.txtMonth.Size = new System.Drawing.Size(70, 20);
            this.txtMonth.TabIndex = 1;
            // 
            // lblYear
            // 
            this.lblYear.AutoSize = true;
            this.lblYear.Location = new System.Drawing.Point(16, 18);
            this.lblYear.Name = "lblYear";
            this.lblYear.Size = new System.Drawing.Size(29, 13);
            this.lblYear.TabIndex = 0;
            this.lblYear.Text = "&Year";
            // 
            // lblMonth
            // 
            this.lblMonth.AutoSize = true;
            this.lblMonth.Location = new System.Drawing.Point(92, 18);
            this.lblMonth.Name = "lblMonth";
            this.lblMonth.Size = new System.Drawing.Size(37, 13);
            this.lblMonth.TabIndex = 1;
            this.lblMonth.Text = "&Month";
            // 
            // lblDay
            // 
            this.lblDay.AutoSize = true;
            this.lblDay.Location = new System.Drawing.Point(168, 18);
            this.lblDay.Name = "lblDay";
            this.lblDay.Size = new System.Drawing.Size(26, 13);
            this.lblDay.TabIndex = 2;
            this.lblDay.Text = "&Day";
            // 
            // lblValidation
            // 
            this.lblValidation.AutoSize = true;
            this.lblValidation.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblValidation.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblValidation.Location = new System.Drawing.Point(19, 73);
            this.lblValidation.Name = "lblValidation";
            this.lblValidation.Size = new System.Drawing.Size(0, 24);
            this.lblValidation.TabIndex = 4;
            // 
            // DateValidator
            // 
            this.AcceptButton = this.btnCheckDate;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(262, 119);
            this.Controls.Add(this.lblValidation);
            this.Controls.Add(this.lblDay);
            this.Controls.Add(this.lblMonth);
            this.Controls.Add(this.lblYear);
            this.Controls.Add(this.txtMonth);
            this.Controls.Add(this.txtDay);
            this.Controls.Add(this.txtYear);
            this.Controls.Add(this.btnCheckDate);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "DateValidator";
            this.Text = "Date Validator";
            this.Load += new System.EventHandler(this.DateValidator_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnCheckDate;
        private System.Windows.Forms.TextBox txtYear;
        private System.Windows.Forms.TextBox txtDay;
        private System.Windows.Forms.TextBox txtMonth;
        private System.Windows.Forms.Label lblYear;
        private System.Windows.Forms.Label lblMonth;
        private System.Windows.Forms.Label lblDay;
        private System.Windows.Forms.Label lblValidation;
    }
}