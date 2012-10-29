using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace GUIConceptsPart2
{
    public partial class TabControl : Form
    {
        private int intTabIndex = 0;

        public TabControl()
        {
            InitializeComponent();
        }

        private void btnAddTab_Click(object sender, EventArgs e)
        {
            //add a new tabpage as the last tab
            intTabIndex++;
            tabControlTest.Controls.Add(new TabPage("new Page " + intTabIndex.ToString()));

        }

        private void btnRemoveTab_Click(object sender, EventArgs e)
        {
            // remove the selected tab
            tabControlTest.Controls.Remove(tabControlTest.SelectedTab);


        }

        private void btnInsertTab_Click(object sender, EventArgs e)
        {
           // There does not appear to be support in the framework 
           // for inserting a tab at a particular position. 
           // A work around might be to save the current tabpage 
           // controls, clear the Controls collection, and then add
           // the saved controls back to the Controls collection 
           // inserting a new tab. Here is some code that does this.
            int limit = tabControlTest.Controls.Count;
      
            if (limit <= 0)
            {
                tabControlTest.Controls.Add(new TabPage("First Page"));
                return;
            }

            int target = tabControlTest.SelectedIndex;

            // save the exisiting pages & clear the controls
            Control[] c = new Control[limit];
            tabControlTest.Controls.CopyTo(c, 0);
            tabControlTest.Controls.Clear();

            // add the earlier pages
            for (int i = 0; i < target; ++i)
                tabControlTest.Controls.Add(c[i]);

            // insert the page
            tabControlTest.Controls.Add(new TabPage("Inserted Page"));

            // add the later pages
            for (int i = target; i < limit; ++i)
                tabControlTest.Controls.Add(c[i]);

            // select the new page
            tabControlTest.SelectedIndex = target;


        }

        private void btnColorTabs_Click(object sender, EventArgs e)
        {
            // Set the TabControl's DrawMode to OwnerDraw, 
            // and then handle the DrawItem event             
            this.tabControlTest.DrawMode = System.Windows.Forms.TabDrawMode.OwnerDrawFixed;
            this.tabControlTest.DrawItem += new DrawItemEventHandler(this.tabControl1_DrawItem);
        }
        private void tabControl1_DrawItem(object sender, System.Windows.Forms.DrawItemEventArgs e)
        {
            Font f;
            Brush backBrush;
            Brush foreBrush;

            if (e.Index == this.tabControlTest.SelectedIndex)
            {
                f = new Font(e.Font, FontStyle.Italic | FontStyle.Bold);
                // display a gradient tab for the active tabpage. 
                backBrush = new System.Drawing.Drawing2D.LinearGradientBrush(e.Bounds, Color.Blue, Color.Red, System.Drawing.Drawing2D.LinearGradientMode.BackwardDiagonal);
                foreBrush = Brushes.PowderBlue;
            }
            else
            {
                f = e.Font;
                backBrush = new SolidBrush(e.BackColor);
                foreBrush = new SolidBrush(e.ForeColor);
            }

            string tabName = this.tabControlTest.TabPages[e.Index].Text;
            StringFormat sf = new StringFormat();
            sf.Alignment = StringAlignment.Center;
            e.Graphics.FillRectangle(backBrush, e.Bounds);
            Rectangle r = e.Bounds;
            r = new Rectangle(r.X, r.Y + 3, r.Width, r.Height - 3);
            e.Graphics.DrawString(tabName, f, foreBrush, r, sf);

            sf.Dispose();
            if (e.Index == this.tabControlTest.SelectedIndex)
            {
                f.Dispose();
                backBrush.Dispose();
            }
            else
            {
                backBrush.Dispose();
                foreBrush.Dispose();
            }
        }
    
    }
}