
   partial class TreeViewDirectoryStructureForm
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
          this.directoryTreeView = new System.Windows.Forms.TreeView();
          this.promptLabel = new System.Windows.Forms.Label();
          this.inputTextBox = new System.Windows.Forms.TextBox();
          this.enterButton = new System.Windows.Forms.Button();
          this.SuspendLayout();
          // 
          // directoryTreeView
          // 
          this.directoryTreeView.Location = new System.Drawing.Point(12, 77);
          this.directoryTreeView.Name = "directoryTreeView";
          this.directoryTreeView.Size = new System.Drawing.Size(284, 102);
          this.directoryTreeView.TabIndex = 0;
          // 
          // promptLabel
          // 
          this.promptLabel.AutoSize = true;
          this.promptLabel.Location = new System.Drawing.Point(11, 22);
          this.promptLabel.Name = "promptLabel";
          this.promptLabel.Size = new System.Drawing.Size(273, 13);
          this.promptLabel.TabIndex = 1;
          this.promptLabel.Text = "Enter the full path to the directory you would like to view:";
          // 
          // inputTextBox
          // 
          this.inputTextBox.Location = new System.Drawing.Point(12, 43);
          this.inputTextBox.Name = "inputTextBox";
          this.inputTextBox.Size = new System.Drawing.Size(203, 20);
          this.inputTextBox.TabIndex = 2;
          // 
          // enterButton
          // 
          this.enterButton.Location = new System.Drawing.Point(221, 41);
          this.enterButton.Name = "enterButton";
          this.enterButton.Size = new System.Drawing.Size(75, 23);
          this.enterButton.TabIndex = 3;
          this.enterButton.Text = "Enter";
          this.enterButton.Click += new System.EventHandler(this.enterButton_Click);
          // 
          // TreeViewDirectoryStructureForm
          // 
          this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
          this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
          this.ClientSize = new System.Drawing.Size(304, 191);
          this.Controls.Add(this.enterButton);
          this.Controls.Add(this.inputTextBox);
          this.Controls.Add(this.promptLabel);
          this.Controls.Add(this.directoryTreeView);
          this.Name = "TreeViewDirectoryStructureForm";
          this.Text = "TreeViewDirectoryStructure";
          this.ResumeLayout(false);
          this.PerformLayout();

      }

      #endregion

      private System.Windows.Forms.TreeView directoryTreeView;
      private System.Windows.Forms.Label promptLabel;
      private System.Windows.Forms.TextBox inputTextBox;
      private System.Windows.Forms.Button enterButton;
   }
