using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Threading.ADONetSamples.Async
{
    public partial class Callback_NotThreadSafe : Form
    {
        SqlCommand _cmd;
        StringBuilder sb = new StringBuilder("");
        
        public Callback_NotThreadSafe()
        {
            InitializeComponent();
            // When a thread other than the creating thread of a control tries to access one of 
            // that control's methods or properties, it often leads to unpredictable results. 
            // A common invalid thread activity is a call on the wrong thread that accesses 
            // the control's Handle property. Set CheckForIllegalCrossThreadCalls to true to find 
            // and diagnose this thread activity more easily while debugging. 
            // Note that illegal cross-thread calls will always raise an exception when an application 
            // is started outside the debugger.
            CheckForIllegalCrossThreadCalls = false;
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
            
            Results.Text = sb.ToString();
             _cmd.Connection.Close();
        }

    }
}