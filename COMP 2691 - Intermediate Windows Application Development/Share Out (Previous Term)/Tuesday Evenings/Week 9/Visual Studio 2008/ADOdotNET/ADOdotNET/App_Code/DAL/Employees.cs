using System;
using System.Data;
using System.Configuration;
using System.Data.SqlClient;
using System.Collections.Generic;
using System.Collections.Specialized;
using ADOdotNET.DAL;



// EMPLOYEE 
// A class to hold employee data and a static class for the behavior according to the 
// Table Data Gateway pattern

namespace ADOdotNET.DAL
{
    // EMPLOYEE 
    // Holds information about the employee
    public class Employee
    {
        private string _firstname, _lastname, _title, _titleofcourtesy, _notes, _extension;
		private string _street, _postalcode, _city, _country, _phone, _region, _fax;
		private int _id, _reportsTo;
		private DateTime _birthdate, _hiredate;

        public Employee()
        {
        }

        #region PROPERTIES

        // ID
        public int ID
        {
            get { return _id; }
            set { _id = value; }
        }

        // FirstName
        public string FirstName
        {
            get { return _firstname; }
            set { _firstname = value; }
        }

        // LastName
        public string LastName
        {
            get { return _lastname; }
            set { _lastname = value; }
        }

        // Title
        public string Title
        {
            get { return _title; }
            set { _title = value; }
        }

        // TitleOfCourtesy
        public string TitleOfCourtesy
        {
            get { return _titleofcourtesy; }
            set { _titleofcourtesy = value; }
        }

        // BirthDate
        public DateTime BirthDate
        {
            get { return _birthdate; }
            set { _birthdate = value; }
        }
        
        // HireDate
        public DateTime HireDate
        {
            get { return _hiredate; }
            set { _hiredate = value; }
        }

        // ReportsTo
        public int ReportsTo
        {
            get { return _reportsTo; }
            set { _reportsTo = value; }
        }

        // Extension
        public string Extension
        {
            get { return _extension; }
            set { _extension = value; }
        }

        // Notes
        public string Notes
        {
            get { return _notes; }
            set { _notes = value; }
        }

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
            return String.Format("{0} {1}", _firstname, _lastname);
        }
        #endregion
    }


    // NULLEMPLOYEE
    public class NullEmployee : Employee
    {
        public NullEmployee()
        {
            ID = -1;
        }
    }


    // EMPLOYEECOLLECTION
    // Collection of employee objects
    public class EmployeeCollection : List<Employee>
    {
    }


    // EMPLOYEES--employee gateway
    // Behavior of the employee
    public class Employees
    {
        public static string ConnectionString
        {
            get { return ConfigurationManager.ConnectionStrings["J2EENWind"].ConnectionString; }
        }

        #region METHOD: Load
        // Load
        public static Employee Load(int id)
        {
            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                SqlCommand cmd = new SqlCommand(EmployeeCommands.cmdLoad, conn);
                cmd.Parameters.AddWithValue("@id", id);

                conn.Open();
                SqlDataReader reader = cmd.ExecuteReader();
				reader.Read();
				Employee emp = HelperMethods.GetEmployee(reader);
                reader.Close();
                conn.Close();

                return emp;
            }
        }
        #endregion


        #region METHOD: LoadAll
        // LoadAll
        public static EmployeeCollection LoadAll()
        {
            EmployeeCollection coll = new EmployeeCollection();

            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                SqlCommand cmd = new SqlCommand(EmployeeCommands.cmdLoadAll, conn);

                conn.Open();
                SqlDataReader reader = cmd.ExecuteReader();
                HelperMethods.FillEmployeeList(coll, reader);
                reader.Close();
                conn.Close();
            }

            return coll;
        }
        #endregion


        #region METHOD: LoadByCountry
        // LoadAll
        public static EmployeeCollection LoadByCountry(string country)
        {
            EmployeeCollection coll = new EmployeeCollection();

            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                SqlCommand cmd = new SqlCommand(EmployeeCommands.cmdLoadByCountry, conn);
                cmd.Parameters.AddWithValue("@country", country);

                conn.Open();
                SqlDataReader reader = cmd.ExecuteReader();
                HelperMethods.FillEmployeeList(coll, reader);
                reader.Close();
                conn.Close();
            }

            return coll;
        }
        #endregion


        #region METHOD: GetEmployeeCountries
        // GetEmployeeCountries
        public static StringCollection GetEmployeeCountries()
        {
            StringCollection countries = new StringCollection();

            using (SqlConnection conn = new SqlConnection(ConnectionString))
            {
                SqlCommand cmd = new SqlCommand(EmployeeCommands.cmdEmpCountries, conn);

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
		public static void Save(Employee emp)
		{
			using (SqlConnection conn = new SqlConnection(ConnectionString))
			{
				SqlCommand cmd = new SqlCommand(EmployeeCommands.cmdSave, conn);
				cmd.Parameters.AddWithValue("@id", emp.ID);
				cmd.Parameters.AddWithValue("@lastname", emp.LastName);
				cmd.Parameters.AddWithValue("@firstname", emp.FirstName);
				cmd.Parameters.AddWithValue("@birthdate", emp.BirthDate);
				cmd.Parameters.AddWithValue("@title", emp.Title);
                cmd.Parameters.AddWithValue("@country", emp.Country);

/*
 *              In production code, you typically have stored procedures instead of SQL 
 *              commands. In a stored procedure, if there are situations in which only a
 *              subset of parameters can be passed, you first read the row, then assign
 *              default values to missing parameters and proceed with the update
 */

/*
				cmd.Parameters.AddWithValue("@titleofcourtesy", emp.TitleOfCourtesy);
				cmd.Parameters.AddWithValue("@reportsto", emp.ReportsTo);
				cmd.Parameters.AddWithValue("@notes", emp.Notes);
				cmd.Parameters.AddWithValue("@hiredate", emp.HireDate);
				cmd.Parameters.AddWithValue("@extension", emp.Extension);
				cmd.Parameters.AddWithValue("@city", emp.City);
				cmd.Parameters.AddWithValue("@phone", emp.Phone);
				cmd.Parameters.AddWithValue("@postalcode", emp.PostalCode);
				cmd.Parameters.AddWithValue("@region", emp.Region);
				cmd.Parameters.AddWithValue("@address", emp.Street);
*/
				conn.Open();
				cmd.ExecuteNonQuery();
				conn.Close();
				return;
			}
		}

		#endregion

		// Delete


    }


    // Helpers
    public static partial class HelperMethods
    {
        // GetEmployee
        public static Employee GetEmployee(SqlDataReader reader)
        {
            int index;
			if (!reader.HasRows)
				return null;
			
			Employee emp = new Employee();
			emp.ID = (int) reader["employeeid"];
            emp.LastName = reader["lastname"].ToString();
            emp.FirstName = reader["firstname"].ToString();

            index = reader.GetOrdinal("birthdate");
            if (reader.IsDBNull(index))
                emp.BirthDate = DateTime.MinValue;
            else
                emp.BirthDate = (DateTime)reader["birthdate"];

            index = reader.GetOrdinal("hiredate");
            if (reader.IsDBNull(index))
                emp.HireDate = DateTime.MinValue;
            else
                emp.HireDate = (DateTime)reader["hiredate"];

            emp.Extension = reader["extension"].ToString();
            emp.Title = reader["title"].ToString();
            emp.TitleOfCourtesy = reader["titleofcourtesy"].ToString();
            emp.Notes = reader["notes"].ToString();
            
            index = reader.GetOrdinal("reportsto");
            if (reader.IsDBNull(index))
                emp.ReportsTo = -1;
            else
                emp.ReportsTo = (int) reader["reportsto"];
            emp.Street = reader["address"].ToString();
            emp.City = reader["city"].ToString();
            emp.Country = reader["country"].ToString();
            emp.Region = reader["region"].ToString();
            emp.PostalCode = reader["postalcode"].ToString();
            emp.Phone = reader["homephone"].ToString();
            emp.Fax = "";

            return emp;
        }

        // FillEmployeeList
        public static void FillEmployeeList(EmployeeCollection coll, SqlDataReader reader)
        {
            while (reader.Read())
            {
                Employee emp = HelperMethods.GetEmployee(reader);
                coll.Add(emp);
            }
        }

        // FillCountryList
        public static void FillCountryList(StringCollection coll, SqlDataReader reader)
        {
            while (reader.Read())
            {
                if (reader["country"] != null)
                {
                    string country = reader["country"].ToString();
                    if (!String.IsNullOrEmpty(country))
                        coll.Add(country);
                }
            }
        }

    }
}
