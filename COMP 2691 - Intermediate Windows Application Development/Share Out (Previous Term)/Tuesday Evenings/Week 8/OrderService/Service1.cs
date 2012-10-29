using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.ServiceProcess;
using System.Text;
using System.Data.SqlClient;
using System.IO;

namespace WindowsService_SectionTen
{
    public partial class Service1 : ServiceBase
    {

        private System.IO.FileSystemWatcher fswOrders;
        /// <summary> 
        /// Required designer variable.
        /// </summary>
     
        public Service1()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            // TODO: Add code here to start your service.
            fswOrders.EnableRaisingEvents = true;
        }

        protected override void OnStop()
        {
            // TODO: Add code here to perform any tear-down necessary to stop your service.
            fswOrders.EnableRaisingEvents = false;
        }

        private void fswOrders_Created(object sender,
            System.IO.FileSystemEventArgs e)
        {
            DataSet dsOrders = new DataSet("Orders");
            // Read the contents of the XML file
            // into the Orders DataSet
            dsOrders.ReadXml(e.FullPath);

            // setup the database connection string
            string strConn = "data source=(local);" +
                "initial catalog=Northwind;" +
                "integrated security=SSPI";
            string strOrderQuery = "Select * from orders";
            // Create a DataAdapter for the Orders
            // table of the Northwind database
            SqlDataAdapter daOrders =
                new SqlDataAdapter(strOrderQuery, strConn);
            // Automatically generate the update
            // command to reconcile the changes 
            // made to the DataSet
            SqlCommandBuilder cbOrders =
                new SqlCommandBuilder(daOrders);
            //Update the DataSet
            daOrders.Update(dsOrders, "Orders");
            daOrders.Dispose();

            FileInfo fi = new FileInfo(e.FullPath);
            // Create a subdirectory named "Updated"
            // if it does not already exist
            fi.Directory.CreateSubdirectory("Updated");
            // Copy the processed XML file to updated
            // directory, overwriting if needed
            File.Copy(e.FullPath, fi.DirectoryName +
                @"\Updated\" + fi.Name, true);
            // Delete the XML file from its 
            // original location
            fi.Delete();
        }

    }
}
