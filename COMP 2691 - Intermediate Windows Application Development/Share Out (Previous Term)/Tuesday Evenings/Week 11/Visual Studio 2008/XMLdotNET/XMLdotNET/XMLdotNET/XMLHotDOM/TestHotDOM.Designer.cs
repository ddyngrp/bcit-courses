namespace XMLdotNET.XMLHotDOM
{
    partial class TestHotDOM
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
            this.OutputBox = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.PendingChanges = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // OutputBox
            // 
            this.OutputBox.AcceptsReturn = true;
            this.OutputBox.AcceptsTab = true;
            this.OutputBox.Font = new System.Drawing.Font("Courier New", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.OutputBox.Location = new System.Drawing.Point(21, 42);
            this.OutputBox.Multiline = true;
            this.OutputBox.Name = "OutputBox";
            this.OutputBox.ReadOnly = true;
            this.OutputBox.Size = new System.Drawing.Size(448, 192);
            this.OutputBox.TabIndex = 3;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(357, 10);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(112, 24);
            this.button1.TabIndex = 2;
            this.button1.Text = "Load...";
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // PendingChanges
            // 
            this.PendingChanges.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PendingChanges.Location = new System.Drawing.Point(18, 9);
            this.PendingChanges.Name = "PendingChanges";
            this.PendingChanges.Size = new System.Drawing.Size(192, 23);
            this.PendingChanges.TabIndex = 4;
            // 
            // TestHotDOM
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(482, 242);
            this.Controls.Add(this.PendingChanges);
            this.Controls.Add(this.OutputBox);
            this.Controls.Add(this.button1);
            this.Name = "TestHotDOM";
            this.Text = "HotDOM Testing...";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox OutputBox;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label PendingChanges;
    }
}