using System;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;


namespace ADOdotNET.DAL
{

    public class CustomersManager
    {
        // *****************************************************************************
        // Ctor(s)
        public CustomersManager()
        {
        }

        // *****************************************************************************
        // Private member(s)
        //private const string cmdListOfNames = "SELECT employeeid, lastname FROM employees";
        //private const string cmdEmployeeDetails = "SELECT firstname, lastname, title, country, notes FROM employees WHERE employeeid={0}";

        // *****************************************************************************
        // Returns the list of all employees
        public DataTable GetListofNames()
        {
            // Get the lastnames of all employees
            SqlDataAdapter adapter;
            adapter = new SqlDataAdapter(
                CustomerCommandList.cmdListOfNames,
                ConfigurationManager.ConnectionStrings["J2EENWind"].ConnectionString);

            DataTable table = new DataTable();
            adapter.Fill(table);

            return table;
        }


        // Returns the list of all employees
        public DataTable GetListofCustomers()
        {
            // Get the lastnames of all employees
            SqlDataAdapter adapter;
            adapter = new SqlDataAdapter(
                CustomerCommandList.cmdListOfCustomers,
                ConfigurationManager.ConnectionStrings["J2EENWind"].ConnectionString);

            DataTable table = new DataTable();
            adapter.Fill(table);

            return table;
        }
        // *****************************************************************************
        // Returns the list of all employees
        public CustomerInfo GetCustomerDetails(int custID)
        {
            // Get details about the specified employee
            SqlDataAdapter adapter = new SqlDataAdapter(
                String.Format(CustomerCommandList.cmdCustomerDetails, custID),
                ConfigurationManager.ConnectionStrings["J2EENWind"].ConnectionString);
            DataTable table = new DataTable();
            adapter.Fill(table);

            // Execute the command and populate the return buffer
            DataRow row = table.Rows[0];
            CustomerInfo info = new CustomerInfo();
            info.ID = custID;
            info.ContactName = row["contactname"].ToString();
            info.Address = row["address"].ToString();
            info.City = row["city"].ToString();
            info.Country = row["country"].ToString();


            return info;
        }
    }


    public class CustomerCommandList
    {
        public static string cmdListOfNames = "SELECT customerid, contactname FROM customers";
        public static string cmdListOfCustomers = "SELECT customerid, companyname, contactname, country, address FROM customers";


        public static string cmdCustomerDetails = "SELECT companyname, contactname, address, city, country FROM customers WHERE customerid={0}";
    }


    public class CustomerInfo
    {
        public int ID;
        public string ContactName;
        public string Address;
        public string City;
        public string Country;

    }
}