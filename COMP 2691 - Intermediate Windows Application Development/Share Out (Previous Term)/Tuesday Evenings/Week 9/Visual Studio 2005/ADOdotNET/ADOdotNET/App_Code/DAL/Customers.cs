using System;
using System.Data;
using System.Configuration;
using System.Data.SqlClient;
using System.Collections.Generic;
using System.Collections.Specialized;
using ADOdotNET.DAL;



// CUSTOMERS 
// A class to hold customers data and a static class for the behavior according to the 
// Table Data Gateway pattern

namespace ADOdotNET.DAL
{
    // CUSTOMER 
    // Holds information about the customer
    public class Customer
    {
        private string _companyname, _contactname, _contacttitle, _id;
		private string _street, _postalcode, _city, _country, _phone, _region, _fax;

        public Customer()
        {
        }

        #region PROPERTIES

        // ID
        public string ID
        {
            get { return _id; }
            set { _id = value; }
        }

        // CompanyName
        public string CompanyName
        {
            get { return _companyname; }
            set { _companyname = value; }
        }

        // ContactName
        public string ContactName
        {
            get { return _contactname; }
            set { _contactname = value; }
        }

        // ContactTitle
        public string ContactTitle
        {
            get { return _contacttitle; }
            set { _contacttitle = value; }
        }

		// Street
		public string Street
		{
			get { return _street; }
			set { _street = value; }
		}

		// PostalCode
		public string PostalCode
		{
			get { return _postalcode; }
			set { _postalcode = value; }
		}

		// City
		public string City
		{
			get { return _city; }
			set { _city = value; }
		}

		// Country
		public string Country
		{
			get { return _country; }
			set { _country = value; }
		}

		// Phone
		public string Phone
		{
			get { return _phone; }
			set { _phone = value; }
		}

		// Fax
		public string Fax
		{
			get { return _fax; }
			set { _fax = value; }
		}

		// Region
		public string Region
		{
			get { return _region; }
			set { _region = value; }
		}

        #endregion


        #region METHODS

        // ToString
        public override string ToString()
        {
            return String.Format("{0} [{1}]", _companyname, _id);
        }
        #endregion
    }


    public class NoCustomer : Customer
    {
    }


    // CUSTOMERCOLLECTION
    // Collection of customer objects
    public class CustomerCollection : List<Customer>
    {
    }


    // CUSTOMERS--customer gateway
    // Behavior of the customer
    public class Customers
    {
        public static string ConnectionString
        {
            get { return ConfigurationManager.ConnectionStrings["J2EENWind"].ConnectionString; }
        }

        #region METHOD: Load
        // Load
        public static Customer Load(string id)
        {
            if (String.IsNullOrEmpty(id))
                return null; // new NoCustomer();  

            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                SqlCommand cmd = new SqlCommand(CustomerCommands.cmdLoad, conn);
                cmd.Parameters.AddWithValue("@id", id);

                conn.Open();
                SqlDataReader reader = cmd.ExecuteReader();
                reader.Read();
                Customer cust = HelperMethods.GetCustomer(reader);
                reader.Close();
                conn.Close();

                return cust;
            }
        }
        #endregion


        #region METHOD: LoadSet
        // Load
        public static CustomerCollection LoadSet(string match)
        {
            if (String.IsNullOrEmpty(match))
                return LoadAll();

            CustomerCollection coll = new CustomerCollection();

            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                SqlCommand cmd = new SqlCommand(CustomerCommands.cmdLoadSet, conn);
                cmd.Parameters.AddWithValue("@id", match);

                conn.Open();
                SqlDataReader reader = cmd.ExecuteReader();
                HelperMethods.FillCustomerList(coll, reader);
                reader.Close();
                conn.Close();

                return coll;
            }
        }
        #endregion

        #region METHOD: LoadAll
        // LoadAll
        public static CustomerCollection LoadAll()
        {
            return LoadAll(-1, 0);
        }
        public static CustomerCollection LoadAll(int totalRows, int firstRow)
        {
            return LoadAll(totalRows, firstRow, "");
        }
        public static CustomerCollection LoadAll(int totalRows, int firstRow, string sortExpression)
        {
            CustomerCollection coll = new CustomerCollection();

            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                SqlCommand cmd = new SqlCommand(CustomerCommands.cmdLoadAll, conn);
                if (!String.IsNullOrEmpty(sortExpression))
                    cmd.CommandText += " ORDER BY " + sortExpression;

                conn.Open();
                SqlDataReader reader = cmd.ExecuteReader();
                HelperMethods.FillCustomerList(coll, reader, totalRows, firstRow);
                reader.Close();
                conn.Close();
            }

            return coll;
        }
        #endregion


        #region METHOD: LoadByCountry
        // LoadByCountry
        public static CustomerCollection LoadByCountry(string country)
        {
            return LoadByCountry(country, -1, 0, "");
        }
        public static CustomerCollection LoadByCountry(string country, int totalRows, int firstRow)
        {
            return LoadByCountry(country, totalRows, firstRow, "");
        }
		public static CustomerCollection LoadByCountry(string country, int totalRows, int firstRow, string sortExpression)
		{
			CustomerCollection coll = new CustomerCollection();

			using (SqlConnection conn = new SqlConnection(ConnectionString))
			{
				SqlCommand cmd = new SqlCommand(CustomerCommands.cmdLoadByCountry, conn);
				cmd.Parameters.AddWithValue("@country", country);
				if (!String.IsNullOrEmpty(sortExpression))
					cmd.CommandText += " ORDER BY " + sortExpression;

				conn.Open();
				SqlDataReader reader = cmd.ExecuteReader();
				HelperMethods.FillCustomerList(coll, reader, totalRows, firstRow);
				reader.Close();
				conn.Close();
			}

			return coll;
		}
		#endregion


        #region METHOD: GetCustomerCountries
        // GetCustomerCountries
        public static StringCollection GetCustomerCountries()
        {
            StringCollection countries = new StringCollection();

            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                SqlCommand cmd = new SqlCommand(CustomerCommands.cmdCustCountries, conn);

                conn.Open();
                SqlDataReader reader = cmd.ExecuteReader();
                HelperMethods.FillCountryList(countries, reader);
                reader.Close();
                conn.Close();
            }

            return countries;
        }
        #endregion


        #region METHOD: Save
        // Save 
        public static void Save(Customer cust)
        {
            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                SqlCommand cmd = new SqlCommand(CustomerCommands.cmdSave, conn);
                cmd.Parameters.AddWithValue("@id", cust.ID);
                cmd.Parameters.AddWithValue("@companyname", cust.CompanyName);
                cmd.Parameters.AddWithValue("@city", cust.City);
                cmd.Parameters.AddWithValue("@address", cust.Street);
                cmd.Parameters.AddWithValue("@country", cust.Country);
//                cmd.Parameters.AddWithValue("@phone", cust.Phone);
//                cmd.Parameters.AddWithValue("@postalcode", cust.PostalCode);
//                cmd.Parameters.AddWithValue("@region", cust.Region);
//                cmd.Parameters.AddWithValue("@contactname", cust.ContactName);
//                cmd.Parameters.AddWithValue("@contacttitle", cust.ContactTitle);
//                cmd.Parameters.AddWithValue("@fax", cust.Fax);

                conn.Open();
                cmd.ExecuteNonQuery();
                conn.Close();
                return;
            }
        }

        #endregion


        #region METHOD: Add
        // Add 
        public static void Add(Customer cust)
        {
            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                SqlCommand cmd = new SqlCommand(CustomerCommands.cmdInsert, conn);
                cmd.Parameters.AddWithValue("@id", cust.ID);
                cmd.Parameters.AddWithValue("@companyname", cust.CompanyName);
                cmd.Parameters.AddWithValue("@city", cust.City);
                cmd.Parameters.AddWithValue("@address", cust.Street);
                cmd.Parameters.AddWithValue("@country", cust.Country);
                //                cmd.Parameters.AddWithValue("@phone", cust.Phone);
                //                cmd.Parameters.AddWithValue("@postalcode", cust.PostalCode);
                //                cmd.Parameters.AddWithValue("@region", cust.Region);
                //                cmd.Parameters.AddWithValue("@contactname", cust.ContactName);
                //                cmd.Parameters.AddWithValue("@contacttitle", cust.ContactTitle);
                //                cmd.Parameters.AddWithValue("@fax", cust.Fax);

                conn.Open();
                cmd.ExecuteNonQuery();
                conn.Close();
                return;
            }
        }

        #endregion


        #region METHOD: Delete
        // Delete 
        public static void Delete(string id)
        {
            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                SqlCommand cmd = new SqlCommand(CustomerCommands.cmdDelete, conn);
                cmd.Parameters.AddWithValue("@id", id);

                conn.Open();
                cmd.ExecuteNonQuery();
                conn.Close();
                return;
            }
        }
        public static void Delete(Customer cust)
        {
            Delete(cust.ID);
        }
        #endregion


    }


    // Helpers
    public static partial class HelperMethods
    {
        // GetCustomer
        public static Customer GetCustomer(SqlDataReader reader)
        {
            Customer cust = new Customer();
            if (reader.IsClosed) 
                reader.Read();

            cust.ID = reader["customerid"].ToString(); 
            cust.CompanyName = reader["companyname"].ToString();
            cust.ContactName = reader["contactname"].ToString();
            cust.ContactTitle = reader["contacttitle"].ToString();

            cust.City = reader["city"].ToString();
            cust.Street = reader["address"].ToString();
            cust.Country = reader["country"].ToString(); ;
            cust.Region = reader["region"].ToString();
            cust.PostalCode = reader["postalcode"].ToString();
            cust.Phone = reader["phone"].ToString(); ;
            cust.Fax = reader["fax"].ToString();

            return cust;
        }

        // FillCustomerList
        public static void FillCustomerList(CustomerCollection coll, SqlDataReader reader)
        {
            FillCustomerList(coll, reader, -1, 0);
        }
        public static void FillCustomerList(CustomerCollection coll, SqlDataReader reader, int totalRows, int firstRow)
        {
            int index = 0;
            bool readMore = true;

            while (reader.Read())
            {
                if (index >= firstRow && readMore)
                {
                    if (coll.Count >= totalRows && totalRows >0)
                        readMore = false;
                    else
                    {
                        Customer cust = HelperMethods.GetCustomer(reader);
                        coll.Add(cust);
                    }
                }
                index++;
            }
        }

    }
}
