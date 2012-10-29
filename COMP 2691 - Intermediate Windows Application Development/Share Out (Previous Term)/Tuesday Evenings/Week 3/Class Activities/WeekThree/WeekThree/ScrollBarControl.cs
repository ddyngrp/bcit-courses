using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WeekThree
{
    public partial class ScrollBarControl : Form
    {
        public ScrollBarControl()
        {
            InitializeComponent();
        }


        // Do not forget to set the SizeMode of PictureBox to Autosize
        private float getHScrollAdjustment()
        {	//Calculate horizontal scroll bar changes
            float hPos = (float)(hScroll.Value - hScroll.Minimum);
            float hDiff = (float)(hScroll.Width - pbImage.Width);
            float hTicks = (float)(hScroll.Maximum - hScroll.Minimum);
            return (hDiff / hTicks) * hPos;
        }

        private void vScroll_Scroll(object sender, ScrollEventArgs e)
        {
            //Scroll the image vertically
            pbImage.Top = vScroll.Bottom - pbImage.Height - (int)getVScrollAdjustment();
        }

        private float getVScrollAdjustment()
        {
            //Calculate vertical scroll bar changes
            float vPos = (float)(vScroll.Value - vScroll.Minimum);
            float vDiff = (float)(vScroll.Height - pbImage.Height);
            float vTicks = (float)(vScroll.Maximum - vScroll.Minimum);
            return (vDiff / vTicks) * vPos;
        }

        private void hScroll_Scroll(object sender, ScrollEventArgs e)
        {
            //Scroll the image horizontally
            pbImage.Left = hScroll.Right - pbImage.Width - (int)getHScrollAdjustment();
        }

    }
}