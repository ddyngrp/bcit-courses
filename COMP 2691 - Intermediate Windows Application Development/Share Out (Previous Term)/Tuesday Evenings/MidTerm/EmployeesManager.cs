using System;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;


public class EmployeesManager
{
	// *****************************************************************************
	// Ctor(s)
	public EmployeesManager()
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
            EmployeeCommandList.cmdListOfNames, 
			ConfigurationManager.ConnectionStrings["J2EENorthwind"].ConnectionString);

		DataTable table = new DataTable();
		adapter.Fill(table);

		return table;
	}


    // Returns the list of all employees
    public DataTable GetListofEmployees()
    {
        // Get the lastnames of all employees  //LocalNWind
        SqlDataAdapter adapter;
        adapter = new SqlDataAdapter(
            EmployeeCommandList.cmdListOfEmployees,
            ConfigurationManager.ConnectionStrings["J2EENorthwind"].ConnectionString);

        DataTable table = new DataTable();
        adapter.Fill(table);

        return table;
    }
	// *****************************************************************************
	// Returns the list of all employees
	public EmployeeInfo GetEmployeeDetails(int empID)
	{
		// Get details about the specified employee
		SqlDataAdapter adapter = new SqlDataAdapter(
            String.Format(EmployeeCommandList.cmdEmployeeDetails, empID),
			ConfigurationManager.ConnectionStrings["J2EENorthwind"].ConnectionString);
		DataTable table = new DataTable();
		adapter.Fill(table);

		// Execute the command and populate the return buffer
		DataRow row = table.Rows[0];
		EmployeeInfo info = new EmployeeInfo();
		info.ID = empID;
		info.FirstName = row["firstname"].ToString();
		info.LastName = row["lastname"].ToString();
		info.Title = row["title"].ToString();
		info.Country = row["country"].ToString();
		info.Notes = row["notes"].ToString();

		return info;
	}
}


public class EmployeeCommandList
{
	public static string cmdListOfNames = "SELECT employeeid, lastname FROM employees";
   // public static string cmdListOfEmployees = "SELECT employeeid, hiredate, lastname FROM employees";
    public static string cmdListOfEmployees = "SELECT employeeid, hiredate, firstname + ' ' + lastname as fullname, Photo FROM employees";

	public static string cmdEmployeeDetails = "SELECT firstname, lastname, title, country, notes FROM employees WHERE employeeid={0}";
}


public class EmployeeInfo
{
    public int ID;
    public string FirstName;
    public string LastName;
    public string Title;
    public string Country;
    public string Notes;
}
