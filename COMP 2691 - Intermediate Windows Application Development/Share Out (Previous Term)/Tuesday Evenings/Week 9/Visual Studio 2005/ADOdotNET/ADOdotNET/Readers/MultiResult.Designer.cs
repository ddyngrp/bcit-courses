namespace ADOdotNET.Readers
{
    partial class MultiResult
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
            this.Query = new System.Windows.Forms.TextBox();
            this.btnGoGetData = new System.Windows.Forms.Button();
            this.Results = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(733, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Type any T-SQL query you wish against the Northwind database. The first two colum" +
                "ns of any result set will be displayed below.";
            // 
            // Query
            // 
            this.Query.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Query.Location = new System.Drawing.Point(15, 40);
            this.Query.Name = "Query";
            this.Query.Size = new System.Drawing.Size(644, 20);
            this.Query.TabIndex = 1;
            this.Query.Text = "SELECT TOP 10 * FROM customers;SELECT lastname, firstname FROM employees";
            // 
            // btnGoGetData
            // 
            this.btnGoGetData.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnGoGetData.Location = new System.Drawing.Point(15, 66);
            this.btnGoGetData.Name = "btnGoGetData";
            this.btnGoGetData.Size = new System.Drawing.Size(97, 23);
            this.btnGoGetData.TabIndex = 2;
            this.btnGoGetData.Text = "Go get data";
            this.btnGoGetData.UseVisualStyleBackColor = true;
            this.btnGoGetData.Click += new System.EventHandler(this.btnGoGetData_Click);
            // 
            // Results
            // 
            this.Results.AutoSize = true;
            this.Results.Location = new System.Drawing.Point(21, 105);
            this.Results.Name = "Results";
            this.Results.Size = new System.Drawing.Size(0, 13);
            this.Results.TabIndex = 3;
            // 
            // MultiResult
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(764, 423);
            this.Controls.Add(this.Results);
            this.Controls.Add(this.btnGoGetData);
            this.Controls.Add(this.Query);
            this.Controls.Add(this.label1);
            this.Name = "MultiResult";
            this.Text = "MultiResult";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox Query;
        private System.Windows.Forms.Button btnGoGetData;
        private System.Windows.Forms.Label Results;
    }
}