namespace TamilFM
{
    partial class mainForm
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

                if (notifyIcon != null)
                {
                    notifyIcon.Dispose();
                }
                if (mediaPlayer != null)
                {
                    mediaPlayer.Dispose();
                }
                if (vlcPlayer != null)
                {
                    vlcPlayer.Dispose();
                }
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainForm));
            this.comboStation = new System.Windows.Forms.ComboBox();
            this.laStation = new System.Windows.Forms.Label();
            this.ctxtMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.showMainToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stationsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ctxtMenu.SuspendLayout();
            this.SuspendLayout();
            // 
            // comboStation
            // 
            this.comboStation.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboStation.FormattingEnabled = true;
            this.comboStation.Location = new System.Drawing.Point(85, 48);
            this.comboStation.Name = "comboStation";
            this.comboStation.Size = new System.Drawing.Size(209, 21);
            this.comboStation.TabIndex = 1;
            this.comboStation.SelectedIndexChanged += new System.EventHandler(this.comboStation_SelectedIndexChanged);
            // 
            // laStation
            // 
            this.laStation.AutoSize = true;
            this.laStation.Location = new System.Drawing.Point(3, 51);
            this.laStation.Name = "laStation";
            this.laStation.Size = new System.Drawing.Size(76, 13);
            this.laStation.TabIndex = 3;
            this.laStation.Text = "SelectStation :";
            this.laStation.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // ctxtMenu
            // 
            this.ctxtMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem,
            this.showMainToolStripMenuItem,
            this.stationsToolStripMenuItem,
            this.toolStripMenuItem1,
            this.exitToolStripMenuItem});
            this.ctxtMenu.Name = "ctxtMenu";
            this.ctxtMenu.Size = new System.Drawing.Size(134, 98);
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(133, 22);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // showMainToolStripMenuItem
            // 
            this.showMainToolStripMenuItem.Name = "showMainToolStripMenuItem";
            this.showMainToolStripMenuItem.Size = new System.Drawing.Size(133, 22);
            this.showMainToolStripMenuItem.Text = "ShowMain";
            this.showMainToolStripMenuItem.Click += new System.EventHandler(this.showMainToolStripMenuItem_Click);
            // 
            // stationsToolStripMenuItem
            // 
            this.stationsToolStripMenuItem.Name = "stationsToolStripMenuItem";
            this.stationsToolStripMenuItem.Size = new System.Drawing.Size(133, 22);
            this.stationsToolStripMenuItem.Text = "Stations";
            this.stationsToolStripMenuItem.DropDownItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.stationsToolStripMenuItem_DropDownItemClicked);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(130, 6);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(133, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(516, 101);
            this.Controls.Add(this.laStation);
            this.Controls.Add(this.comboStation);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "mainForm";
            this.ShowInTaskbar = false;
            this.Text = "Radio Tamil";
            this.SizeChanged += new System.EventHandler(this.mainForm_SizeChanged);
            this.Load += new System.EventHandler(this.mainForm_Load);
            this.ctxtMenu.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboStation;
        private System.Windows.Forms.Label laStation;
        private VolumeControl vlcVolumeCtrl;
        private System.Windows.Forms.Label laVlcDesc;
        private System.Windows.Forms.Label lavlcVolume;
        private System.Windows.Forms.Button vlcStopBttn;
        private System.Windows.Forms.Button vlcPlayBttn;
        private System.Windows.Forms.ContextMenuStrip ctxtMenu;
        private System.Windows.Forms.ToolStripMenuItem stationsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem showMainToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
    }
}

