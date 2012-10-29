using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Configuration;
using System.Data.SqlClient;

using System.Threading;

namespace Threading.ADONetSamples.Async
{
    public partial class Callback_ThreadSafe : Form
    {
        SqlCommand _cmd;
        StringBuilder sb = new StringBuilder("");

        private Thread ResultsThread = null;
        delegate void SetTextCallback(string text);
        
        public Callback_ThreadSafe()
        {
            InitializeComponent();
        }

        private void btnExecute_Click(object sender, EventArgs e)
        {
            //string connString = "Async=true;SERVER=(local);DATABASE=northwind;UID=sa;";
            string connString = "Async=true;SERVER=www.j2ee.ca;DATABASE=northwind;uid=aspx;password=aspx;";

            SqlConnection conn = new SqlConnection(connString);
            SqlCommand cmd = new SqlCommand("SELECT lastname,firstname FROM employees", conn);
            _cmd = cmd;
            
            conn.Open();
            AsyncCallback callback = new AsyncCallback(ProcessData);
            IAsyncResult iar = cmd.BeginExecuteReader(callback, null);

            iar.AsyncWaitHandle.WaitOne();

                        
        }
        protected void ProcessData(IAsyncResult iar)
        {
            SqlDataReader reader = _cmd.EndExecuteReader(iar);

       
            while (reader.Read())
                sb.AppendFormat("{0}, {1} \n", reader[0], reader[1]);
            
            reader.Close();

            // Results.Text = sb.ToString() does not work here
            // Error: Cross-thread operation not valid: Control 'Results' 
            // accessed from a thread other than the thread it was created on.
            // If you use multithreading to improve the performance your Windows Forms applications,
            // you must be careful to make calls to your controls in a thread-safe way.
            this.ResultsThread = new Thread(new ThreadStart(this.ThreadProcSafe));
            this.ResultsThread.Start();
            
            _cmd.Connection.Close();
        }

        private void ThreadProcSafe()
        {
            
            this.SetText(sb.ToString());   //Results.Text = sb.ToString();
        }
        private void SetText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (this.Results.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.Results.Text = text;
            }
        }

    }
}