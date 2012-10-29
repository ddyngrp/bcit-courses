namespace WeekThree
{
    partial class ScrollBarControl
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
            this.pbImage = new System.Windows.Forms.PictureBox();
            this.vScroll = new System.Windows.Forms.VScrollBar();
            this.hScroll = new System.Windows.Forms.HScrollBar();
            ((System.ComponentModel.ISupportInitialize)(this.pbImage)).BeginInit();
            this.SuspendLayout();
            // 
            // pbImage
            // 
            this.pbImage.Image = global::WeekThree.Properties.Resources.Flower;
            this.pbImage.Location = new System.Drawing.Point(-3, -1);
            this.pbImage.Name = "pbImage";
            this.pbImage.Size = new System.Drawing.Size(800, 600);
            this.pbImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pbImage.TabIndex = 0;
            this.pbImage.TabStop = false;
            // 
            // vScroll
            // 
            this.vScroll.Dock = System.Windows.Forms.DockStyle.Right;
            this.vScroll.Location = new System.Drawing.Point(391, 0);
            this.vScroll.Name = "vScroll";
            this.vScroll.Size = new System.Drawing.Size(17, 363);
            this.vScroll.TabIndex = 1;
            this.vScroll.Scroll += new System.Windows.Forms.ScrollEventHandler(this.vScroll_Scroll);
            // 
            // hScroll
            // 
            this.hScroll.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.hScroll.Location = new System.Drawing.Point(0, 346);
            this.hScroll.Name = "hScroll";
            this.hScroll.Size = new System.Drawing.Size(391, 17);
            this.hScroll.TabIndex = 2;
            this.hScroll.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScroll_Scroll);
            // 
            // ScrollBarControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(408, 363);
            this.Controls.Add(this.hScroll);
            this.Controls.Add(this.vScroll);
            this.Controls.Add(this.pbImage);
            this.Name = "ScrollBarControl";
            this.Text = "ScrollBarControl";
            ((System.ComponentModel.ISupportInitialize)(this.pbImage)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pbImage;
        private System.Windows.Forms.VScrollBar vScroll;
        private System.Windows.Forms.HScrollBar hScroll;

    }
}