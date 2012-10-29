namespace XMLdotNET.DiffGram
{
    partial class Edit
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
            this.ButtonRowError = new System.Windows.Forms.Button();
            this.ButtonClear = new System.Windows.Forms.Button();
            this.ErrorMessage = new System.Windows.Forms.TextBox();
            this.ButtonSetError = new System.Windows.Forms.Button();
            this.ErrorColumn = new System.Windows.Forms.TextBox();
            this.ButtonDelete = new System.Windows.Forms.Button();
            this.ButtonReject = new System.Windows.Forms.Button();
            this.ButtonSave = new System.Windows.Forms.Button();
            this.CurrentData = new System.Windows.Forms.DataGrid();
            ((System.ComponentModel.ISupportInitialize)(this.CurrentData)).BeginInit();
            this.SuspendLayout();
            // 
            // ButtonRowError
            // 
            this.ButtonRowError.Location = new System.Drawing.Point(232, 30);
            this.ButtonRowError.Name = "ButtonRowError";
            this.ButtonRowError.Size = new System.Drawing.Size(80, 24);
            this.ButtonRowError.TabIndex = 17;
            this.ButtonRowError.Text = "Set RowError";
            this.ButtonRowError.Click += new System.EventHandler(this.ButtonRowError_Click);
            // 
            // ButtonClear
            // 
            this.ButtonClear.Location = new System.Drawing.Point(272, 6);
            this.ButtonClear.Name = "ButtonClear";
            this.ButtonClear.Size = new System.Drawing.Size(40, 24);
            this.ButtonClear.TabIndex = 16;
            this.ButtonClear.Text = "Clear";
            this.ButtonClear.Click += new System.EventHandler(this.ButtonClear_Click);
            // 
            // ErrorMessage
            // 
            this.ErrorMessage.Location = new System.Drawing.Point(128, 30);
            this.ErrorMessage.Name = "ErrorMessage";
            this.ErrorMessage.Size = new System.Drawing.Size(88, 20);
            this.ErrorMessage.TabIndex = 15;
            this.ErrorMessage.Text = "!!! Error !!!";
            // 
            // ButtonSetError
            // 
            this.ButtonSetError.Location = new System.Drawing.Point(232, 6);
            this.ButtonSetError.Name = "ButtonSetError";
            this.ButtonSetError.Size = new System.Drawing.Size(40, 24);
            this.ButtonSetError.TabIndex = 14;
            this.ButtonSetError.Text = "Set";
            this.ButtonSetError.Click += new System.EventHandler(this.ButtonSetError_Click);
            // 
            // ErrorColumn
            // 
            this.ErrorColumn.Location = new System.Drawing.Point(128, 6);
            this.ErrorColumn.Name = "ErrorColumn";
            this.ErrorColumn.Size = new System.Drawing.Size(88, 20);
            this.ErrorColumn.TabIndex = 13;
            this.ErrorColumn.Text = "employeeid";
            // 
            // ButtonDelete
            // 
            this.ButtonDelete.Enabled = false;
            this.ButtonDelete.Location = new System.Drawing.Point(16, 14);
            this.ButtonDelete.Name = "ButtonDelete";
            this.ButtonDelete.Size = new System.Drawing.Size(96, 24);
            this.ButtonDelete.TabIndex = 12;
            this.ButtonDelete.Text = "Delete row";
            this.ButtonDelete.Click += new System.EventHandler(this.ButtonDelete_Click);
            // 
            // ButtonReject
            // 
            this.ButtonReject.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.ButtonReject.Location = new System.Drawing.Point(512, 14);
            this.ButtonReject.Name = "ButtonReject";
            this.ButtonReject.Size = new System.Drawing.Size(96, 24);
            this.ButtonReject.TabIndex = 11;
            this.ButtonReject.Text = "Reject all";
            this.ButtonReject.Click += new System.EventHandler(this.ButtonReject_Click);
            // 
            // ButtonSave
            // 
            this.ButtonSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.ButtonSave.Location = new System.Drawing.Point(408, 14);
            this.ButtonSave.Name = "ButtonSave";
            this.ButtonSave.Size = new System.Drawing.Size(96, 24);
            this.ButtonSave.TabIndex = 10;
            this.ButtonSave.Text = "Save all";
            this.ButtonSave.Click += new System.EventHandler(this.ButtonSave_Click);
            // 
            // CurrentData
            // 
            this.CurrentData.AlternatingBackColor = System.Drawing.Color.GhostWhite;
            this.CurrentData.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.CurrentData.BackColor = System.Drawing.Color.GhostWhite;
            this.CurrentData.BackgroundColor = System.Drawing.Color.Lavender;
            this.CurrentData.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.CurrentData.CaptionBackColor = System.Drawing.Color.RoyalBlue;
            this.CurrentData.CaptionForeColor = System.Drawing.Color.White;
            this.CurrentData.CaptionText = "Edit the current data";
            this.CurrentData.CausesValidation = false;
            this.CurrentData.DataMember = "";
            this.CurrentData.FlatMode = true;
            this.CurrentData.Font = new System.Drawing.Font("Tahoma", 8F);
            this.CurrentData.ForeColor = System.Drawing.Color.MidnightBlue;
            this.CurrentData.GridLineColor = System.Drawing.Color.RoyalBlue;
            this.CurrentData.HeaderBackColor = System.Drawing.Color.MidnightBlue;
            this.CurrentData.HeaderFont = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
            this.CurrentData.HeaderForeColor = System.Drawing.Color.Lavender;
            this.CurrentData.LinkColor = System.Drawing.Color.Teal;
            this.CurrentData.Location = new System.Drawing.Point(8, 54);
            this.CurrentData.Name = "CurrentData";
            this.CurrentData.ParentRowsBackColor = System.Drawing.Color.Lavender;
            this.CurrentData.ParentRowsForeColor = System.Drawing.Color.MidnightBlue;
            this.CurrentData.SelectionBackColor = System.Drawing.Color.Teal;
            this.CurrentData.SelectionForeColor = System.Drawing.Color.PaleGreen;
            this.CurrentData.Size = new System.Drawing.Size(600, 280);
            this.CurrentData.TabIndex = 9;
            // 
            // Edit
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(616, 341);
            this.Controls.Add(this.ButtonRowError);
            this.Controls.Add(this.ButtonClear);
            this.Controls.Add(this.ErrorMessage);
            this.Controls.Add(this.ButtonSetError);
            this.Controls.Add(this.ErrorColumn);
            this.Controls.Add(this.ButtonDelete);
            this.Controls.Add(this.ButtonReject);
            this.Controls.Add(this.ButtonSave);
            this.Controls.Add(this.CurrentData);
            this.Name = "Edit";
            this.Text = "Edit";
            ((System.ComponentModel.ISupportInitialize)(this.CurrentData)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button ButtonRowError;
        private System.Windows.Forms.Button ButtonClear;
        private System.Windows.Forms.TextBox ErrorMessage;
        private System.Windows.Forms.Button ButtonSetError;
        private System.Windows.Forms.TextBox ErrorColumn;
        private System.Windows.Forms.Button ButtonDelete;
        private System.Windows.Forms.Button ButtonReject;
        private System.Windows.Forms.Button ButtonSave;
        private System.Windows.Forms.DataGrid CurrentData;
    }
}