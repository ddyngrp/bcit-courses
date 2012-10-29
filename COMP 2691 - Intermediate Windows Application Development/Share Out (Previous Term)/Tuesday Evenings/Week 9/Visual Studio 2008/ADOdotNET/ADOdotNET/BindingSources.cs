using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ADOdotNET.DAL;

namespace ADOdotNET
{
    public partial class BindingSources : Form
    {
        BindingSource bsEmployees;

        public BindingSources()
        {
            InitializeComponent();
        }

        private void btnCreateEmployees_Click(object sender, EventArgs e)
        {
            
            bsEmployees = new BindingSource();
            
            EmployeesManager objEmployeesManager = new EmployeesManager();
            bsEmployees.DataSource = objEmployeesManager.GetListofEmployees();
                     
            tbEmployeeID.DataBindings.Add("Text", bsEmployees, "EmployeeID");
            tbHireDate.DataBindings.Add("Text", bsEmployees, "HireDate");
            tbFullName.DataBindings.Add("Text", bsEmployees, "FullName");
            pictureBox1.DataBindings.Add("Image", bsEmployees, "Photo", true, DataSourceUpdateMode.Never, new Bitmap(typeof(Button),"Button.bmp"));
            
            bsEmployees.PositionChanged += new EventHandler(bsEmployees_PositionChanged);
            bsEmployees_PositionChanged(this, null);
        }
       
        private void bsEmployees_PositionChanged(object sender, EventArgs e)
        {
            txtPosition.Text = (bsEmployees.Position + 1).ToString() + " of "
                + bsEmployees.Count.ToString();
        }

        private void btnFirst_Click(object sender, EventArgs e)
        {
            bsEmployees.MoveFirst();
        }

        private void btnPrevious_Click(object sender, EventArgs e)
        {
            bsEmployees.MovePrevious();
        }

        private void btnNext_Click(object sender, EventArgs e)
        {
            bsEmployees.MoveNext();
        }

        private void btnLast_Click(object sender, EventArgs e)
        {
            bsEmployees.MoveLast();
        }

   

        
    }
}