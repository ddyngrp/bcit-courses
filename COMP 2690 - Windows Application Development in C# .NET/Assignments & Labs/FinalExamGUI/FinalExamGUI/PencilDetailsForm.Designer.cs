namespace FinalExamGUI
{
    partial class PencilDetailsForm
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
            this.txtLeadType = new System.Windows.Forms.TextBox();
            this.txtLeadCapacity = new System.Windows.Forms.TextBox();
            this.txtColour = new System.Windows.Forms.TextBox();
            this.lblLeadType = new System.Windows.Forms.Label();
            this.lblLeadCapacity = new System.Windows.Forms.Label();
            this.lblColour = new System.Windows.Forms.Label();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOK = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // txtLeadType
            // 
            this.txtLeadType.Location = new System.Drawing.Point(97, 17);
            this.txtLeadType.Name = "txtLeadType";
            this.txtLeadType.Size = new System.Drawing.Size(128, 20);
            this.txtLeadType.TabIndex = 1;
            // 
            // txtLeadCapacity
            // 
            this.txtLeadCapacity.Location = new System.Drawing.Point(97, 43);
            this.txtLeadCapacity.Name = "txtLeadCapacity";
            this.txtLeadCapacity.Size = new System.Drawing.Size(128, 20);
            this.txtLeadCapacity.TabIndex = 3;
            // 
            // txtColour
            // 
            this.txtColour.Location = new System.Drawing.Point(97, 69);
            this.txtColour.Name = "txtColour";
            this.txtColour.Size = new System.Drawing.Size(128, 20);
            this.txtColour.TabIndex = 5;
            // 
            // lblLeadType
            // 
            this.lblLeadType.AutoSize = true;
            this.lblLeadType.Location = new System.Drawing.Point(12, 20);
            this.lblLeadType.Name = "lblLeadType";
            this.lblLeadType.Size = new System.Drawing.Size(61, 13);
            this.lblLeadType.TabIndex = 0;
            this.lblLeadType.Text = "&Lead Type:";
            // 
            // lblLeadCapacity
            // 
            this.lblLeadCapacity.AutoSize = true;
            this.lblLeadCapacity.Location = new System.Drawing.Point(12, 46);
            this.lblLeadCapacity.Name = "lblLeadCapacity";
            this.lblLeadCapacity.Size = new System.Drawing.Size(78, 13);
            this.lblLeadCapacity.TabIndex = 2;
            this.lblLeadCapacity.Text = "L&ead Capacity:";
            // 
            // lblColour
            // 
            this.lblColour.AutoSize = true;
            this.lblColour.Location = new System.Drawing.Point(12, 72);
            this.lblColour.Name = "lblColour";
            this.lblColour.Size = new System.Drawing.Size(40, 13);
            this.lblColour.TabIndex = 4;
            this.lblColour.Text = "&Colour:";
            // 
            // btnCancel
            // 
            this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btnCancel.Location = new System.Drawing.Point(150, 113);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 6;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(69, 113);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 7;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // PencilDetailsForm
            // 
            this.AcceptButton = this.btnOK;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.ClientSize = new System.Drawing.Size(237, 148);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.lblColour);
            this.Controls.Add(this.lblLeadCapacity);
            this.Controls.Add(this.lblLeadType);
            this.Controls.Add(this.txtColour);
            this.Controls.Add(this.txtLeadCapacity);
            this.Controls.Add(this.txtLeadType);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "PencilDetailsForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Mechanical Pencil Details";
            this.Load += new System.EventHandler(this.PencilDetailsForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtLeadType;
        private System.Windows.Forms.TextBox txtLeadCapacity;
        private System.Windows.Forms.TextBox txtColour;
        private System.Windows.Forms.Label lblLeadType;
        private System.Windows.Forms.Label lblLeadCapacity;
        private System.Windows.Forms.Label lblColour;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOK;
    }
}