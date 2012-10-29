using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Configuration;
using System.Data.SqlClient;
using ADOdotNET.DAL;
using System.Threading;

namespace ADOdotNET.Async
{
    public partial class Parallel : Form
    {
        protected string ConnString;
        protected string CustomerInfoCmd = "SELECT * FROM customers WHERE customerid=@customerid";
        protected string CustomerOrderHistory = "custorderhist";
        
        public Parallel()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
        }
        private void Parallel_Load(object sender, EventArgs e)
        {
            ConnString = ConfigurationManager.ConnectionStrings["J2EENWind"].ConnectionString;
            SqlConnectionStringBuilder cb = new SqlConnectionStringBuilder(ConnString);
            cb.AsynchronousProcessing = true;
            ConnString = cb.ConnectionString;

            LoadCustomers();
        }
        protected void LoadCustomers()
        {
             //using (SqlConnection conn = new SqlConnection(ConnString))
             //{
             //SqlCommand cmd = new SqlCommand("SELECT companyname,customerid FROM customers", conn);
             //cmd.Connection.Open();
             //SqlDataReader reader = cmd.ExecuteReader();
             //CustomerList.DataSource = reader;
             //CustomerList.DisplayMember = "CompanyName";    //Does not work!
             //CustomerList.ValueMember = "CustomerId";       //Does not work!
             // cmd.Connection.Close();
             //}

            // CustomerList.DataSource = reader;
            // the DataReader is connected only, read only & forward only data.  
            // Well, if you were wondering if it could be bound to in WindowsForms, 
            // you thought right.  It definitely CAN NOT be bound to, because again, 
            // in WindowsForms, you're binding to the actual objects and if you close 
            // a DataReader, then all the data is no longer there.  The other big reason 
            // you wouldn't be able to bind to a DataReader is that only instances that 
            // Implement IList can be bound to in WindowsForms.

            // Add a binding source to be able to use the northwind and poulate the DataSet 


            BindingSource bsCustomers;

            bsCustomers = new BindingSource();

            CustomersManager objCustomersManager = new CustomersManager();
            bsCustomers.DataSource = objCustomersManager.GetListofCustomers();


            CustomerList.DataSource = bsCustomers;
            CustomerList.DisplayMember = "CompanyName";
            CustomerList.ValueMember = "CustomerId";         
                
        }
        protected void QueryButton_Click(object sender, EventArgs e)
        {
            // You might want to move this code out to a separate class
            // Using two connection strings to simulate distinct databases

            string custID = CustomerList.SelectedValue.ToString();

            using (SqlConnection conn1 = new SqlConnection(ConnString))
            using (SqlConnection conn2 = new SqlConnection(ConnString))
            {
                // Fire the first command: get customer info
                SqlCommand cmd1 = new SqlCommand(CustomerInfoCmd, conn1);
                cmd1.Parameters.Add("@customerid", SqlDbType.Char, 5).Value = custID;
                conn1.Open();
                IAsyncResult arCustomerInfo = cmd1.BeginExecuteReader();

                // Fire the second command: get order info
                SqlCommand cmd2 = new SqlCommand(CustomerOrderHistory, conn2);
                cmd2.CommandType = CommandType.StoredProcedure;
                cmd2.Parameters.Add("@customerid", SqlDbType.Char, 5).Value = custID;
                conn2.Open();
                IAsyncResult arOrdersInfo = cmd2.BeginExecuteReader();

                // Prepare wait objects to sync up 
                WaitHandle[] handles = new WaitHandle[2];
                handles[0] = arCustomerInfo.AsyncWaitHandle;
                handles[1] = arOrdersInfo.AsyncWaitHandle;
                SqlDataReader reader;

                // Wait (no longer than 5 secs)
                for (int i = 0; i < 2; i++)
                {
                    StringBuilder builder = new StringBuilder();
                    int index = WaitHandle.WaitAny(handles, 5000, false);
                    if (index == WaitHandle.WaitTimeout)
                        throw new Exception("Timeout expired");

                    if (index == 0)
                    {
                        reader = cmd1.EndExecuteReader(arCustomerInfo);

                        // Only one record caught here
                        if (!reader.Read())
                            continue;

                        builder.AppendFormat("Company Name: {0}\n", reader["companyname"]);
                        builder.AppendFormat("Address: {0}\n", reader["address"]);
                        builder.AppendFormat("Country: {0}\n", reader["country"]);
                        Info.Text = builder.ToString();
                        reader.Close();
                    }

                    if (index == 1)
                    {
                  
                        reader = cmd2.EndExecuteReader(arOrdersInfo);


                        // Only one record caught here
                        if (!reader.Read())
                            continue;

                        builder.AppendFormat("Product Name: {0}\n", reader["ProductName"]);
                        builder.AppendFormat("Total: {0}\n", reader["Total"]);
                       
                        MInfo.Text = builder.ToString();
                        reader.Close();

                                                
                    }
                }
            }
        }

        
    }
}