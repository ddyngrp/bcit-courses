namespace GUIConceptsPart2
{
    partial class TabControl
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
            this.tabControlTest = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.btnAddTab = new System.Windows.Forms.Button();
            this.btnRemoveTab = new System.Windows.Forms.Button();
            this.btnInsertTab = new System.Windows.Forms.Button();
            this.btnColorTabs = new System.Windows.Forms.Button();
            this.tabControlTest.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControlTest
            // 
            this.tabControlTest.Controls.Add(this.tabPage1);
            this.tabControlTest.Controls.Add(this.tabPage2);
            this.tabControlTest.Location = new System.Drawing.Point(12, 24);
            this.tabControlTest.Name = "tabControlTest";
            this.tabControlTest.SelectedIndex = 0;
            this.tabControlTest.Size = new System.Drawing.Size(394, 100);
            this.tabControlTest.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(386, 74);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(386, 74);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // btnAddTab
            // 
            this.btnAddTab.Location = new System.Drawing.Point(16, 167);
            this.btnAddTab.Name = "btnAddTab";
            this.btnAddTab.Size = new System.Drawing.Size(75, 23);
            this.btnAddTab.TabIndex = 0;
            this.btnAddTab.Text = "Add Tab";
            this.btnAddTab.UseVisualStyleBackColor = true;
            this.btnAddTab.Click += new System.EventHandler(this.btnAddTab_Click);
            // 
            // btnRemoveTab
            // 
            this.btnRemoveTab.Location = new System.Drawing.Point(123, 167);
            this.btnRemoveTab.Name = "btnRemoveTab";
            this.btnRemoveTab.Size = new System.Drawing.Size(85, 23);
            this.btnRemoveTab.TabIndex = 1;
            this.btnRemoveTab.Text = "Remove Tab";
            this.btnRemoveTab.UseVisualStyleBackColor = true;
            this.btnRemoveTab.Click += new System.EventHandler(this.btnRemoveTab_Click);
            // 
            // btnInsertTab
            // 
            this.btnInsertTab.Location = new System.Drawing.Point(243, 167);
            this.btnInsertTab.Name = "btnInsertTab";
            this.btnInsertTab.Size = new System.Drawing.Size(75, 23);
            this.btnInsertTab.TabIndex = 2;
            this.btnInsertTab.Text = "Insert Tab";
            this.btnInsertTab.UseVisualStyleBackColor = true;
            this.btnInsertTab.Click += new System.EventHandler(this.btnInsertTab_Click);
            // 
            // btnColorTabs
            // 
            this.btnColorTabs.Location = new System.Drawing.Point(16, 211);
            this.btnColorTabs.Name = "btnColorTabs";
            this.btnColorTabs.Size = new System.Drawing.Size(93, 23);
            this.btnColorTabs.TabIndex = 3;
            this.btnColorTabs.Text = "Color the Tabs";
            this.btnColorTabs.UseVisualStyleBackColor = true;
            this.btnColorTabs.Click += new System.EventHandler(this.btnColorTabs_Click);
            // 
            // TabControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(446, 266);
            this.Controls.Add(this.btnColorTabs);
            this.Controls.Add(this.btnInsertTab);
            this.Controls.Add(this.btnRemoveTab);
            this.Controls.Add(this.btnAddTab);
            this.Controls.Add(this.tabControlTest);
            this.Name = "TabControl";
            this.Text = "TabControl";
            this.tabControlTest.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControlTest;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button btnAddTab;
        private System.Windows.Forms.Button btnRemoveTab;
        private System.Windows.Forms.Button btnInsertTab;
        private System.Windows.Forms.Button btnColorTabs;
    }
}