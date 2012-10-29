namespace SectionThree
{
    partial class KeyDemoForm
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
            this.charLabel = new System.Windows.Forms.Label();
            this.keyInfoLabel = new System.Windows.Forms.Label();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.SuspendLayout();
            // 
            // charLabel
            // 
            this.charLabel.AutoSize = true;
            this.charLabel.Location = new System.Drawing.Point(124, 32);
            this.charLabel.Name = "charLabel";
            this.charLabel.Size = new System.Drawing.Size(63, 13);
            this.charLabel.TabIndex = 0;
            this.charLabel.Text = "Press a Key";
            // 
            // keyInfoLabel
            // 
            this.keyInfoLabel.AutoSize = true;
            this.keyInfoLabel.Location = new System.Drawing.Point(124, 73);
            this.keyInfoLabel.Name = "keyInfoLabel";
            this.keyInfoLabel.Size = new System.Drawing.Size(46, 13);
            this.keyInfoLabel.TabIndex = 1;
            this.keyInfoLabel.Text = "Key Info";
            // 
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(106, 169);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(104, 45);
            this.trackBar1.TabIndex = 2;
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.Location = new System.Drawing.Point(213, 92);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.ShowCheckBox = true;
            this.dateTimePicker1.Size = new System.Drawing.Size(200, 20);
            this.dateTimePicker1.TabIndex = 3;
            // 
            // KeyDemoForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(425, 266);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.keyInfoLabel);
            this.Controls.Add(this.charLabel);
            this.Name = "KeyDemoForm";
            this.Text = "KeyDemoForm";
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.KeyDemoForm_KeyPress);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.KeyDemoForm_KeyUp);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.KeyDemoForm_KeyDown);

            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label charLabel;
        private System.Windows.Forms.Label keyInfoLabel;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
    }
}