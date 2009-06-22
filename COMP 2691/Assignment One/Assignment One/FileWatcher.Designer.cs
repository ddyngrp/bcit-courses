/*
 * FileWatcher.Designer.cs - Assignment One
 * 
 * Copyright (C) Steffen L. Norgren 2009 <ironix@trollop.org>
 *               A00683006
 *               
 * Created: 2009-06-22
 * 
 * FileWatcher.Designer.cs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FileWatcher.Designer.cs is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

namespace Assignment_One
{
    partial class FileWatcher
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
            this.btn_start = new System.Windows.Forms.Button();
            this.btn_stop = new System.Windows.Forms.Button();
            this.btn_clear = new System.Windows.Forms.Button();
            this.txtMonitor = new System.Windows.Forms.TextBox();
            this.lstNewFiles = new System.Windows.Forms.ListBox();
            this.lbl_new = new System.Windows.Forms.Label();
            this.lbl_changes = new System.Windows.Forms.Label();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // btn_start
            // 
            this.btn_start.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_start.AutoSize = true;
            this.btn_start.Location = new System.Drawing.Point(193, 353);
            this.btn_start.Name = "btn_start";
            this.btn_start.Size = new System.Drawing.Size(75, 23);
            this.btn_start.TabIndex = 0;
            this.btn_start.Text = "Start";
            this.btn_start.UseVisualStyleBackColor = true;
            this.btn_start.Click += new System.EventHandler(this.btn_start_Click);
            // 
            // btn_stop
            // 
            this.btn_stop.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_stop.AutoSize = true;
            this.btn_stop.Enabled = false;
            this.btn_stop.Location = new System.Drawing.Point(274, 353);
            this.btn_stop.Name = "btn_stop";
            this.btn_stop.Size = new System.Drawing.Size(75, 23);
            this.btn_stop.TabIndex = 1;
            this.btn_stop.Text = "Stop";
            this.btn_stop.UseVisualStyleBackColor = true;
            this.btn_stop.Click += new System.EventHandler(this.btn_stop_Click);
            // 
            // btn_clear
            // 
            this.btn_clear.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btn_clear.AutoSize = true;
            this.btn_clear.Location = new System.Drawing.Point(355, 353);
            this.btn_clear.Name = "btn_clear";
            this.btn_clear.Size = new System.Drawing.Size(75, 23);
            this.btn_clear.TabIndex = 2;
            this.btn_clear.Text = "Clear";
            this.btn_clear.UseVisualStyleBackColor = true;
            this.btn_clear.Click += new System.EventHandler(this.btn_clear_Click);
            // 
            // txtMonitor
            // 
            this.txtMonitor.BackColor = System.Drawing.SystemColors.Window;
            this.txtMonitor.Location = new System.Drawing.Point(15, 175);
            this.txtMonitor.Multiline = true;
            this.txtMonitor.Name = "txtMonitor";
            this.txtMonitor.ReadOnly = true;
            this.txtMonitor.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtMonitor.Size = new System.Drawing.Size(412, 168);
            this.txtMonitor.TabIndex = 0;
            this.txtMonitor.TabStop = false;
            this.txtMonitor.WordWrap = false;
            // 
            // lstNewFiles
            // 
            this.lstNewFiles.FormattingEnabled = true;
            this.lstNewFiles.Location = new System.Drawing.Point(15, 25);
            this.lstNewFiles.Name = "lstNewFiles";
            this.lstNewFiles.SelectionMode = System.Windows.Forms.SelectionMode.None;
            this.lstNewFiles.Size = new System.Drawing.Size(412, 121);
            this.lstNewFiles.TabIndex = 0;
            this.lstNewFiles.TabStop = false;
            // 
            // lbl_new
            // 
            this.lbl_new.AutoSize = true;
            this.lbl_new.Location = new System.Drawing.Point(12, 9);
            this.lbl_new.Name = "lbl_new";
            this.lbl_new.Size = new System.Drawing.Size(62, 13);
            this.lbl_new.TabIndex = 0;
            this.lbl_new.Text = "New File(s):";
            // 
            // lbl_changes
            // 
            this.lbl_changes.AutoSize = true;
            this.lbl_changes.Location = new System.Drawing.Point(12, 159);
            this.lbl_changes.Name = "lbl_changes";
            this.lbl_changes.Size = new System.Drawing.Size(71, 13);
            this.lbl_changes.TabIndex = 0;
            this.lbl_changes.Text = "File Changes:";
            // 
            // timer
            // 
            this.timer.Interval = 500;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // FileWatcher
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(442, 388);
            this.Controls.Add(this.lbl_changes);
            this.Controls.Add(this.lbl_new);
            this.Controls.Add(this.lstNewFiles);
            this.Controls.Add(this.txtMonitor);
            this.Controls.Add(this.btn_clear);
            this.Controls.Add(this.btn_stop);
            this.Controls.Add(this.btn_start);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimumSize = new System.Drawing.Size(448, 380);
            this.Name = "FileWatcher";
            this.Text = "File System Watcher";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FileWatcher_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_start;
        private System.Windows.Forms.Button btn_stop;
        private System.Windows.Forms.Button btn_clear;
        private System.Windows.Forms.TextBox txtMonitor;
        private System.Windows.Forms.ListBox lstNewFiles;
        private System.Windows.Forms.Label lbl_new;
        private System.Windows.Forms.Label lbl_changes;
        private System.Windows.Forms.Timer timer;

    }
}