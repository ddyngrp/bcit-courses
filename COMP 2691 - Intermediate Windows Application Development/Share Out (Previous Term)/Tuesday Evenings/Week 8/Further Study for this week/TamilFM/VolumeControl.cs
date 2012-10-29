
using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace TamilFM
{
    /// <summary>
    /// volume control event delegate
    /// </summary>
    public delegate void volumeChanged();
    /// <summary>
    /// volume control class
    /// </summary>
    public partial class VolumeControl : ProgressBar
    {
        private bool bFlag = false;
        /// <summary>
        /// volume changed event
        /// </summary>
        public event volumeChanged VolumeChanged = null;

        #region Constructors
        public VolumeControl()
        {
            InitializeComponent();
        } 
        #endregion

        #region Override methods
        /// <param name="e">A <see cref="T:System.Windows.Forms.MouseEventArgs"></see> that contains the event data.</param>
        protected override void OnMouseDown(System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                bFlag = true;
                int iPer = (int)(((float)e.X / (float)Width) * (float)(Maximum - Minimum));
                if (iPer + Minimum > Maximum)
                {
                    Value = Maximum;
                }
                else if (iPer + Minimum < Minimum)
                {
                    Value = Minimum;
                }
                else
                {
                    Value = iPer + Minimum;
                }
            }
        }

        /// <param name="e">A <see cref="T:System.Windows.Forms.MouseEventArgs"></see> that contains the event data.</param>
        protected override void OnMouseMove(System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left && bFlag == true)
            {
                int iPer = (int)(((float)e.X / (float)Width) * (float)(Maximum - Minimum));
                if (iPer + Minimum > Maximum)
                {
                    Value = Maximum;
                }
                else if (iPer + Minimum < Minimum)
                {
                    Value = Minimum;
                }
                else
                {
                    Value = iPer + Minimum;
                }
            }
        }

        /// <param name="e">A <see cref="T:System.Windows.Forms.MouseEventArgs"></see> that contains the event data.</param>
        protected override void OnMouseUp(System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                bFlag = false;
                if (VolumeChanged != null)
                {
                    VolumeChanged();
                }
            }
        } 
        #endregion
    }
}
