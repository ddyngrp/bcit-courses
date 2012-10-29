using System;
using System.Drawing;
using System.Windows.Forms;

/* ----------------------------------------------------------------------
	Define a Delegate type, to indicate signature of method to call
	----------------------------------------------------------------------*/
delegate void DrawShape(Brush aBrush , Rectangle aRect);


	/// <summary>
	/// Summary description for UsingDelegates.
	/// </summary>
public class UsingDelegates : System.Windows.Forms.Form
{
	private System.Windows.Forms.TextBox txtLeft;
	private System.Windows.Forms.TextBox txtTop;
	private System.Windows.Forms.TextBox txtWidth;
	private System.Windows.Forms.TextBox txtHeight;
	private System.Windows.Forms.Label lblTop;
	private System.Windows.Forms.Label lblLeft;
	private System.Windows.Forms.Label lblWidth;
	private System.Windows.Forms.Label lblHeight;
	private System.Windows.Forms.Button btnColor;
	private System.Windows.Forms.Button btnDrawEll;
	private System.Windows.Forms.Button btnDrawRect;
	/// <summary>
	/// Required designer variable.
	/// </summary>
	private System.ComponentModel.Container components = null;

	public UsingDelegates()
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
        this.txtLeft = new System.Windows.Forms.TextBox();
        this.txtTop = new System.Windows.Forms.TextBox();
        this.txtWidth = new System.Windows.Forms.TextBox();
        this.txtHeight = new System.Windows.Forms.TextBox();
        this.lblTop = new System.Windows.Forms.Label();
        this.lblLeft = new System.Windows.Forms.Label();
        this.lblWidth = new System.Windows.Forms.Label();
        this.lblHeight = new System.Windows.Forms.Label();
        this.btnColor = new System.Windows.Forms.Button();
        this.btnDrawEll = new System.Windows.Forms.Button();
        this.btnDrawRect = new System.Windows.Forms.Button();
        this.SuspendLayout();
        // 
        // txtLeft
        // 
        this.txtLeft.Location = new System.Drawing.Point(64, 248);
        this.txtLeft.Name = "txtLeft";
        this.txtLeft.Size = new System.Drawing.Size(32, 20);
        this.txtLeft.TabIndex = 0;
        this.txtLeft.Text = "120";
        // 
        // txtTop
        // 
        this.txtTop.Location = new System.Drawing.Point(176, 248);
        this.txtTop.Name = "txtTop";
        this.txtTop.Size = new System.Drawing.Size(32, 20);
        this.txtTop.TabIndex = 1;
        this.txtTop.Text = "120";
        // 
        // txtWidth
        // 
        this.txtWidth.Location = new System.Drawing.Point(64, 280);
        this.txtWidth.Name = "txtWidth";
        this.txtWidth.Size = new System.Drawing.Size(32, 20);
        this.txtWidth.TabIndex = 2;
        this.txtWidth.Text = "30";
        // 
        // txtHeight
        // 
        this.txtHeight.Location = new System.Drawing.Point(176, 280);
        this.txtHeight.Name = "txtHeight";
        this.txtHeight.Size = new System.Drawing.Size(32, 20);
        this.txtHeight.TabIndex = 3;
        this.txtHeight.Text = "30";
        // 
        // lblTop
        // 
        this.lblTop.Location = new System.Drawing.Point(136, 248);
        this.lblTop.Name = "lblTop";
        this.lblTop.Size = new System.Drawing.Size(32, 23);
        this.lblTop.TabIndex = 4;
        this.lblTop.Text = "Top";
        // 
        // lblLeft
        // 
        this.lblLeft.Location = new System.Drawing.Point(16, 248);
        this.lblLeft.Name = "lblLeft";
        this.lblLeft.Size = new System.Drawing.Size(48, 23);
        this.lblLeft.TabIndex = 5;
        this.lblLeft.Text = "Left";
        // 
        // lblWidth
        // 
        this.lblWidth.Location = new System.Drawing.Point(16, 280);
        this.lblWidth.Name = "lblWidth";
        this.lblWidth.Size = new System.Drawing.Size(48, 23);
        this.lblWidth.TabIndex = 6;
        this.lblWidth.Text = "Width";
        // 
        // lblHeight
        // 
        this.lblHeight.Location = new System.Drawing.Point(136, 280);
        this.lblHeight.Name = "lblHeight";
        this.lblHeight.Size = new System.Drawing.Size(40, 23);
        this.lblHeight.TabIndex = 7;
        this.lblHeight.Text = "Height";
        // 
        // btnColor
        // 
        this.btnColor.Location = new System.Drawing.Point(248, 248);
        this.btnColor.Name = "btnColor";
        this.btnColor.Size = new System.Drawing.Size(104, 56);
        this.btnColor.TabIndex = 8;
        this.btnColor.Text = "Color";
        this.btnColor.Click += new System.EventHandler(this.btnColor_Click);
        // 
        // btnDrawEll
        // 
        this.btnDrawEll.Location = new System.Drawing.Point(192, 320);
        this.btnDrawEll.Name = "btnDrawEll";
        this.btnDrawEll.Size = new System.Drawing.Size(120, 23);
        this.btnDrawEll.TabIndex = 9;
        this.btnDrawEll.Text = "Draw Ellipse";
        this.btnDrawEll.Click += new System.EventHandler(this.btnDrawEll_Click);
        // 
        // btnDrawRect
        // 
        this.btnDrawRect.Location = new System.Drawing.Point(48, 320);
        this.btnDrawRect.Name = "btnDrawRect";
        this.btnDrawRect.Size = new System.Drawing.Size(112, 23);
        this.btnDrawRect.TabIndex = 10;
        this.btnDrawRect.Text = "Draw rectangle";
        this.btnDrawRect.Click += new System.EventHandler(this.btnDrawRect_Click);
        // 
        // UsingDelegates
        // 
        this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
        this.ClientSize = new System.Drawing.Size(400, 349);
        this.Controls.Add(this.btnDrawRect);
        this.Controls.Add(this.btnDrawEll);
        this.Controls.Add(this.btnColor);
        this.Controls.Add(this.lblHeight);
        this.Controls.Add(this.lblWidth);
        this.Controls.Add(this.lblLeft);
        this.Controls.Add(this.lblTop);
        this.Controls.Add(this.txtHeight);
        this.Controls.Add(this.txtWidth);
        this.Controls.Add(this.txtTop);
        this.Controls.Add(this.txtLeft);
        this.Name = "UsingDelegates";
        this.Text = "Using Delegates";
        this.Paint += new System.Windows.Forms.PaintEventHandler(this.UsingDelegates_Paint);
        this.ResumeLayout(false);
        this.PerformLayout();

	}
		#endregion

	/// <summary>
	/// The main entry point for the application.
	/// </summary>
	[STAThread]
	static void Main() 
	{
		Application.Run(new UsingDelegates());
	}

	/*----------------------------------------------------------------
		 Declare a Rectangle field, to indicate available drawing area
		 ----------------------------------------------------------------*/
	private Rectangle mRect;

	/* ----------------------------------------------------------------
		 When the form receives a paint event, color the available drawing area white
		 ----------------------------------------------------------------*/
	private void UsingDelegates_Paint(object sender, System.Windows.Forms.PaintEventArgs e)
	{
		mRect = new Rectangle(0, 0, Width, Height / 2);
		e.Graphics.FillRectangle(new SolidBrush(Color.White), mRect);
	}

	private void btnColor_Click(object sender, System.EventArgs e)
	{
		ColorDialog dlgColor = new ColorDialog();
		dlgColor.ShowDialog(this);
		btnColor.BackColor = dlgColor.Color;

	}


	/* ----------------------------------------------------------------
		 Handle the Click event for the btnDrawRect button
		 ----------------------------------------------------------------*/
	private void btnDrawRect_Click(object sender, System.EventArgs e)
	{
		// Create a Graphics object (we need its FillRectangle method)
		Graphics aGraphics = CreateGraphics();

		// Declare a MyDelegate variable
		DrawShape DrawRectangleMethod;

		// Create a delegate object, and bind to the FillRectangle method
		DrawRectangleMethod = new DrawShape(aGraphics.FillRectangle);

		// Call MyDrawShape, and pass the delegate as a parameter
		MyDrawShape(DrawRectangleMethod);
	}

	/* ----------------------------------------------------------------
		 Handle the Click event for the btnDrawEll button
		 ----------------------------------------------------------------*/
	private void btnDrawEll_Click(object sender, System.EventArgs e)
	{
		// Use a shorter but more cryptic syntax.
		MyDrawShape(new DrawShape(CreateGraphics().FillEllipse));
	}
	/* ----------------------------------------------------------------------
		 MyDrawShape uses a delegate to indicate which method to call
		 ----------------------------------------------------------------------*/
	private void MyDrawShape(DrawShape theDelegate )
	{
		// Are any text fields blank?
		if (txtLeft.Text.Length == 0 || txtTop.Text.Length == 0 || 
			txtWidth.Text.Length == 0 || txtHeight.Text.Length == 0)
		{
			MessageBox.Show("Please fill in all text boxes", 
				"Error",
				MessageBoxButtons.OK,
				MessageBoxIcon.Error);
			return;
		}

		// Get the coordinate values entered in the text fields
		Rectangle aRect = new Rectangle(Int32.Parse(txtLeft.Text), Int32.Parse(txtTop.Text), 
			Int32.Parse(txtWidth.Text),	Int32.Parse(txtHeight.Text));
		// Make sure the coordinates are in range
		if (mRect.Contains(aRect))
		{
			// Get the color of the btnColor button
			Brush aBrush = new SolidBrush(btnColor.BackColor);
			// Call the delegate, to draw the specified shape
			theDelegate(aBrush, aRect);
		}
		else
		{
			// Display error message, and return immediately 
			MessageBox.Show("Coordinates are outside drawing area", "Error", 
				MessageBoxButtons.OK, MessageBoxIcon.Error);
		}
	}

}
