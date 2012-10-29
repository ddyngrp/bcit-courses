namespace XMLdotNET
{
    partial class frmXML
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
            this.btnLab1 = new System.Windows.Forms.Button();
            this.btnLab2 = new System.Windows.Forms.Button();
            this.lblDisplay = new System.Windows.Forms.Label();
            this.btnLab3 = new System.Windows.Forms.Button();
            this.btnLab4 = new System.Windows.Forms.Button();
            this.btnLab5 = new System.Windows.Forms.Button();
            this.btnLab6 = new System.Windows.Forms.Button();
            this.btnLab7 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnLab1
            // 
            this.btnLab1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnLab1.Location = new System.Drawing.Point(47, 12);
            this.btnLab1.Name = "btnLab1";
            this.btnLab1.Size = new System.Drawing.Size(434, 23);
            this.btnLab1.TabIndex = 0;
            this.btnLab1.Text = "Creating a New XMLDocument from Scratch ";
            this.btnLab1.UseVisualStyleBackColor = true;
            this.btnLab1.Click += new System.EventHandler(this.btnLab1_Click);
            // 
            // btnLab2
            // 
            this.btnLab2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnLab2.Location = new System.Drawing.Point(47, 36);
            this.btnLab2.Name = "btnLab2";
            this.btnLab2.Size = new System.Drawing.Size(434, 23);
            this.btnLab2.TabIndex = 2;
            this.btnLab2.Text = "Parsing XMLDocument Using the DOM";
            this.btnLab2.UseVisualStyleBackColor = true;
            this.btnLab2.Click += new System.EventHandler(this.btnLab2_Click);
            // 
            // lblDisplay
            // 
            this.lblDisplay.AutoSize = true;
            this.lblDisplay.Location = new System.Drawing.Point(55, 197);
            this.lblDisplay.Name = "lblDisplay";
            this.lblDisplay.Size = new System.Drawing.Size(0, 13);
            this.lblDisplay.TabIndex = 1;
            // 
            // btnLab3
            // 
            this.btnLab3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnLab3.Location = new System.Drawing.Point(47, 60);
            this.btnLab3.Name = "btnLab3";
            this.btnLab3.Size = new System.Drawing.Size(434, 23);
            this.btnLab3.TabIndex = 3;
            this.btnLab3.Text = "Parsing XMLDocument Using the XPathNavigator";
            this.btnLab3.UseVisualStyleBackColor = true;
            this.btnLab3.Click += new System.EventHandler(this.btnLab3_Click);
            // 
            // btnLab4
            // 
            this.btnLab4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnLab4.Location = new System.Drawing.Point(47, 84);
            this.btnLab4.Name = "btnLab4";
            this.btnLab4.Size = new System.Drawing.Size(434, 23);
            this.btnLab4.TabIndex = 4;
            this.btnLab4.Text = "Searching the XmlDocument Using the DOM";
            this.btnLab4.UseVisualStyleBackColor = true;
            this.btnLab4.Click += new System.EventHandler(this.btnLab4_Click);
            // 
            // btnLab5
            // 
            this.btnLab5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnLab5.Location = new System.Drawing.Point(47, 109);
            this.btnLab5.Name = "btnLab5";
            this.btnLab5.Size = new System.Drawing.Size(434, 23);
            this.btnLab5.TabIndex = 5;
            this.btnLab5.Text = "Searching the XmlDocument Using the DOM (SelectSingleNode)";
            this.btnLab5.UseVisualStyleBackColor = true;
            this.btnLab5.Click += new System.EventHandler(this.btnLab5_Click);
            // 
            // btnLab6
            // 
            this.btnLab6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnLab6.Location = new System.Drawing.Point(47, 133);
            this.btnLab6.Name = "btnLab6";
            this.btnLab6.Size = new System.Drawing.Size(434, 23);
            this.btnLab6.TabIndex = 6;
            this.btnLab6.Text = "Searching the XmlDocument Using the DOM (GetElementByTagName)";
            this.btnLab6.UseVisualStyleBackColor = true;
            this.btnLab6.Click += new System.EventHandler(this.btnLab6_Click);
            // 
            // btnLab7
            // 
            this.btnLab7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnLab7.Location = new System.Drawing.Point(47, 159);
            this.btnLab7.Name = "btnLab7";
            this.btnLab7.Size = new System.Drawing.Size(434, 23);
            this.btnLab7.TabIndex = 7;
            this.btnLab7.Text = "Searching the XmlDocument Using the DOM (SelectNodes)";
            this.btnLab7.UseVisualStyleBackColor = true;
            this.btnLab7.Click += new System.EventHandler(this.btnLab7_Click);
            // 
            // frmXML
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(652, 498);
            this.Controls.Add(this.btnLab7);
            this.Controls.Add(this.btnLab6);
            this.Controls.Add(this.btnLab5);
            this.Controls.Add(this.btnLab4);
            this.Controls.Add(this.btnLab3);
            this.Controls.Add(this.btnLab2);
            this.Controls.Add(this.lblDisplay);
            this.Controls.Add(this.btnLab1);
            this.Name = "frmXML";
            this.Text = "XML Processing";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnLab1;
        private System.Windows.Forms.Button btnLab2;
        private System.Windows.Forms.Label lblDisplay;
        private System.Windows.Forms.Button btnLab3;
        private System.Windows.Forms.Button btnLab4;
        private System.Windows.Forms.Button btnLab5;
        private System.Windows.Forms.Button btnLab6;
        private System.Windows.Forms.Button btnLab7;
    }
}

