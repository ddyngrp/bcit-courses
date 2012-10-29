namespace XMLdotNET.ReadXML
{
    partial class ReadXML
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
            this.FinalSchema = new System.Windows.Forms.TextBox();
            this.ModeUsed = new System.Windows.Forms.Label();
            this.ReadMode = new System.Windows.Forms.ComboBox();
            this.grid = new System.Windows.Forms.DataGrid();
            this.Data = new System.Windows.Forms.TextBox();
            this.ButtonLoad = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.SourceData = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.grid)).BeginInit();
            this.SuspendLayout();
            // 
            // FinalSchema
            // 
            this.FinalSchema.BackColor = System.Drawing.Color.Lavender;
            this.FinalSchema.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FinalSchema.Location = new System.Drawing.Point(7, 274);
            this.FinalSchema.Multiline = true;
            this.FinalSchema.Name = "FinalSchema";
            this.FinalSchema.ReadOnly = true;
            this.FinalSchema.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.FinalSchema.Size = new System.Drawing.Size(712, 248);
            this.FinalSchema.TabIndex = 15;
            this.FinalSchema.WordWrap = false;
            // 
            // ModeUsed
            // 
            this.ModeUsed.Location = new System.Drawing.Point(263, 18);
            this.ModeUsed.Name = "ModeUsed";
            this.ModeUsed.Size = new System.Drawing.Size(136, 16);
            this.ModeUsed.TabIndex = 14;
            // 
            // ReadMode
            // 
            this.ReadMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ReadMode.Location = new System.Drawing.Point(263, 34);
            this.ReadMode.Name = "ReadMode";
            this.ReadMode.Size = new System.Drawing.Size(136, 21);
            this.ReadMode.TabIndex = 13;
            // 
            // grid
            // 
            this.grid.AlternatingBackColor = System.Drawing.Color.GhostWhite;
            this.grid.BackColor = System.Drawing.Color.GhostWhite;
            this.grid.BackgroundColor = System.Drawing.Color.Lavender;
            this.grid.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.grid.CaptionBackColor = System.Drawing.Color.RoyalBlue;
            this.grid.CaptionForeColor = System.Drawing.Color.White;
            this.grid.CaptionText = "Loaded DataSet";
            this.grid.DataMember = "";
            this.grid.FlatMode = true;
            this.grid.Font = new System.Drawing.Font("Tahoma", 8F);
            this.grid.ForeColor = System.Drawing.Color.MidnightBlue;
            this.grid.GridLineColor = System.Drawing.Color.RoyalBlue;
            this.grid.HeaderBackColor = System.Drawing.Color.MidnightBlue;
            this.grid.HeaderFont = new System.Drawing.Font("Tahoma", 8F, System.Drawing.FontStyle.Bold);
            this.grid.HeaderForeColor = System.Drawing.Color.Lavender;
            this.grid.LinkColor = System.Drawing.Color.Teal;
            this.grid.Location = new System.Drawing.Point(407, 10);
            this.grid.Name = "grid";
            this.grid.ParentRowsBackColor = System.Drawing.Color.Lavender;
            this.grid.ParentRowsForeColor = System.Drawing.Color.MidnightBlue;
            this.grid.SelectionBackColor = System.Drawing.Color.Teal;
            this.grid.SelectionForeColor = System.Drawing.Color.PaleGreen;
            this.grid.Size = new System.Drawing.Size(312, 256);
            this.grid.TabIndex = 12;
            // 
            // Data
            // 
            this.Data.BackColor = System.Drawing.SystemColors.Info;
            this.Data.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Data.Location = new System.Drawing.Point(7, 66);
            this.Data.Multiline = true;
            this.Data.Name = "Data";
            this.Data.ReadOnly = true;
            this.Data.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.Data.Size = new System.Drawing.Size(392, 200);
            this.Data.TabIndex = 11;
            this.Data.WordWrap = false;
            // 
            // ButtonLoad
            // 
            this.ButtonLoad.Location = new System.Drawing.Point(183, 34);
            this.ButtonLoad.Name = "ButtonLoad";
            this.ButtonLoad.Size = new System.Drawing.Size(72, 21);
            this.ButtonLoad.TabIndex = 10;
            this.ButtonLoad.Text = "Load...";
            this.ButtonLoad.Click += new System.EventHandler(this.ButtonLoad_Click);
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(7, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(136, 23);
            this.label1.TabIndex = 9;
            this.label1.Text = "Pick up a data source";
            this.label1.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // SourceData
            // 
            this.SourceData.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.SourceData.Location = new System.Drawing.Point(7, 34);
            this.SourceData.Name = "SourceData";
            this.SourceData.Size = new System.Drawing.Size(168, 21);
            this.SourceData.TabIndex = 8;
            // 
            // ReadXML
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(726, 533);
            this.Controls.Add(this.FinalSchema);
            this.Controls.Add(this.ModeUsed);
            this.Controls.Add(this.ReadMode);
            this.Controls.Add(this.grid);
            this.Controls.Add(this.Data);
            this.Controls.Add(this.ButtonLoad);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.SourceData);
            this.Name = "ReadXML";
            this.Text = "Demonstrating ReadXml...";
            this.Load += new System.EventHandler(this.ReadXML_Load);
            ((System.ComponentModel.ISupportInitialize)(this.grid)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox FinalSchema;
        private System.Windows.Forms.Label ModeUsed;
        private System.Windows.Forms.ComboBox ReadMode;
        private System.Windows.Forms.DataGrid grid;
        private System.Windows.Forms.TextBox Data;
        private System.Windows.Forms.Button ButtonLoad;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox SourceData;
    }
}