namespace ADOdotNET.Factory
{
    partial class CallDb
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
            this.ProviderNameBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.ConnectionStringBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.CommandTextBox = new System.Windows.Forms.TextBox();
            this.btnRun = new System.Windows.Forms.Button();
            this.Results = new System.Windows.Forms.DataGrid();
            ((System.ComponentModel.ISupportInitialize)(this.Results)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(54, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Provider";
            // 
            // ProviderNameBox
            // 
            this.ProviderNameBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ProviderNameBox.Location = new System.Drawing.Point(137, 24);
            this.ProviderNameBox.Name = "ProviderNameBox";
            this.ProviderNameBox.Size = new System.Drawing.Size(427, 20);
            this.ProviderNameBox.TabIndex = 1;
            this.ProviderNameBox.Text = "System.Data.SqlClient";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(12, 67);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(108, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Connection String";
            // 
            // ConnectionStringBox
            // 
            this.ConnectionStringBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ConnectionStringBox.Location = new System.Drawing.Point(137, 63);
            this.ConnectionStringBox.Name = "ConnectionStringBox";
            this.ConnectionStringBox.Size = new System.Drawing.Size(427, 20);
            this.ConnectionStringBox.TabIndex = 3;
            this.ConnectionStringBox.Text = "SERVER=www.j2ee.ca;DATABASE=northwind;UID=aspx;Password=aspx;";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(12, 105);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(90, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Command Text";
            // 
            // CommandTextBox
            // 
            this.CommandTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CommandTextBox.Location = new System.Drawing.Point(137, 101);
            this.CommandTextBox.Name = "CommandTextBox";
            this.CommandTextBox.Size = new System.Drawing.Size(427, 20);
            this.CommandTextBox.TabIndex = 5;
            this.CommandTextBox.Text = "SELECT TOP 15 customerid, companyname FROM customers";
            // 
            // btnRun
            // 
            this.btnRun.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnRun.Location = new System.Drawing.Point(15, 159);
            this.btnRun.Name = "btnRun";
            this.btnRun.Size = new System.Drawing.Size(75, 23);
            this.btnRun.TabIndex = 6;
            this.btnRun.Text = "Run";
            this.btnRun.UseVisualStyleBackColor = true;
            this.btnRun.Click += new System.EventHandler(this.btnRun_Click);
            // 
            // Results
            // 
            this.Results.DataMember = "";
            this.Results.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.Results.Location = new System.Drawing.Point(15, 204);
            this.Results.Name = "Results";
            this.Results.Size = new System.Drawing.Size(424, 218);
            this.Results.TabIndex = 7;
            // 
            // CallDb
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(672, 480);
            this.Controls.Add(this.Results);
            this.Controls.Add(this.btnRun);
            this.Controls.Add(this.CommandTextBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.ConnectionStringBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.ProviderNameBox);
            this.Controls.Add(this.label1);
            this.Name = "CallDb";
            this.Text = "CallDb";
            ((System.ComponentModel.ISupportInitialize)(this.Results)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox ProviderNameBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox ConnectionStringBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox CommandTextBox;
        private System.Windows.Forms.Button btnRun;
        private System.Windows.Forms.DataGrid Results;
    }
}