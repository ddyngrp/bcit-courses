namespace WeekThree
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
            this.SuspendLayout();
            // 
            // charLabel
            // 
            this.charLabel.AutoSize = true;
            this.charLabel.Location = new System.Drawing.Point(74, 26);
            this.charLabel.Name = "charLabel";
            this.charLabel.Size = new System.Drawing.Size(96, 13);
            this.charLabel.TabIndex = 0;
            this.charLabel.Text = "Please press a key";
            // 
            // keyInfoLabel
            // 
            this.keyInfoLabel.AutoSize = true;
            this.keyInfoLabel.Location = new System.Drawing.Point(74, 74);
            this.keyInfoLabel.Name = "keyInfoLabel";
            this.keyInfoLabel.Size = new System.Drawing.Size(0, 13);
            this.keyInfoLabel.TabIndex = 1;
            // 
            // KeyDemoForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(292, 266);
            this.Controls.Add(this.keyInfoLabel);
            this.Controls.Add(this.charLabel);
            this.Name = "KeyDemoForm";
            this.Text = "KeyDemoForm";
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.KeyDemoForm_KeyPress);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.KeyDemoForm_KeyUp);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.KeyDemoForm_KeyDown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label charLabel;
        private System.Windows.Forms.Label keyInfoLabel;
    }
}