namespace COMP2690_Ass05
{
    partial class NewsReader
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
            this.fileMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.fileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.onlineMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.onlineGetGroupList = new System.Windows.Forms.ToolStripMenuItem();
            this.menuBar = new System.Windows.Forms.MenuStrip();
            this.txtServer = new System.Windows.Forms.TextBox();
            this.lblServer = new System.Windows.Forms.Label();
            this.splitContainerLists = new System.Windows.Forms.SplitContainer();
            this.lstGroups = new System.Windows.Forms.ListBox();
            this.lstArticleHeaders = new System.Windows.Forms.ListBox();
            this.splitContainerMain = new System.Windows.Forms.SplitContainer();
            this.txtArticle = new System.Windows.Forms.TextBox();
            this.grpFilterGroups = new System.Windows.Forms.GroupBox();
            this.lblGroupFilters = new System.Windows.Forms.Label();
            this.cboGroupFilters = new System.Windows.Forms.ComboBox();
            this.radExclude = new System.Windows.Forms.RadioButton();
            this.radInclude = new System.Windows.Forms.RadioButton();
            this.chkFilterGroups = new System.Windows.Forms.CheckBox();
            this.grpFilterArticles = new System.Windows.Forms.GroupBox();
            this.txtGetNumber = new System.Windows.Forms.TextBox();
            this.lblGetNumber2 = new System.Windows.Forms.Label();
            this.lblGetNumber = new System.Windows.Forms.Label();
            this.chkFilterArticles = new System.Windows.Forms.CheckBox();
            this.menuBar.SuspendLayout();
            this.splitContainerLists.Panel1.SuspendLayout();
            this.splitContainerLists.Panel2.SuspendLayout();
            this.splitContainerLists.SuspendLayout();
            this.splitContainerMain.Panel1.SuspendLayout();
            this.splitContainerMain.Panel2.SuspendLayout();
            this.splitContainerMain.SuspendLayout();
            this.grpFilterGroups.SuspendLayout();
            this.grpFilterArticles.SuspendLayout();
            this.SuspendLayout();
            // 
            // fileMenu
            // 
            this.fileMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileExit});
            this.fileMenu.Name = "fileMenu";
            this.fileMenu.Size = new System.Drawing.Size(35, 20);
            this.fileMenu.Text = "&File";
            // 
            // fileExit
            // 
            this.fileExit.Name = "fileExit";
            this.fileExit.Size = new System.Drawing.Size(103, 22);
            this.fileExit.Text = "E&xit";
            this.fileExit.Click += new System.EventHandler(this.fileExit_Click);
            // 
            // onlineMenu
            // 
            this.onlineMenu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.onlineGetGroupList});
            this.onlineMenu.Name = "onlineMenu";
            this.onlineMenu.Size = new System.Drawing.Size(49, 20);
            this.onlineMenu.Text = "&Online";
            // 
            // onlineGetGroupList
            // 
            this.onlineGetGroupList.Name = "onlineGetGroupList";
            this.onlineGetGroupList.Size = new System.Drawing.Size(153, 22);
            this.onlineGetGroupList.Text = "Get &Group List";
            this.onlineGetGroupList.Click += new System.EventHandler(this.onlineGetGroupList_Click);
            // 
            // menuBar
            // 
            this.menuBar.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileMenu,
            this.onlineMenu});
            this.menuBar.Location = new System.Drawing.Point(0, 0);
            this.menuBar.Name = "menuBar";
            this.menuBar.Size = new System.Drawing.Size(676, 24);
            this.menuBar.TabIndex = 0;
            this.menuBar.Text = "menuBar";
            // 
            // txtServer
            // 
            this.txtServer.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.txtServer.Location = new System.Drawing.Point(59, 33);
            this.txtServer.Name = "txtServer";
            this.txtServer.Size = new System.Drawing.Size(605, 20);
            this.txtServer.TabIndex = 0;
            this.txtServer.Text = "news.microsoft.com";
            // 
            // lblServer
            // 
            this.lblServer.AutoSize = true;
            this.lblServer.Location = new System.Drawing.Point(12, 36);
            this.lblServer.Name = "lblServer";
            this.lblServer.Size = new System.Drawing.Size(41, 13);
            this.lblServer.TabIndex = 0;
            this.lblServer.Text = "&Server:";
            // 
            // splitContainerLists
            // 
            this.splitContainerLists.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainerLists.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainerLists.Location = new System.Drawing.Point(0, 0);
            this.splitContainerLists.Name = "splitContainerLists";
            this.splitContainerLists.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainerLists.Panel1
            // 
            this.splitContainerLists.Panel1.Controls.Add(this.lstGroups);
            // 
            // splitContainerLists.Panel2
            // 
            this.splitContainerLists.Panel2.Controls.Add(this.lstArticleHeaders);
            this.splitContainerLists.Size = new System.Drawing.Size(242, 229);
            this.splitContainerLists.SplitterDistance = 107;
            this.splitContainerLists.TabIndex = 4;
            // 
            // lstGroups
            // 
            this.lstGroups.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lstGroups.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lstGroups.FormattingEnabled = true;
            this.lstGroups.IntegralHeight = false;
            this.lstGroups.Location = new System.Drawing.Point(0, 0);
            this.lstGroups.Name = "lstGroups";
            this.lstGroups.Size = new System.Drawing.Size(242, 107);
            this.lstGroups.TabIndex = 0;
            this.lstGroups.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.lstGroups_MouseDoubleClick);
            this.lstGroups.SelectedIndexChanged += new System.EventHandler(this.lstGroups_SelectedIndexChanged);
            // 
            // lstArticleHeaders
            // 
            this.lstArticleHeaders.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lstArticleHeaders.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lstArticleHeaders.FormattingEnabled = true;
            this.lstArticleHeaders.IntegralHeight = false;
            this.lstArticleHeaders.Location = new System.Drawing.Point(0, 0);
            this.lstArticleHeaders.Name = "lstArticleHeaders";
            this.lstArticleHeaders.Size = new System.Drawing.Size(242, 118);
            this.lstArticleHeaders.TabIndex = 0;
            this.lstArticleHeaders.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.lstArticleHeaders_MouseDoubleClick);
            this.lstArticleHeaders.SelectedIndexChanged += new System.EventHandler(this.lstArticleHeaders_SelectedIndexChanged);
            // 
            // splitContainerMain
            // 
            this.splitContainerMain.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainerMain.Location = new System.Drawing.Point(12, 166);
            this.splitContainerMain.Name = "splitContainerMain";
            // 
            // splitContainerMain.Panel1
            // 
            this.splitContainerMain.Panel1.Controls.Add(this.splitContainerLists);
            // 
            // splitContainerMain.Panel2
            // 
            this.splitContainerMain.Panel2.Controls.Add(this.txtArticle);
            this.splitContainerMain.Size = new System.Drawing.Size(652, 229);
            this.splitContainerMain.SplitterDistance = 242;
            this.splitContainerMain.TabIndex = 3;
            // 
            // txtArticle
            // 
            this.txtArticle.BackColor = System.Drawing.SystemColors.Window;
            this.txtArticle.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtArticle.Location = new System.Drawing.Point(0, 0);
            this.txtArticle.Multiline = true;
            this.txtArticle.Name = "txtArticle";
            this.txtArticle.ReadOnly = true;
            this.txtArticle.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtArticle.Size = new System.Drawing.Size(406, 229);
            this.txtArticle.TabIndex = 0;
            // 
            // grpFilterGroups
            // 
            this.grpFilterGroups.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.grpFilterGroups.Controls.Add(this.lblGroupFilters);
            this.grpFilterGroups.Controls.Add(this.cboGroupFilters);
            this.grpFilterGroups.Controls.Add(this.radExclude);
            this.grpFilterGroups.Controls.Add(this.radInclude);
            this.grpFilterGroups.Controls.Add(this.chkFilterGroups);
            this.grpFilterGroups.Location = new System.Drawing.Point(12, 59);
            this.grpFilterGroups.Name = "grpFilterGroups";
            this.grpFilterGroups.Size = new System.Drawing.Size(416, 101);
            this.grpFilterGroups.TabIndex = 1;
            this.grpFilterGroups.TabStop = false;
            // 
            // lblGroupFilters
            // 
            this.lblGroupFilters.AutoSize = true;
            this.lblGroupFilters.Location = new System.Drawing.Point(17, 57);
            this.lblGroupFilters.Name = "lblGroupFilters";
            this.lblGroupFilters.Size = new System.Drawing.Size(189, 13);
            this.lblGroupFilters.TabIndex = 3;
            this.lblGroupFilters.Text = "Enter filter &words separated by spaces:";
            // 
            // cboGroupFilters
            // 
            this.cboGroupFilters.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.cboGroupFilters.FormattingEnabled = true;
            this.cboGroupFilters.Location = new System.Drawing.Point(20, 73);
            this.cboGroupFilters.Name = "cboGroupFilters";
            this.cboGroupFilters.Size = new System.Drawing.Size(387, 21);
            this.cboGroupFilters.TabIndex = 3;
            // 
            // radExclude
            // 
            this.radExclude.AutoSize = true;
            this.radExclude.Location = new System.Drawing.Point(86, 35);
            this.radExclude.Name = "radExclude";
            this.radExclude.Size = new System.Drawing.Size(63, 17);
            this.radExclude.TabIndex = 2;
            this.radExclude.Text = "&Exclude";
            this.radExclude.UseVisualStyleBackColor = true;
            // 
            // radInclude
            // 
            this.radInclude.AutoSize = true;
            this.radInclude.Checked = true;
            this.radInclude.Location = new System.Drawing.Point(20, 35);
            this.radInclude.Name = "radInclude";
            this.radInclude.Size = new System.Drawing.Size(60, 17);
            this.radInclude.TabIndex = 1;
            this.radInclude.TabStop = true;
            this.radInclude.Text = "&Include";
            this.radInclude.UseVisualStyleBackColor = true;
            // 
            // chkFilterGroups
            // 
            this.chkFilterGroups.AutoSize = true;
            this.chkFilterGroups.Location = new System.Drawing.Point(12, 9);
            this.chkFilterGroups.Name = "chkFilterGroups";
            this.chkFilterGroups.Size = new System.Drawing.Size(83, 17);
            this.chkFilterGroups.TabIndex = 0;
            this.chkFilterGroups.Text = "Fil&ter groups";
            this.chkFilterGroups.UseVisualStyleBackColor = true;
            this.chkFilterGroups.CheckedChanged += new System.EventHandler(this.chkFilterGroups_CheckedChanged);
            // 
            // grpFilterArticles
            // 
            this.grpFilterArticles.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.grpFilterArticles.Controls.Add(this.txtGetNumber);
            this.grpFilterArticles.Controls.Add(this.lblGetNumber2);
            this.grpFilterArticles.Controls.Add(this.lblGetNumber);
            this.grpFilterArticles.Controls.Add(this.chkFilterArticles);
            this.grpFilterArticles.Location = new System.Drawing.Point(434, 59);
            this.grpFilterArticles.Name = "grpFilterArticles";
            this.grpFilterArticles.Size = new System.Drawing.Size(230, 101);
            this.grpFilterArticles.TabIndex = 2;
            this.grpFilterArticles.TabStop = false;
            // 
            // txtGetNumber
            // 
            this.txtGetNumber.Location = new System.Drawing.Point(108, 34);
            this.txtGetNumber.Name = "txtGetNumber";
            this.txtGetNumber.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.txtGetNumber.Size = new System.Drawing.Size(66, 20);
            this.txtGetNumber.TabIndex = 1;
            this.txtGetNumber.Text = "100";
            // 
            // lblGetNumber2
            // 
            this.lblGetNumber2.AutoSize = true;
            this.lblGetNumber2.Location = new System.Drawing.Point(177, 39);
            this.lblGetNumber2.Name = "lblGetNumber2";
            this.lblGetNumber2.Size = new System.Drawing.Size(40, 13);
            this.lblGetNumber2.TabIndex = 1;
            this.lblGetNumber2.Text = "articles";
            // 
            // lblGetNumber
            // 
            this.lblGetNumber.AutoSize = true;
            this.lblGetNumber.Location = new System.Drawing.Point(15, 39);
            this.lblGetNumber.Name = "lblGetNumber";
            this.lblGetNumber.Size = new System.Drawing.Size(95, 13);
            this.lblGetNumber.TabIndex = 1;
            this.lblGetNumber.Text = "Get only the latest:";
            // 
            // chkFilterArticles
            // 
            this.chkFilterArticles.AutoSize = true;
            this.chkFilterArticles.Checked = true;
            this.chkFilterArticles.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkFilterArticles.Location = new System.Drawing.Point(12, 9);
            this.chkFilterArticles.Name = "chkFilterArticles";
            this.chkFilterArticles.Size = new System.Drawing.Size(84, 17);
            this.chkFilterArticles.TabIndex = 0;
            this.chkFilterArticles.Text = "Filter &articles";
            this.chkFilterArticles.UseVisualStyleBackColor = true;
            this.chkFilterArticles.CheckedChanged += new System.EventHandler(this.chkFilterArticles_CheckedChanged);
            // 
            // NewsReader
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(676, 407);
            this.Controls.Add(this.grpFilterArticles);
            this.Controls.Add(this.grpFilterGroups);
            this.Controls.Add(this.splitContainerMain);
            this.Controls.Add(this.lblServer);
            this.Controls.Add(this.txtServer);
            this.Controls.Add(this.menuBar);
            this.MainMenuStrip = this.menuBar;
            this.Name = "NewsReader";
            this.Text = "News Reader";
            this.Load += new System.EventHandler(this.NewsReader_Load);
            this.menuBar.ResumeLayout(false);
            this.menuBar.PerformLayout();
            this.splitContainerLists.Panel1.ResumeLayout(false);
            this.splitContainerLists.Panel2.ResumeLayout(false);
            this.splitContainerLists.ResumeLayout(false);
            this.splitContainerMain.Panel1.ResumeLayout(false);
            this.splitContainerMain.Panel2.ResumeLayout(false);
            this.splitContainerMain.Panel2.PerformLayout();
            this.splitContainerMain.ResumeLayout(false);
            this.grpFilterGroups.ResumeLayout(false);
            this.grpFilterGroups.PerformLayout();
            this.grpFilterArticles.ResumeLayout(false);
            this.grpFilterArticles.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStripMenuItem fileMenu;
        private System.Windows.Forms.ToolStripMenuItem fileExit;
        private System.Windows.Forms.ToolStripMenuItem onlineMenu;
        private System.Windows.Forms.ToolStripMenuItem onlineGetGroupList;
        private System.Windows.Forms.MenuStrip menuBar;
        private System.Windows.Forms.TextBox txtServer;
        private System.Windows.Forms.Label lblServer;
        private System.Windows.Forms.SplitContainer splitContainerLists;
        private System.Windows.Forms.ListBox lstGroups;
        private System.Windows.Forms.ListBox lstArticleHeaders;
        private System.Windows.Forms.SplitContainer splitContainerMain;
        private System.Windows.Forms.TextBox txtArticle;
        private System.Windows.Forms.GroupBox grpFilterGroups;
        private System.Windows.Forms.GroupBox grpFilterArticles;
        private System.Windows.Forms.CheckBox chkFilterGroups;
        private System.Windows.Forms.CheckBox chkFilterArticles;
        private System.Windows.Forms.RadioButton radExclude;
        private System.Windows.Forms.RadioButton radInclude;
        private System.Windows.Forms.ComboBox cboGroupFilters;
        private System.Windows.Forms.Label lblGroupFilters;
        private System.Windows.Forms.TextBox txtGetNumber;
        private System.Windows.Forms.Label lblGetNumber2;
        private System.Windows.Forms.Label lblGetNumber;

    }
}

