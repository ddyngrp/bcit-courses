namespace GUIConceptsPart2
{
    partial class TreeViewControl
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
            this.btnPopulateTreeView = new System.Windows.Forms.Button();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.SuspendLayout();
            // 
            // btnPopulateTreeView
            // 
            this.btnPopulateTreeView.Location = new System.Drawing.Point(12, 12);
            this.btnPopulateTreeView.Name = "btnPopulateTreeView";
            this.btnPopulateTreeView.Size = new System.Drawing.Size(250, 23);
            this.btnPopulateTreeView.TabIndex = 0;
            this.btnPopulateTreeView.Text = "Display Customer Information in a TreeView";
            this.btnPopulateTreeView.UseVisualStyleBackColor = true;
            this.btnPopulateTreeView.Click += new System.EventHandler(this.btnPopulateTreeView_Click);
            // 
            // treeView1
            // 
            this.treeView1.Location = new System.Drawing.Point(12, 51);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(300, 256);
            this.treeView1.TabIndex = 1;
            // 
            // TreeViewControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(341, 348);
            this.Controls.Add(this.treeView1);
            this.Controls.Add(this.btnPopulateTreeView);
            this.Name = "TreeViewControl";
            this.Text = "TreeViewControl";
            
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnPopulateTreeView;
        private System.Windows.Forms.TreeView treeView1;
    }
}