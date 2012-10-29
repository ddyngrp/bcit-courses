using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WeekThree
{
    public partial class PainterForm : Form
    {
        bool shouldPaint = false; // determines whether to paint

        
        public PainterForm()
        {
            InitializeComponent();
        }

        private void PainterForm_MouseDown(object sender, MouseEventArgs e)
        {
            shouldPaint = true;    // end method Painter_MouseDown
        }

        private void PainterForm_MouseUp(object sender, MouseEventArgs e)
        {
            shouldPaint = false; 
        }

        private void PainterForm_MouseMove(object sender, MouseEventArgs e)
        {
           if ( shouldPaint ) // check if mouse button is being pressed
            {
                 // draw a circle where the mouse pointer is present
                 Graphics graphics = CreateGraphics();
                 graphics.FillEllipse(
                    new SolidBrush( Color.BlueViolet ), e.X, e.Y, 20, 20 );
                 graphics.Dispose();
            } // end if
         } // end method Painter_MouseMove

        
    }
}