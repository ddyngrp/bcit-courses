using System;
using System.Data;
using System.Configuration;



namespace ADOdotNET.DAL
{
    public class EmployeeCommands
    {
        public static string cmdGetNames = "SELECT employeeid, lastname FROM employees";
        public static string cmdLoadAll = "SELECT * FROM employees";
        public static string cmdEmpCountries = "SELECT DISTINCT country FROM employees";
        public static string cmdLoadByCountry = "SELECT * FROM employees WHERE country=@country";
        public static string cmdLoad = "SELECT * FROM employees WHERE employeeid=@id";
        public static string cmdSave = "UPDATE employees SET " + 
                                       " lastname=@lastname, firstname=@firstname, " + 
			                           " birthdate=@birthdate, country=@country, title=@title " +
                                       "WHERE employeeid=@id";
        public static string cmdDelete = "DELETE FROM employees WHERE employeeid=@id";
    }
    

    public class CustomerCommands
    {
        public static string cmdGetNames = "SELECT customerid, companyname FROM customers";
        public static string cmdLoadAll = "SELECT * FROM customers";
        public static string cmdLoadSet = "SELECT * FROM customers WHERE customerid LIKE @id + '%'";
        public static string cmdCustCountries = "SELECT DISTINCT country FROM customers";
        public static string cmdLoadByCountry = "SELECT * FROM customers WHERE country=@country OR @country='[All]'";
        public static string cmdLoad = "SELECT * FROM customers WHERE customerid=@id";
        public static string cmdSave = "UPDATE customers SET " +
                                       " companyname=@companyname, country=@country, city=@city, address=@address " +
                                       "WHERE customerid=@id";
        public static string cmdInsert = "INSERT INTO customers (customerid,companyname,address,city,country) " +
                                         "VALUES (@id,@companyname,@address,@city,@country)";
        public static string cmdDelete = "DELETE FROM customers WHERE customerid=@id";
    }

}
