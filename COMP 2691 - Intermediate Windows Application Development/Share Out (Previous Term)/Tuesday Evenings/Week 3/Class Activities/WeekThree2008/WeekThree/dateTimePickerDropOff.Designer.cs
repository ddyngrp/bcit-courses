namespace WeekThree
{
    partial class dateTimePickerDropOff
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
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.DropOffDate = new System.Windows.Forms.Label();
            this.outputLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.Location = new System.Drawing.Point(90, 78);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(200, 20);
            this.dateTimePicker1.TabIndex = 0;
            this.dateTimePicker1.ValueChanged += new System.EventHandler(this.dateTimePicker1_ValueChanged);
            // 
            // DropOffDate
            // 
            this.DropOffDate.AutoSize = true;
            this.DropOffDate.Location = new System.Drawing.Point(87, 53);
            this.DropOffDate.Name = "DropOffDate";
            this.DropOffDate.Size = new System.Drawing.Size(73, 13);
            this.DropOffDate.TabIndex = 1;
            this.DropOffDate.Text = "Drop Off Date";
            // 
            // outputLabel
            // 
            this.outputLabel.AutoSize = true;
            this.outputLabel.Location = new System.Drawing.Point(87, 142);
            this.outputLabel.Name = "outputLabel";
            this.outputLabel.Size = new System.Drawing.Size(0, 13);
            this.outputLabel.TabIndex = 2;
            // 
            // dateTimePickerDropOff
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(356, 306);
            this.Controls.Add(this.outputLabel);
            this.Controls.Add(this.DropOffDate);
            this.Controls.Add(this.dateTimePicker1);
            this.Name = "dateTimePickerDropOff";
            this.Text = "dateTimePickerDropOff";
            this.Load += new System.EventHandler(this.dateTimePickerDropOff_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.Label DropOffDate;
        private System.Windows.Forms.Label outputLabel;
    }
}