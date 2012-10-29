namespace ADOdotNET.Async
{
    partial class Parallel
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
            this.CustomerList = new System.Windows.Forms.ComboBox();
            this.QueryButton = new System.Windows.Forms.Button();
            this.Info = new System.Windows.Forms.Label();
            this.MInfo = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(44, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(116, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Pick up a customer";
            // 
            // CustomerList
            // 
            this.CustomerList.FormattingEnabled = true;
            this.CustomerList.Location = new System.Drawing.Point(47, 56);
            this.CustomerList.Name = "CustomerList";
            this.CustomerList.Size = new System.Drawing.Size(202, 21);
            this.CustomerList.TabIndex = 1;
            // 
            // QueryButton
            // 
            this.QueryButton.Location = new System.Drawing.Point(267, 54);
            this.QueryButton.Name = "QueryButton";
            this.QueryButton.Size = new System.Drawing.Size(75, 23);
            this.QueryButton.TabIndex = 2;
            this.QueryButton.Text = "Go get data";
            this.QueryButton.UseVisualStyleBackColor = true;
            this.QueryButton.Click += new System.EventHandler(this.QueryButton_Click);
            // 
            // Info
            // 
            this.Info.AutoSize = true;
            this.Info.Location = new System.Drawing.Point(17, 26);
            this.Info.Name = "Info";
            this.Info.Size = new System.Drawing.Size(25, 13);
            this.Info.TabIndex = 4;
            this.Info.Text = "Info";
            // 
            // MInfo
            // 
            this.MInfo.AutoSize = true;
            this.MInfo.Location = new System.Drawing.Point(17, 26);
            this.MInfo.Name = "MInfo";
            this.MInfo.Size = new System.Drawing.Size(25, 13);
            this.MInfo.TabIndex = 5;
            this.MInfo.Text = "Info";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.Info);
            this.groupBox1.Location = new System.Drawing.Point(47, 116);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(287, 100);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Company Information";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.MInfo);
            this.groupBox2.Location = new System.Drawing.Point(340, 116);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(277, 100);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Customer Order History";
            // 
            // Parallel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(655, 263);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.QueryButton);
            this.Controls.Add(this.CustomerList);
            this.Controls.Add(this.label1);
            this.Name = "Parallel";
            this.Text = "Parallel";
            this.Load += new System.EventHandler(this.Parallel_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox CustomerList;
        private System.Windows.Forms.Button QueryButton;
        private System.Windows.Forms.Label Info;
        private System.Windows.Forms.Label MInfo;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
    }
}