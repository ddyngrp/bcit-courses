namespace Multithreaded_π_Calculator
{
    partial class PiCalculator
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
            this.label1 = new System.Windows.Forms.Label();
            this._calcButton = new System.Windows.Forms.Button();
            this._digits = new System.Windows.Forms.NumericUpDown();
            this._pi = new System.Windows.Forms.TextBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            ((System.ComponentModel.ISupportInitialize)(this._digits)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Digits of Pi:";
            // 
            // _calcButton
            // 
            this._calcButton.Location = new System.Drawing.Point(173, 9);
            this._calcButton.Name = "_calcButton";
            this._calcButton.Size = new System.Drawing.Size(75, 23);
            this._calcButton.TabIndex = 1;
            this._calcButton.Text = "Calculate";
            this._calcButton.UseVisualStyleBackColor = true;
            this._calcButton.Click += new System.EventHandler(this._calcButton_Click);
            // 
            // _digits
            // 
            this._digits.Location = new System.Drawing.Point(79, 10);
            this._digits.Maximum = new decimal(new int[] {
            -727379968,
            232,
            0,
            0});
            this._digits.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this._digits.Name = "_digits";
            this._digits.Size = new System.Drawing.Size(82, 20);
            this._digits.TabIndex = 0;
            this._digits.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // _pi
            // 
            this._pi.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this._pi.BackColor = System.Drawing.SystemColors.Window;
            this._pi.Location = new System.Drawing.Point(12, 38);
            this._pi.Multiline = true;
            this._pi.Name = "_pi";
            this._pi.ReadOnly = true;
            this._pi.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this._pi.Size = new System.Drawing.Size(260, 199);
            this._pi.TabIndex = 2;
            // 
            // progressBar1
            // 
            this.progressBar1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.progressBar1.Location = new System.Drawing.Point(13, 240);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(259, 18);
            this.progressBar1.Step = 1;
            this.progressBar1.TabIndex = 3;
            // 
            // PiCalculator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this._pi);
            this.Controls.Add(this._digits);
            this.Controls.Add(this._calcButton);
            this.Controls.Add(this.label1);
            this.Name = "PiCalculator";
            this.Text = "Calculate π";
            ((System.ComponentModel.ISupportInitialize)(this._digits)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button _calcButton;
        private System.Windows.Forms.NumericUpDown _digits;
        private System.Windows.Forms.TextBox _pi;
        private System.Windows.Forms.ProgressBar progressBar1;
    }
}

