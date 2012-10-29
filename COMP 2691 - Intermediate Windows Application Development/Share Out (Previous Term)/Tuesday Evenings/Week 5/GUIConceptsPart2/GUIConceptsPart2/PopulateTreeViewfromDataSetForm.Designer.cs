namespace GUIConceptsPart2
{
    partial class PopulateTreeViewfromDataSetForm
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
            this.btnPopulate = new System.Windows.Forms.Button();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.SuspendLayout();
            // 
            // btnPopulate
            // 
            this.btnPopulate.Location = new System.Drawing.Point(42, 12);
            this.btnPopulate.Name = "btnPopulate";
            this.btnPopulate.Size = new System.Drawing.Size(123, 23);
            this.btnPopulate.TabIndex = 0;
            this.btnPopulate.Text = "Populate TreeView";
            this.btnPopulate.UseVisualStyleBackColor = true;
            this.btnPopulate.Click += new System.EventHandler(this.btnPopulate_Click);
            // 
            // treeView1
            // 
            this.treeView1.Location = new System.Drawing.Point(44, 41);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(328, 200);
            this.treeView1.TabIndex = 1;
            // 
            // PopulateTreeViewfromDataSetForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(407, 266);
            this.Controls.Add(this.treeView1);
            this.Controls.Add(this.btnPopulate);
            this.Name = "PopulateTreeViewfromDataSetForm";
            this.Text = "Populate TreeView Control from DataSet";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnPopulate;
        private System.Windows.Forms.TreeView treeView1;
    }
}