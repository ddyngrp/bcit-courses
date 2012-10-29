namespace GUIConceptsPart2
{
    partial class ImageListControl
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.ListBox lstImageLocation;
        private System.Windows.Forms.Label lblCurrentImage;
        private System.Windows.Forms.Button btnShowNextImage;
        private System.Windows.Forms.Button btnRemoveImage;
        private System.Windows.Forms.Button btnClearList;
        private System.Windows.Forms.Button btnOpenImage;
        private System.Windows.Forms.PictureBox picImage;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        
        private System.Windows.Forms.Panel pnlImage;
        private System.Windows.Forms.Label lblImageLocation;
       

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
            this.components = new System.ComponentModel.Container();
            this.lstImageLocation = new System.Windows.Forms.ListBox();
            this.lblCurrentImage = new System.Windows.Forms.Label();
            this.btnShowNextImage = new System.Windows.Forms.Button();
            this.btnRemoveImage = new System.Windows.Forms.Button();
            this.btnClearList = new System.Windows.Forms.Button();
            this.btnOpenImage = new System.Windows.Forms.Button();
            this.picImage = new System.Windows.Forms.PictureBox();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.pnlImage = new System.Windows.Forms.Panel();
            this.lblImageLocation = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.picImage)).BeginInit();
            this.SuspendLayout();
            // 
            // lstImageLocation
            // 
            this.lstImageLocation.HorizontalScrollbar = true;
            this.lstImageLocation.Location = new System.Drawing.Point(16, 16);
            this.lstImageLocation.Name = "lstImageLocation";
            this.lstImageLocation.Size = new System.Drawing.Size(400, 95);
            this.lstImageLocation.TabIndex = 0;
            // 
            // lblCurrentImage
            // 
            this.lblCurrentImage.Location = new System.Drawing.Point(24, 168);
            this.lblCurrentImage.Name = "lblCurrentImage";
            this.lblCurrentImage.Size = new System.Drawing.Size(100, 23);
            this.lblCurrentImage.TabIndex = 7;
            // 
            // btnShowNextImage
            // 
            this.btnShowNextImage.Location = new System.Drawing.Point(96, 128);
            this.btnShowNextImage.Name = "btnShowNextImage";
            this.btnShowNextImage.Size = new System.Drawing.Size(104, 23);
            this.btnShowNextImage.TabIndex = 6;
            this.btnShowNextImage.Text = "Show Next Image";
            this.btnShowNextImage.Click += new System.EventHandler(this.btnShowNextImage_Click);
            // 
            // btnRemoveImage
            // 
            this.btnRemoveImage.Location = new System.Drawing.Point(208, 128);
            this.btnRemoveImage.Name = "btnRemoveImage";
            this.btnRemoveImage.Size = new System.Drawing.Size(104, 23);
            this.btnRemoveImage.TabIndex = 5;
            this.btnRemoveImage.Text = "Remove Image";
            this.btnRemoveImage.Click += new System.EventHandler(this.btnRemoveImage_Click);
            // 
            // btnClearList
            // 
            this.btnClearList.Location = new System.Drawing.Point(320, 128);
            this.btnClearList.Name = "btnClearList";
            this.btnClearList.Size = new System.Drawing.Size(75, 23);
            this.btnClearList.TabIndex = 4;
            this.btnClearList.Text = "Clear List";
            this.btnClearList.Click += new System.EventHandler(this.btnClearList_Click);
            // 
            // btnOpenImage
            // 
            this.btnOpenImage.Location = new System.Drawing.Point(16, 128);
            this.btnOpenImage.Name = "btnOpenImage";
            this.btnOpenImage.Size = new System.Drawing.Size(75, 23);
            this.btnOpenImage.TabIndex = 3;
            this.btnOpenImage.Text = "Open Image";
            this.btnOpenImage.Click += new System.EventHandler(this.btnOpenImage_Click);
            // 
            // picImage
            // 
            this.picImage.Location = new System.Drawing.Point(336, 259);
            this.picImage.Name = "picImage";
            this.picImage.Size = new System.Drawing.Size(80, 80);
            this.picImage.TabIndex = 2;
            this.picImage.TabStop = false;
            // 
            // imageList1
            // 
            this.imageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
            this.imageList1.ImageSize = new System.Drawing.Size(16, 16);
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // pnlImage
            // 
            this.pnlImage.Location = new System.Drawing.Point(16, 259);
            this.pnlImage.Name = "pnlImage";
            this.pnlImage.Size = new System.Drawing.Size(80, 80);
            this.pnlImage.TabIndex = 1;
            // 
            // lblImageLocation
            // 
            this.lblImageLocation.Location = new System.Drawing.Point(24, 189);
            this.lblImageLocation.Name = "lblImageLocation";
            this.lblImageLocation.Size = new System.Drawing.Size(384, 40);
            this.lblImageLocation.TabIndex = 0;
            // 
            // ImageListControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(436, 347);
            this.Controls.Add(this.lblImageLocation);
            this.Controls.Add(this.pnlImage);
            this.Controls.Add(this.picImage);
            this.Controls.Add(this.btnOpenImage);
            this.Controls.Add(this.btnClearList);
            this.Controls.Add(this.btnRemoveImage);
            this.Controls.Add(this.btnShowNextImage);
            this.Controls.Add(this.lblCurrentImage);
            this.Controls.Add(this.lstImageLocation);
            this.Name = "ImageListControl";
            this.Text = "ImageListControl";
            ((System.ComponentModel.ISupportInitialize)(this.picImage)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
    }
}