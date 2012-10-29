
   partial class UsingTabsForm
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
         this.textOptionsTabControl = new System.Windows.Forms.TabControl();
         this.colorTabPage = new System.Windows.Forms.TabPage();
         this.greenRadioButton = new System.Windows.Forms.RadioButton();
         this.redRadioButton = new System.Windows.Forms.RadioButton();
         this.blackRadioButton = new System.Windows.Forms.RadioButton();
         this.sizeTabPage = new System.Windows.Forms.TabPage();
         this.size20RadioButton = new System.Windows.Forms.RadioButton();
         this.size16RadioButton = new System.Windows.Forms.RadioButton();
         this.size12RadioButton = new System.Windows.Forms.RadioButton();
         this.messageTabPage = new System.Windows.Forms.TabPage();
         this.goodbyeRadioButton = new System.Windows.Forms.RadioButton();
         this.helloRadioButton = new System.Windows.Forms.RadioButton();
         this.aboutTabPage = new System.Windows.Forms.TabPage();
         this.messageLabel = new System.Windows.Forms.Label();
         this.displayLabel = new System.Windows.Forms.Label();
         this.textOptionsTabControl.SuspendLayout();
         this.colorTabPage.SuspendLayout();
         this.sizeTabPage.SuspendLayout();
         this.messageTabPage.SuspendLayout();
         this.aboutTabPage.SuspendLayout();
         this.SuspendLayout();
         // 
         // textOptionsTabControl
         // 
         this.textOptionsTabControl.Controls.Add(this.colorTabPage);
         this.textOptionsTabControl.Controls.Add(this.sizeTabPage);
         this.textOptionsTabControl.Controls.Add(this.messageTabPage);
         this.textOptionsTabControl.Controls.Add(this.aboutTabPage);
         this.textOptionsTabControl.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.textOptionsTabControl.Location = new System.Drawing.Point(12, 12);
         this.textOptionsTabControl.Name = "textOptionsTabControl";
         this.textOptionsTabControl.SelectedIndex = 0;
         this.textOptionsTabControl.Size = new System.Drawing.Size(315, 186);
         this.textOptionsTabControl.TabIndex = 0;
         // 
         // colorTabPage
         // 
         this.colorTabPage.Controls.Add(this.greenRadioButton);
         this.colorTabPage.Controls.Add(this.redRadioButton);
         this.colorTabPage.Controls.Add(this.blackRadioButton);
         this.colorTabPage.Location = new System.Drawing.Point(4, 29);
         this.colorTabPage.Name = "colorTabPage";
         this.colorTabPage.Padding = new System.Windows.Forms.Padding(3);
         this.colorTabPage.Size = new System.Drawing.Size(307, 153);
         this.colorTabPage.TabIndex = 0;
         this.colorTabPage.Text = "Color";
         // 
         // greenRadioButton
         // 
         this.greenRadioButton.AutoSize = true;
         this.greenRadioButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.greenRadioButton.Location = new System.Drawing.Point(34, 106);
         this.greenRadioButton.Name = "greenRadioButton";
         this.greenRadioButton.Size = new System.Drawing.Size(67, 24);
         this.greenRadioButton.TabIndex = 2;
         this.greenRadioButton.Text = "Green";
         this.greenRadioButton.CheckedChanged += new System.EventHandler(this.greenRadioButton_CheckedChanged);
         // 
         // redRadioButton
         // 
         this.redRadioButton.AutoSize = true;
         this.redRadioButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.redRadioButton.Location = new System.Drawing.Point(34, 59);
         this.redRadioButton.Name = "redRadioButton";
         this.redRadioButton.Size = new System.Drawing.Size(52, 24);
         this.redRadioButton.TabIndex = 1;
         this.redRadioButton.Text = "Red";
         this.redRadioButton.CheckedChanged += new System.EventHandler(this.redRadioButton_CheckedChanged);
         // 
         // blackRadioButton
         // 
         this.blackRadioButton.AutoSize = true;
         this.blackRadioButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.blackRadioButton.Location = new System.Drawing.Point(34, 15);
         this.blackRadioButton.Name = "blackRadioButton";
         this.blackRadioButton.Size = new System.Drawing.Size(61, 24);
         this.blackRadioButton.TabIndex = 0;
         this.blackRadioButton.Text = "Black";
         this.blackRadioButton.CheckedChanged += new System.EventHandler(this.blackRadioButton_CheckedChanged);
         // 
         // sizeTabPage
         // 
         this.sizeTabPage.Controls.Add(this.size20RadioButton);
         this.sizeTabPage.Controls.Add(this.size16RadioButton);
         this.sizeTabPage.Controls.Add(this.size12RadioButton);
         this.sizeTabPage.Location = new System.Drawing.Point(4, 22);
         this.sizeTabPage.Name = "sizeTabPage";
         this.sizeTabPage.Padding = new System.Windows.Forms.Padding(3);
         this.sizeTabPage.Size = new System.Drawing.Size(307, 160);
         this.sizeTabPage.TabIndex = 1;
         this.sizeTabPage.Text = "Size";
         // 
         // size20RadioButton
         // 
         this.size20RadioButton.AutoSize = true;
         this.size20RadioButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.size20RadioButton.Location = new System.Drawing.Point(34, 106);
         this.size20RadioButton.Name = "size20RadioButton";
         this.size20RadioButton.Size = new System.Drawing.Size(79, 24);
         this.size20RadioButton.TabIndex = 2;
         this.size20RadioButton.Text = "20 point";
         this.size20RadioButton.CheckedChanged += new System.EventHandler(this.size20RadioButton_CheckedChanged);
         // 
         // size16RadioButton
         // 
         this.size16RadioButton.AutoSize = true;
         this.size16RadioButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.size16RadioButton.Location = new System.Drawing.Point(34, 59);
         this.size16RadioButton.Name = "size16RadioButton";
         this.size16RadioButton.Size = new System.Drawing.Size(79, 24);
         this.size16RadioButton.TabIndex = 1;
         this.size16RadioButton.Text = "16 point";
         this.size16RadioButton.CheckedChanged += new System.EventHandler(this.size16RadioButton_CheckedChanged);
         // 
         // size12RadioButton
         // 
         this.size12RadioButton.AutoSize = true;
         this.size12RadioButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.size12RadioButton.Location = new System.Drawing.Point(34, 15);
         this.size12RadioButton.Name = "size12RadioButton";
         this.size12RadioButton.Size = new System.Drawing.Size(79, 24);
         this.size12RadioButton.TabIndex = 0;
         this.size12RadioButton.Text = "12 point";
         this.size12RadioButton.CheckedChanged += new System.EventHandler(this.size12RadioButton_CheckedChanged);
         // 
         // messageTabPage
         // 
         this.messageTabPage.Controls.Add(this.goodbyeRadioButton);
         this.messageTabPage.Controls.Add(this.helloRadioButton);
         this.messageTabPage.Location = new System.Drawing.Point(4, 29);
         this.messageTabPage.Name = "messageTabPage";
         this.messageTabPage.Size = new System.Drawing.Size(307, 153);
         this.messageTabPage.TabIndex = 2;
         this.messageTabPage.Text = "Message";
         // 
         // goodbyeRadioButton
         // 
         this.goodbyeRadioButton.AutoSize = true;
         this.goodbyeRadioButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.goodbyeRadioButton.Location = new System.Drawing.Point(29, 66);
         this.goodbyeRadioButton.Name = "goodbyeRadioButton";
         this.goodbyeRadioButton.Size = new System.Drawing.Size(91, 24);
         this.goodbyeRadioButton.TabIndex = 1;
         this.goodbyeRadioButton.Text = "Goodbye!";
         this.goodbyeRadioButton.CheckedChanged += new System.EventHandler(this.goodbyeRadioButton_CheckedChanged);
         // 
         // helloRadioButton
         // 
         this.helloRadioButton.AutoSize = true;
         this.helloRadioButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.helloRadioButton.Location = new System.Drawing.Point(29, 21);
         this.helloRadioButton.Name = "helloRadioButton";
         this.helloRadioButton.Size = new System.Drawing.Size(62, 24);
         this.helloRadioButton.TabIndex = 0;
         this.helloRadioButton.Text = "Hello!";
         this.helloRadioButton.CheckedChanged += new System.EventHandler(this.helloRadioButton_CheckedChanged);
         // 
         // aboutTabPage
         // 
         this.aboutTabPage.Controls.Add(this.messageLabel);
         this.aboutTabPage.Location = new System.Drawing.Point(4, 29);
         this.aboutTabPage.Name = "aboutTabPage";
         this.aboutTabPage.Size = new System.Drawing.Size(307, 153);
         this.aboutTabPage.TabIndex = 3;
         this.aboutTabPage.Text = "About";
         // 
         // messageLabel
         // 
         this.messageLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
         this.messageLabel.Location = new System.Drawing.Point(18, 20);
         this.messageLabel.Name = "messageLabel";
         this.messageLabel.Size = new System.Drawing.Size(227, 99);
         this.messageLabel.TabIndex = 0;
         this.messageLabel.Text = "Tabs are used to organize controls and conserve screen space.";
         // 
         // displayLabel
         // 
         this.displayLabel.Location = new System.Drawing.Point(120, 211);
         this.displayLabel.Name = "displayLabel";
         this.displayLabel.Size = new System.Drawing.Size(146, 42);
         this.displayLabel.TabIndex = 1;
         this.displayLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
         // 
         // UsingTabsForm
         // 
         this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
         this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
         this.ClientSize = new System.Drawing.Size(340, 262);
         this.Controls.Add(this.displayLabel);
         this.Controls.Add(this.textOptionsTabControl);
         this.Name = "UsingTabsForm";
         this.Text = "Using Tabs";
         this.textOptionsTabControl.ResumeLayout(false);
         this.colorTabPage.ResumeLayout(false);
         this.colorTabPage.PerformLayout();
         this.sizeTabPage.ResumeLayout(false);
         this.sizeTabPage.PerformLayout();
         this.messageTabPage.ResumeLayout(false);
         this.messageTabPage.PerformLayout();
         this.aboutTabPage.ResumeLayout(false);
         this.ResumeLayout(false);

      }

      #endregion

      private System.Windows.Forms.TabControl textOptionsTabControl;
      private System.Windows.Forms.TabPage colorTabPage;
      private System.Windows.Forms.TabPage sizeTabPage;
      private System.Windows.Forms.TabPage messageTabPage;
      private System.Windows.Forms.TabPage aboutTabPage;
      private System.Windows.Forms.RadioButton greenRadioButton;
      private System.Windows.Forms.RadioButton redRadioButton;
      private System.Windows.Forms.RadioButton blackRadioButton;
      private System.Windows.Forms.RadioButton size20RadioButton;
      private System.Windows.Forms.RadioButton size16RadioButton;
      private System.Windows.Forms.RadioButton size12RadioButton;
      private System.Windows.Forms.RadioButton helloRadioButton;
      private System.Windows.Forms.RadioButton goodbyeRadioButton;
      private System.Windows.Forms.Label messageLabel;
      private System.Windows.Forms.Label displayLabel;
   }
