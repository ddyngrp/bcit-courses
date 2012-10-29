namespace XMLdotNET.WriteXML
{
    partial class WriteXML
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
            this.Check_Validating = new System.Windows.Forms.CheckBox();
            this.Check_Relation = new System.Windows.Forms.CheckBox();
            this.appStatusBar = new System.Windows.Forms.StatusBar();
            this.label4 = new System.Windows.Forms.Label();
            this.DataSetName = new System.Windows.Forms.TextBox();
            this.TableName2 = new System.Windows.Forms.TextBox();
            this.TableName1 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.OutputText = new System.Windows.Forms.TextBox();
            this.ColumnSettings = new System.Windows.Forms.CheckedListBox();
            this.Check_Nested = new System.Windows.Forms.CheckBox();
            this.Check_WithSchema = new System.Windows.Forms.CheckBox();
            this.ButtonSave = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.TerritoriesCommand = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.EmployeesCommand = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // Check_Validating
            // 
            this.Check_Validating.Location = new System.Drawing.Point(8, 248);
            this.Check_Validating.Name = "Check_Validating";
            this.Check_Validating.Size = new System.Drawing.Size(152, 24);
            this.Check_Validating.TabIndex = 34;
            this.Check_Validating.Text = "Create validating output ";
            // 
            // Check_Relation
            // 
            this.Check_Relation.Location = new System.Drawing.Point(8, 192);
            this.Check_Relation.Name = "Check_Relation";
            this.Check_Relation.Size = new System.Drawing.Size(112, 24);
            this.Check_Relation.TabIndex = 33;
            this.Check_Relation.Text = "Create a relation";
            // 
            // appStatusBar
            // 
            this.appStatusBar.Location = new System.Drawing.Point(0, 337);
            this.appStatusBar.Name = "appStatusBar";
            this.appStatusBar.Size = new System.Drawing.Size(768, 22);
            this.appStatusBar.TabIndex = 32;
            this.appStatusBar.Text = "Ready";
            // 
            // label4
            // 
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(8, 272);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(168, 20);
            this.label4.TabIndex = 31;
            this.label4.Text = "Name of the DataSet";
            this.label4.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // DataSetName
            // 
            this.DataSetName.BackColor = System.Drawing.Color.PapayaWhip;
            this.DataSetName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.DataSetName.Location = new System.Drawing.Point(8, 296);
            this.DataSetName.Name = "DataSetName";
            this.DataSetName.Size = new System.Drawing.Size(168, 20);
            this.DataSetName.TabIndex = 30;
            this.DataSetName.Text = "NorthwindInfo";
            // 
            // TableName2
            // 
            this.TableName2.BackColor = System.Drawing.Color.PapayaWhip;
            this.TableName2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TableName2.Location = new System.Drawing.Point(544, 32);
            this.TableName2.Name = "TableName2";
            this.TableName2.Size = new System.Drawing.Size(120, 20);
            this.TableName2.TabIndex = 29;
            this.TableName2.Text = "Territories";
            // 
            // TableName1
            // 
            this.TableName1.BackColor = System.Drawing.Color.PapayaWhip;
            this.TableName1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TableName1.Location = new System.Drawing.Point(544, 8);
            this.TableName1.Name = "TableName1";
            this.TableName1.Size = new System.Drawing.Size(120, 20);
            this.TableName1.TabIndex = 28;
            this.TableName1.Text = "Employees";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(5, 72);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(184, 13);
            this.label3.TabIndex = 27;
            this.label3.Text = "Check to render as an attribute";
            this.label3.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // OutputText
            // 
            this.OutputText.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.OutputText.BackColor = System.Drawing.SystemColors.Info;
            this.OutputText.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.OutputText.Location = new System.Drawing.Point(192, 72);
            this.OutputText.Multiline = true;
            this.OutputText.Name = "OutputText";
            this.OutputText.ReadOnly = true;
            this.OutputText.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.OutputText.Size = new System.Drawing.Size(568, 248);
            this.OutputText.TabIndex = 26;
            this.OutputText.WordWrap = false;
            // 
            // ColumnSettings
            // 
            this.ColumnSettings.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ColumnSettings.Location = new System.Drawing.Point(8, 88);
            this.ColumnSettings.Name = "ColumnSettings";
            this.ColumnSettings.Size = new System.Drawing.Size(168, 77);
            this.ColumnSettings.TabIndex = 25;
            // 
            // Check_Nested
            // 
            this.Check_Nested.Location = new System.Drawing.Point(40, 216);
            this.Check_Nested.Name = "Check_Nested";
            this.Check_Nested.Size = new System.Drawing.Size(112, 24);
            this.Check_Nested.TabIndex = 24;
            this.Check_Nested.Text = "Nested Relations";
            // 
            // Check_WithSchema
            // 
            this.Check_WithSchema.Location = new System.Drawing.Point(8, 168);
            this.Check_WithSchema.Name = "Check_WithSchema";
            this.Check_WithSchema.Size = new System.Drawing.Size(152, 24);
            this.Check_WithSchema.TabIndex = 23;
            this.Check_WithSchema.Text = "Save with schema";
            // 
            // ButtonSave
            // 
            this.ButtonSave.Location = new System.Drawing.Point(680, 8);
            this.ButtonSave.Name = "ButtonSave";
            this.ButtonSave.Size = new System.Drawing.Size(80, 40);
            this.ButtonSave.TabIndex = 22;
            this.ButtonSave.Text = "Save...";
            this.ButtonSave.Click += new System.EventHandler(this.ButtonSave_Click);
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(0, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 20);
            this.label2.TabIndex = 21;
            this.label2.Text = "Command";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // TerritoriesCommand
            // 
            this.TerritoriesCommand.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TerritoriesCommand.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TerritoriesCommand.Location = new System.Drawing.Point(80, 32);
            this.TerritoriesCommand.Name = "TerritoriesCommand";
            this.TerritoriesCommand.Size = new System.Drawing.Size(456, 20);
            this.TerritoriesCommand.TabIndex = 20;
            this.TerritoriesCommand.Text = "SELECT TOP 10 employeeid, territoryid FROM employeeterritories";
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(0, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(72, 20);
            this.label1.TabIndex = 19;
            this.label1.Text = "Command";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // EmployeesCommand
            // 
            this.EmployeesCommand.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.EmployeesCommand.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EmployeesCommand.Location = new System.Drawing.Point(80, 8);
            this.EmployeesCommand.Name = "EmployeesCommand";
            this.EmployeesCommand.Size = new System.Drawing.Size(456, 20);
            this.EmployeesCommand.TabIndex = 18;
            this.EmployeesCommand.Text = "SELECT employeeid, lastname, firstname FROM employees";
            // 
            // WriteXML
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(768, 359);
            this.Controls.Add(this.Check_Validating);
            this.Controls.Add(this.Check_Relation);
            this.Controls.Add(this.appStatusBar);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.DataSetName);
            this.Controls.Add(this.TableName2);
            this.Controls.Add(this.TableName1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.OutputText);
            this.Controls.Add(this.ColumnSettings);
            this.Controls.Add(this.Check_Nested);
            this.Controls.Add(this.Check_WithSchema);
            this.Controls.Add(this.ButtonSave);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.TerritoriesCommand);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.EmployeesCommand);
            this.Name = "WriteXML";
            this.Text = "Writing DataSets to XML...";
            this.Load += new System.EventHandler(this.WriteXML_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox Check_Validating;
        private System.Windows.Forms.CheckBox Check_Relation;
        private System.Windows.Forms.StatusBar appStatusBar;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox DataSetName;
        private System.Windows.Forms.TextBox TableName2;
        private System.Windows.Forms.TextBox TableName1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox OutputText;
        private System.Windows.Forms.CheckedListBox ColumnSettings;
        private System.Windows.Forms.CheckBox Check_Nested;
        private System.Windows.Forms.CheckBox Check_WithSchema;
        private System.Windows.Forms.Button ButtonSave;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox TerritoriesCommand;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox EmployeesCommand;
    }
}