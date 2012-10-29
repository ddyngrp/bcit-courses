namespace XMLdotNET.DiffGram
{
    partial class DiffGram
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DiffGram));
            this.ViewAsWeb = new System.Windows.Forms.CheckBox();
            this.ButtonUncheckAll = new System.Windows.Forms.Button();
            this.ButtonEdit = new System.Windows.Forms.Button();
            this.ButtonCheckAll = new System.Windows.Forms.Button();
            this.Check_Hidden = new System.Windows.Forms.CheckBox();
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
            this.WebBrowser = new AxSHDocVw.AxWebBrowser();
            ((System.ComponentModel.ISupportInitialize)(this.WebBrowser)).BeginInit();
            this.SuspendLayout();
            // 
            // ViewAsWeb
            // 
            this.ViewAsWeb.Location = new System.Drawing.Point(8, 324);
            this.ViewAsWeb.Name = "ViewAsWeb";
            this.ViewAsWeb.Size = new System.Drawing.Size(152, 24);
            this.ViewAsWeb.TabIndex = 41;
            this.ViewAsWeb.Text = "View as Web browser";
            this.ViewAsWeb.CheckedChanged += new System.EventHandler(this.ViewAsWeb_CheckedChanged);
            // 
            // ButtonUncheckAll
            // 
            this.ButtonUncheckAll.Location = new System.Drawing.Point(96, 172);
            this.ButtonUncheckAll.Name = "ButtonUncheckAll";
            this.ButtonUncheckAll.Size = new System.Drawing.Size(80, 20);
            this.ButtonUncheckAll.TabIndex = 40;
            this.ButtonUncheckAll.Text = "Uncheck all";
            this.ButtonUncheckAll.Click += new System.EventHandler(this.ButtonUncheckAll_Click);
            // 
            // ButtonEdit
            // 
            this.ButtonEdit.Enabled = false;
            this.ButtonEdit.Location = new System.Drawing.Point(680, 36);
            this.ButtonEdit.Name = "ButtonEdit";
            this.ButtonEdit.Size = new System.Drawing.Size(80, 24);
            this.ButtonEdit.TabIndex = 39;
            this.ButtonEdit.Text = "Edit";
            this.ButtonEdit.Click += new System.EventHandler(this.ButtonEdit_Click);
            // 
            // ButtonCheckAll
            // 
            this.ButtonCheckAll.Location = new System.Drawing.Point(8, 172);
            this.ButtonCheckAll.Name = "ButtonCheckAll";
            this.ButtonCheckAll.Size = new System.Drawing.Size(88, 20);
            this.ButtonCheckAll.TabIndex = 38;
            this.ButtonCheckAll.Text = "Check all";
            this.ButtonCheckAll.Click += new System.EventHandler(this.ButtonCheckAll_Click);
            // 
            // Check_Hidden
            // 
            this.Check_Hidden.Location = new System.Drawing.Point(8, 196);
            this.Check_Hidden.Name = "Check_Hidden";
            this.Check_Hidden.Size = new System.Drawing.Size(168, 24);
            this.Check_Hidden.TabIndex = 37;
            this.Check_Hidden.Text = "Hide Employees.employeeid";
            // 
            // appStatusBar
            // 
            this.appStatusBar.Location = new System.Drawing.Point(0, 383);
            this.appStatusBar.Name = "appStatusBar";
            this.appStatusBar.Size = new System.Drawing.Size(768, 22);
            this.appStatusBar.TabIndex = 36;
            this.appStatusBar.Text = "Ready";
            // 
            // label4
            // 
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(8, 276);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(168, 20);
            this.label4.TabIndex = 35;
            this.label4.Text = "Name of the DataSet";
            this.label4.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // DataSetName
            // 
            this.DataSetName.BackColor = System.Drawing.Color.PapayaWhip;
            this.DataSetName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.DataSetName.Location = new System.Drawing.Point(8, 300);
            this.DataSetName.Name = "DataSetName";
            this.DataSetName.Size = new System.Drawing.Size(168, 20);
            this.DataSetName.TabIndex = 34;
            this.DataSetName.Text = "NorthwindInfo";
            // 
            // TableName2
            // 
            this.TableName2.BackColor = System.Drawing.Color.PapayaWhip;
            this.TableName2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TableName2.Location = new System.Drawing.Point(544, 36);
            this.TableName2.Name = "TableName2";
            this.TableName2.Size = new System.Drawing.Size(120, 20);
            this.TableName2.TabIndex = 33;
            this.TableName2.Text = "Territories";
            // 
            // TableName1
            // 
            this.TableName1.BackColor = System.Drawing.Color.PapayaWhip;
            this.TableName1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TableName1.Location = new System.Drawing.Point(544, 12);
            this.TableName1.Name = "TableName1";
            this.TableName1.Size = new System.Drawing.Size(120, 20);
            this.TableName1.TabIndex = 32;
            this.TableName1.Text = "Employees";
            // 
            // label3
            // 
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(8, 68);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(168, 20);
            this.label3.TabIndex = 31;
            this.label3.Text = "Check to render as an attribute";
            this.label3.TextAlign = System.Drawing.ContentAlignment.BottomLeft;
            // 
            // OutputText
            // 
            this.OutputText.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.OutputText.BackColor = System.Drawing.SystemColors.Info;
            this.OutputText.Font = new System.Drawing.Font("Courier New", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.OutputText.Location = new System.Drawing.Point(184, 76);
            this.OutputText.Multiline = true;
            this.OutputText.Name = "OutputText";
            this.OutputText.ReadOnly = true;
            this.OutputText.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.OutputText.Size = new System.Drawing.Size(576, 294);
            this.OutputText.TabIndex = 30;
            this.OutputText.WordWrap = false;
            // 
            // ColumnSettings
            // 
            this.ColumnSettings.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ColumnSettings.Location = new System.Drawing.Point(8, 92);
            this.ColumnSettings.Name = "ColumnSettings";
            this.ColumnSettings.Size = new System.Drawing.Size(168, 77);
            this.ColumnSettings.TabIndex = 29;
            // 
            // Check_Nested
            // 
            this.Check_Nested.Location = new System.Drawing.Point(8, 244);
            this.Check_Nested.Name = "Check_Nested";
            this.Check_Nested.Size = new System.Drawing.Size(152, 24);
            this.Check_Nested.TabIndex = 28;
            this.Check_Nested.Text = "Create a nested relation";
            // 
            // Check_WithSchema
            // 
            this.Check_WithSchema.Location = new System.Drawing.Point(8, 220);
            this.Check_WithSchema.Name = "Check_WithSchema";
            this.Check_WithSchema.Size = new System.Drawing.Size(152, 24);
            this.Check_WithSchema.TabIndex = 27;
            this.Check_WithSchema.Text = "Save with schema";
            // 
            // ButtonSave
            // 
            this.ButtonSave.Location = new System.Drawing.Point(680, 4);
            this.ButtonSave.Name = "ButtonSave";
            this.ButtonSave.Size = new System.Drawing.Size(80, 24);
            this.ButtonSave.TabIndex = 26;
            this.ButtonSave.Text = "Save...";
            this.ButtonSave.Click += new System.EventHandler(this.ButtonSave_Click);
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(0, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 20);
            this.label2.TabIndex = 25;
            this.label2.Text = "Command";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // TerritoriesCommand
            // 
            this.TerritoriesCommand.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.TerritoriesCommand.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TerritoriesCommand.Location = new System.Drawing.Point(80, 36);
            this.TerritoriesCommand.Name = "TerritoriesCommand";
            this.TerritoriesCommand.Size = new System.Drawing.Size(456, 20);
            this.TerritoriesCommand.TabIndex = 24;
            this.TerritoriesCommand.Text = "SELECT TOP 10 employeeid, territoryid FROM employeeterritories";
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(0, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(72, 20);
            this.label1.TabIndex = 23;
            this.label1.Text = "Command";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // EmployeesCommand
            // 
            this.EmployeesCommand.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.EmployeesCommand.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EmployeesCommand.Location = new System.Drawing.Point(80, 12);
            this.EmployeesCommand.Name = "EmployeesCommand";
            this.EmployeesCommand.Size = new System.Drawing.Size(456, 20);
            this.EmployeesCommand.TabIndex = 22;
            this.EmployeesCommand.Text = "SELECT employeeid, lastname, firstname FROM employees";
            // 
            // WebBrowser
            // 
            this.WebBrowser.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.WebBrowser.Enabled = true;
            this.WebBrowser.Location = new System.Drawing.Point(182, 79);
            this.WebBrowser.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("WebBrowser.OcxState")));
            this.WebBrowser.Size = new System.Drawing.Size(576, 288);
            this.WebBrowser.TabIndex = 42;
            this.WebBrowser.Visible = false;
            // 
            // DiffGram
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(768, 405);
            this.Controls.Add(this.WebBrowser);
            this.Controls.Add(this.ViewAsWeb);
            this.Controls.Add(this.ButtonUncheckAll);
            this.Controls.Add(this.ButtonEdit);
            this.Controls.Add(this.ButtonCheckAll);
            this.Controls.Add(this.Check_Hidden);
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
            this.Name = "DiffGram";
            this.Text = "DiffGram";
            this.Load += new System.EventHandler(this.DiffGram_Load);
            ((System.ComponentModel.ISupportInitialize)(this.WebBrowser)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox ViewAsWeb;
        private System.Windows.Forms.Button ButtonUncheckAll;
        private System.Windows.Forms.Button ButtonEdit;
        private System.Windows.Forms.Button ButtonCheckAll;
        private System.Windows.Forms.CheckBox Check_Hidden;
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
        private AxSHDocVw.AxWebBrowser WebBrowser;
    }
}