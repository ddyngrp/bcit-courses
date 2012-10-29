namespace GUIConceptsPart2
{
    partial class ListViewControl
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
            this.btnCreateListView = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnCreateListView
            // 
            this.btnCreateListView.Location = new System.Drawing.Point(11, 12);
            this.btnCreateListView.Name = "btnCreateListView";
            this.btnCreateListView.Size = new System.Drawing.Size(110, 23);
            this.btnCreateListView.TabIndex = 0;
            this.btnCreateListView.Text = "Create List View";
            this.btnCreateListView.UseVisualStyleBackColor = true;
            this.btnCreateListView.Click += new System.EventHandler(this.btnCreateListView_Click);
            // 
            // ListViewControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(321, 297);
            this.Controls.Add(this.btnCreateListView);
            this.Name = "ListViewControl";
            this.Text = "ListViewControl";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnCreateListView;
    }
}