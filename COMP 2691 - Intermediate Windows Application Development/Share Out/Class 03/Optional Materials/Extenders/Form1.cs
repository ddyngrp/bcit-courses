using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace MsdnMag.Extenders
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private MsdnMag.ExtenderLib.AutoColorTextBox autoColorTextBox1;
		private MsdnMag.ExtenderLib.AutoColorTextBox autoColorTextBox2;
		private MsdnMag.ExtenderLib.AutoColorTextBox autoColorTextBox3;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.TextBox textBox1;
		private MsdnMag.ExtenderLib.AutoNumericTextBox autoNumericTextBox1;
		private Samples.TextBoxExtender textBoxExtender1;
		private Samples.BalloonToolTip balloonToolTip1;
		private System.ComponentModel.IContainer components;

		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.autoColorTextBox1 = new MsdnMag.ExtenderLib.AutoColorTextBox();
			this.autoColorTextBox2 = new MsdnMag.ExtenderLib.AutoColorTextBox();
			this.autoColorTextBox3 = new MsdnMag.ExtenderLib.AutoColorTextBox();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.button1 = new System.Windows.Forms.Button();
			this.autoNumericTextBox1 = new MsdnMag.ExtenderLib.AutoNumericTextBox();
			this.textBoxExtender1 = new Samples.TextBoxExtender();
			this.balloonToolTip1 = new Samples.BalloonToolTip();
			this.SuspendLayout();
			// 
			// autoColorTextBox1
			// 
			this.balloonToolTip1.SetBalloonText(this.autoColorTextBox1, "");
			this.autoColorTextBox1.Location = new System.Drawing.Point(16, 16);
			this.autoColorTextBox1.Name = "autoColorTextBox1";
			this.textBoxExtender1.SetSelectedBackColor(this.autoColorTextBox1, System.Drawing.Color.PaleTurquoise);
			this.textBoxExtender1.SetSelectedForeColor(this.autoColorTextBox1, System.Drawing.Color.Black);
			this.autoColorTextBox1.Size = new System.Drawing.Size(248, 20);
			this.autoColorTextBox1.TabIndex = 0;
			this.autoColorTextBox1.Text = "autoColorTextBox1";
			// 
			// autoColorTextBox2
			// 
			this.balloonToolTip1.SetBalloonText(this.autoColorTextBox2, "");
			this.autoColorTextBox2.Location = new System.Drawing.Point(16, 48);
			this.autoColorTextBox2.Name = "autoColorTextBox2";
			this.textBoxExtender1.SetSelectedBackColor(this.autoColorTextBox2, System.Drawing.Color.Blue);
			this.textBoxExtender1.SetSelectedForeColor(this.autoColorTextBox2, System.Drawing.Color.White);
			this.autoColorTextBox2.Size = new System.Drawing.Size(248, 20);
			this.autoColorTextBox2.TabIndex = 1;
			this.autoColorTextBox2.Text = "autoColorTextBox2";
			// 
			// autoColorTextBox3
			// 
			this.balloonToolTip1.SetBalloonText(this.autoColorTextBox3, "");
			this.autoColorTextBox3.Location = new System.Drawing.Point(16, 80);
			this.autoColorTextBox3.Name = "autoColorTextBox3";
			this.textBoxExtender1.SetSelectedBackColor(this.autoColorTextBox3, System.Drawing.Color.Cyan);
			this.textBoxExtender1.SetSelectedForeColor(this.autoColorTextBox3, System.Drawing.Color.Black);
			this.autoColorTextBox3.Size = new System.Drawing.Size(248, 20);
			this.autoColorTextBox3.TabIndex = 2;
			this.autoColorTextBox3.Text = "autoColorTextBox3";
			// 
			// textBox1
			// 
			this.balloonToolTip1.SetBalloonText(this.textBox1, "");
			this.textBox1.Location = new System.Drawing.Point(16, 112);
			this.textBox1.Name = "textBox1";
			this.textBoxExtender1.SetSelectedBackColor(this.textBox1, System.Drawing.Color.Cyan);
			this.textBoxExtender1.SetSelectedForeColor(this.textBox1, System.Drawing.Color.Black);
			this.textBox1.Size = new System.Drawing.Size(248, 20);
			this.textBox1.TabIndex = 3;
			this.textBox1.Text = "textBox1";
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(152, 168);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(120, 24);
			this.button1.TabIndex = 5;
			this.button1.Text = "(Pretend to) Submit";
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// autoNumericTextBox1
			// 
			this.balloonToolTip1.SetBalloonText(this.autoNumericTextBox1, "");
			this.autoNumericTextBox1.Location = new System.Drawing.Point(152, 144);
			this.autoNumericTextBox1.Name = "autoNumericTextBox1";
			this.textBoxExtender1.SetSelectedBackColor(this.autoNumericTextBox1, System.Drawing.Color.Cyan);
			this.textBoxExtender1.SetSelectedForeColor(this.autoNumericTextBox1, System.Drawing.Color.Black);
			this.autoNumericTextBox1.Size = new System.Drawing.Size(112, 20);
			this.autoNumericTextBox1.TabIndex = 4;
			this.autoNumericTextBox1.Text = "1";
			this.autoNumericTextBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
			// 
			// textBoxExtender1
			// 
			this.textBoxExtender1.SelectedBackColor = System.Drawing.Color.Cyan;
			this.textBoxExtender1.SelectedForeColor = System.Drawing.Color.Empty;
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(280, 197);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.autoColorTextBox3);
			this.Controls.Add(this.autoColorTextBox2);
			this.Controls.Add(this.autoColorTextBox1);
			this.Controls.Add(this.autoNumericTextBox1);
			this.Controls.Add(this.button1);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

		private void Form1_Load(object sender, System.EventArgs e)
		{
			//autoColorTextBox1.SelectedBackColor = Color.Cyan;
			//autoColorTextBox2.SelectedBackColor = Color.Yellow;
			//autoColorTextBox3.SelectedBackColor = Color.LightGreen;
			autoNumericTextBox1.NumericMode = true;
			//autoNumericTextBox1.SelectedBackColor = Color.LightGreen;
			autoNumericTextBox1.LostFocus += new EventHandler(autoNumericTextBox1_LostFocus); 
		}

		private void button1_Click(object sender, System.EventArgs e)
		{
		}

		private void autoNumericTextBox1_LostFocus(object sender, EventArgs e)
		{
		}
	}
}
