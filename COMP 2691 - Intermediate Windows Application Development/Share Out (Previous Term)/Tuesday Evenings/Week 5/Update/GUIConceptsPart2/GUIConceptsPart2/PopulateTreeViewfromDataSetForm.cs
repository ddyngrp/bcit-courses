using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Data.OleDb;
using System.Drawing;
using System.Text;
using System.Windows.Forms;



namespace GUIConceptsPart2
{
    public partial class PopulateTreeViewfromDataSetForm : Form
    {
        public PopulateTreeViewfromDataSetForm()
        {
            InitializeComponent();
        }

        private void btnPopulate_Click(object sender, EventArgs e)
        {
            
            // Connection String
            // Method 1
            
            // To the attached mdf file
            //String strConn = "Server = .\\SQLEXPRESS;";
            //strConn += "AttachDbFilename=|DataDirectory|" + "\\northwind.mdf;";
            //strConn += "Integrated Security=True;Connect Timeout=30;User Instance=True;";
            
            // To the www.j2ee.ca
            String strConn = "Server=www.j2ee.ca;";
            strConn += "database=northwind;";
            strConn += "uid=aspx;password=aspx;";

            // To the local SQL server
            
            // If you do not have the samples, download them from microsoft website and attach them 
            // to the SQL server
            //String strConn = "Data Source=(local);";
            //strConn += "database=northwind;";
            //strConn += "Trusted_Connection=No;uid=john;pwd=doe;";

            // To the NorthWind mdb file
            //String strConn = "Provider=Microsoft.Jet.OleDb.4.0;";
            //strConn += "Data Source=|DataDirectory|" + "\\NorthWind.mdb;";
        
            

            // Method 2
            //SqlConnectionStringBuilder conStrBuilder = new SqlConnectionStringBuilder();
            //conStrBuilder.DataSource = ".\\SQLEXPRESS";
            //conStrBuilder.AttachDBFilename = "|DataDirectory|" +"\\northwind.mdf";
            //conStrBuilder.IntegratedSecurity = true;
            //conStrBuilder.ConnectTimeout = 30;
            //conStrBuilder.UserInstance = true;
            //string strConn = conStrBuilder.ToString();
            
            // Method 3
            // string strConn = Properties.Settings.Default.northwindConnectionString;

            // For SQL provider
            SqlConnection conn = new SqlConnection(strConn);
            SqlDataAdapter daProducts = new SqlDataAdapter("Select * from Products", conn);
            SqlDataAdapter daCategories = new SqlDataAdapter("Select * from Categories", conn);

            // For OLEDB Provider
            //OleDbConnection conn = new OleDbConnection(strConn);
            //OleDbDataAdapter daProducts = new OleDbDataAdapter("Select * from Products", conn);
            //OleDbDataAdapter daCategories = new OleDbDataAdapter("Select * from Categories", conn);

            
            DataSet ds = new DataSet("MyDataSet");
            daProducts.Fill(ds, "Products");
            daCategories.Fill(ds, "Categories");
            ds.Relations.Add("Cat_Product", ds.Tables["Categories"].Columns["CategoryID"],
                                            ds.Tables["Products"].Columns["CategoryID"]);

            foreach (DataRow dr in ds.Tables["Categories"].Rows)
            {
                TreeNode tn = new TreeNode(dr["CategoryName"].ToString());
                foreach (DataRow drChild in dr.GetChildRows("Cat_Product"))
                {
                    tn.Nodes.Add(drChild["ProductName"].ToString());
                }
                treeView1.Nodes.Add(tn);
            }
            
            
            
            
            
            //string strConn = Properties.Settings.Default.northwindConnectionString;

            //this.treeView1.Nodes.Add("Customers");


            //DataTable myTable = new DataTable("myTable");

            //using (SqlConnection conn = new SqlConnection(strConn))
            //{

            //    conn.Open();
            //    SqlCommand cmd = new SqlCommand
            //                                  (@"SELECT * FROM Customers", conn);

            //    SqlDataReader rd = cmd.ExecuteReader();

            //    myTable.Load(rd);
            //    //this was only possible with DataSet object earlier ----Cool eh ;)


            //    foreach (DataRow row in myTable.Rows)
            //    {

            //        TreeNode node = new TreeNode(row[0].ToString());

            //        this.treeView1.Nodes[0].Nodes.Add(node);

            //        this.treeView1.Sorted = true;

            //    }

            //    conn.Close();

            //}



        }
    }
}