using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WeekThree
{
    public partial class KeyDemoForm : Form
    {
        public KeyDemoForm()
        {
            InitializeComponent();
        }

        private void KeyDemoForm_KeyDown(object sender, KeyEventArgs e)
        {
            keyInfoLabel.Text =
         "Alt: " + (e.Alt ? "Yes" : "No") + '\n' +
         "Shift: " + (e.Shift ? "Yes" : "No") + '\n' +
         "Ctrl: " + (e.Control ? "Yes" : "No") + '\n' +
         "KeyCode: " + e.KeyCode + '\n' +
         "KeyData: " + e.KeyData + '\n' +
         "KeyValue: " + e.KeyValue;
            
           
        }

        private void KeyDemoForm_KeyPress(object sender, KeyPressEventArgs e)
        {
            charLabel.Text = "Key pressed: " + e.KeyChar;
        }

        private void KeyDemoForm_KeyUp(object sender, KeyEventArgs e)
        {
            charLabel.Text = "";
            keyInfoLabel.Text = "";

        }
    }
}