namespace Class5_ADO
{
    partial class frmConnection
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
            this.btnGetData = new System.Windows.Forms.Button();
            this.btnConnectionStringfromConfig = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnGetData
            // 
            this.btnGetData.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnGetData.Location = new System.Drawing.Point(49, 32);
            this.btnGetData.Name = "btnGetData";
            this.btnGetData.Size = new System.Drawing.Size(188, 23);
            this.btnGetData.TabIndex = 0;
            this.btnGetData.Text = "Get Data";
            this.btnGetData.UseVisualStyleBackColor = true;
            this.btnGetData.Click += new System.EventHandler(this.btnGetData_Click);
            // 
            // btnConnectionStringfromConfig
            // 
            this.btnConnectionStringfromConfig.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnConnectionStringfromConfig.Location = new System.Drawing.Point(49, 73);
            this.btnConnectionStringfromConfig.Name = "btnConnectionStringfromConfig";
            this.btnConnectionStringfromConfig.Size = new System.Drawing.Size(188, 23);
            this.btnConnectionStringfromConfig.TabIndex = 1;
            this.btnConnectionStringfromConfig.Text = "ConnectionString from Config";
            this.btnConnectionStringfromConfig.UseVisualStyleBackColor = true;
            this.btnConnectionStringfromConfig.Click += new System.EventHandler(this.btnConnectionStringfromConfig_Click);
            // 
            // frmConnection
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(293, 128);
            this.Controls.Add(this.btnConnectionStringfromConfig);
            this.Controls.Add(this.btnGetData);
            this.Name = "frmConnection";
            this.Text = "Connection String Examples";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnGetData;
        private System.Windows.Forms.Button btnConnectionStringfromConfig;
    }
}

