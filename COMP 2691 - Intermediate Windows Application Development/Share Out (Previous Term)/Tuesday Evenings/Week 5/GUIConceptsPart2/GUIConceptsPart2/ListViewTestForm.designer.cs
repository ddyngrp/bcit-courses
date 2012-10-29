
   partial class ListViewTestForm
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
          this.components = new System.ComponentModel.Container();
          this.browserListView = new System.Windows.Forms.ListView();
          this.fileFolder = new System.Windows.Forms.ImageList(this.components);
          this.currentLabel = new System.Windows.Forms.Label();
          this.displayLabel = new System.Windows.Forms.Label();
          this.SuspendLayout();
          // 
          // browserListView
          // 
          this.browserListView.Location = new System.Drawing.Point(12, 83);
          this.browserListView.Name = "browserListView";
          this.browserListView.Size = new System.Drawing.Size(456, 197);
          this.browserListView.SmallImageList = this.fileFolder;
          this.browserListView.TabIndex = 0;
          this.browserListView.UseCompatibleStateImageBehavior = false;
          this.browserListView.View = System.Windows.Forms.View.List;
          this.browserListView.Click += new System.EventHandler(this.browserListView_Click);
          // 
          // fileFolder
          // 
          this.fileFolder.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
          this.fileFolder.ImageSize = new System.Drawing.Size(16, 16);
          this.fileFolder.TransparentColor = System.Drawing.Color.Transparent;
          // 
          // currentLabel
          // 
          this.currentLabel.AutoSize = true;
          this.currentLabel.Font = new System.Drawing.Font("Arial", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
          this.currentLabel.ForeColor = System.Drawing.Color.Black;
          this.currentLabel.Location = new System.Drawing.Point(10, 12);
          this.currentLabel.Name = "currentLabel";
          this.currentLabel.Size = new System.Drawing.Size(127, 16);
          this.currentLabel.TabIndex = 1;
          this.currentLabel.Text = "Now in Directory:";
          // 
          // displayLabel
          // 
          this.displayLabel.Location = new System.Drawing.Point(12, 39);
          this.displayLabel.Name = "displayLabel";
          this.displayLabel.Size = new System.Drawing.Size(456, 32);
          this.displayLabel.TabIndex = 2;
          // 
          // ListViewTestForm
          // 
          this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
          this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
          this.ClientSize = new System.Drawing.Size(480, 293);
          this.Controls.Add(this.displayLabel);
          this.Controls.Add(this.currentLabel);
          this.Controls.Add(this.browserListView);
          this.Name = "ListViewTestForm";
          this.Text = "ListViewTest";
          this.Load += new System.EventHandler(this.ListViewTestForm_Load);
          this.ResumeLayout(false);
          this.PerformLayout();

      }

      #endregion

      private System.Windows.Forms.ListView browserListView;
      private System.Windows.Forms.Label currentLabel;
      private System.Windows.Forms.Label displayLabel;
      private System.Windows.Forms.ImageList fileFolder;
   }


