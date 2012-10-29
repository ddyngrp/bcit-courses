using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Threading.ADONetSamples.Async
{
    public partial class MultipleCommands : Form
    {


        // You'll need this delegate in order to fill the grid from  a thread other 
        // than the form's thread. See the CallbackHandle procedure for more information.
        private delegate void DelFillGrid(SqlDataReader reader);
        
        // You'll need this delegate in order to display text from a thread
        // other than the form's thread. 
        private delegate void DisplayStatusDelegate(string Text);
        
        // This flag ensures that the user doesn't attempt to restart the command 
        // or close the form while the asynchronous command is executing.
        private bool isExecuting = false;

        private SqlConnection conn = null;

        private void DisplayStatus(string Text)
        {
            this.label1.Text = Text;
        }

        public MultipleCommands()
        {
            InitializeComponent();
        }

        private void btnAsynchronousCall_Click(object sender, EventArgs e)
        {
            if (isExecuting)
            {
                MessageBox.Show(this, "Already executing. Please wait until " +
                    "the current query has completed.");
            }
            else
            {
                SqlCommand command = null;
                try
                {
                    DisplayStatus("Connecting...");
                    //To Execute the command asynchronously we need to make Asynchronous Processing=true
                    conn= new SqlConnection("Data Source=localhost;Integrated Security=SSPI;Initial Catalog=Northwind;Asynchronous Processing=true");
                    command = new SqlCommand();
                    // To emulate a long-running query, wait for a few seconds before working with the data.
                    // This command doesn't do much, but that's the point--it doesn't change your data, 
                    // in the long run.
                    command.CommandText = "WAITFOR DELAY '00:00:05' ; SELECT * FROM Customers"; 
                    
                    command.Connection = conn;	
                    conn.Open();

                    DisplayStatus("Executing...");
                    isExecuting = true;
                              

                    AsyncCallback callback = new AsyncCallback(HandleCallback);
                    // Although it's not required that you pass the SqlCommand object as the second parameter 
                    // in the BeginExecuteNonQuery call, doing so makes it easier to call EndExecuteNonQuery 
                    // in the callback procedure.
                    
                    // Once the BeginExecuteNonQuery method is called, the code continues--and the user can 
                    // interact with the form--while the server executes the query.
                    command.BeginExecuteReader(callback, command);
                }
                catch (Exception ex)
                {
                    isExecuting = false;
                    //DisplayStatus("Error: " + ex.Message);
                    DisplayStatus( string.Format("Ready (last error: {0})", ex.Message));

                    if (conn!= null)
                    {
                        conn.Close();
                    }
                }
            }

        }


        private void FillGrid(SqlDataReader dr)
        {
            try
            {
                DataTable dt = new DataTable();
                dt.Load(dr);
                this.dataGridView1.DataSource = dt;
                //DisplayStatus("Ready");
            }
            catch (Exception ex)
            {
                // Because you're guaranteed this procedure is running from within the form's thread,
                // it can directly interact with members of the form.
                DisplayStatus(string.Format("Ready (last attempt failed: {0})", ex.Message));
            }
            finally
            {
                // Don't forget to close the connection, as well.
                if (dr != null)
                {
                    dr.Close();
                }
                if (conn != null)
                {
                    conn.Close();
                }
            }
        }

        private void HandleCallback(IAsyncResult result)
        {
            try
            {
                // Retrieve the original command object, passed to this procedure in the AsyncState property
                // of the IAsyncResult parameter.
                SqlCommand command = (SqlCommand)result.AsyncState;
                SqlDataReader dr = command.EndExecuteReader(result);
                // To execute the code from a different thread instead of main thread.
                DelFillGrid del = new DelFillGrid(FillGrid);
                // To call the form's delegate.
                this.Invoke(del, dr);
                // Reader is to be closed at the end, as some thread may be using it. Use seperate procedure to close it
            }
            catch (Exception ex)
            {
                // We are running the code in a seperate thread so we need to catch the exception. 
                // Else we are unable to catch the exception anywhere.
                this.Invoke(new DisplayStatusDelegate(DisplayStatus), "Error: " + ex.Message);
            }
            finally
            {
                isExecuting = false;
                if (conn != null)
                {
                    conn.Close();
                }

            }
        }

        private void MultipleCommands_Load(object sender, EventArgs e)
        {
            
            this.btnAsynchronousCall.Click += new System.EventHandler(this.btnAsynchronousCall_Click);
            this.FormClosing += new FormClosingEventHandler(Form1_FormClosing);


        }

        void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (isExecuting)
            {
                MessageBox.Show(this, "Can't close the form until " +
                    "the pending asynchronous command has completed. Please wait...");
                e.Cancel = true;
            }

        }





    }
}