using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SectionThree
{
    public partial class PainterForm : Form
    {
        bool shouldPaint = false; // determines whether to paint

        // should paint when mouse button is pressed down
        private void PainterForm_MouseDown(object sender, MouseEventArgs e)
        { shouldPaint = true; } // end method Painter_MouseDown
        // stop painting when mouse button is released
        private void PainterForm_MouseUp(object sender, MouseEventArgs e)
        {
            shouldPaint = false;
        } // end method Painter_MouseUp
        // draw circle whenever mouse moves with its button held down        
        private void PainterForm_MouseMove(object sender, MouseEventArgs e)
        {
            if (shouldPaint) // check if mouse button is being pressed
            {
                // draw a circle where the mouse pointer is present
                Graphics graphics = CreateGraphics();
                graphics.FillEllipse(
                   new SolidBrush(Color.BlueViolet), e.X, e.Y, 4, 4);
                graphics.Dispose();
            } // end if
        } // end method Painter_MouseMove
        public PainterForm()
        {
            InitializeComponent();
        }
    }
}