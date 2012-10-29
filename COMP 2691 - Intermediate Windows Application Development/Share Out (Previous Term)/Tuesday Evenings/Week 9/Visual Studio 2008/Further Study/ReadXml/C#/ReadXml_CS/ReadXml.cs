using System;
using System.Xml;
using System.Data;
using System.IO;

class ReadXmlApp
{
  public static void Main(String[] args)
  {
     try {
		String fileName = args[0];
		StreamReader sr = new StreamReader(fileName);
		DataSet ds = new DataSet(fileName);
		ds.ReadXml(sr);
		sr.Close();	
		Console.WriteLine("{0} table(s) found.\n------------", ds.Tables.Count);
		 foreach(DataTable dt in ds.Tables)
		 {
			 Console.WriteLine(dt.TableName);
			 foreach(DataColumn col in dt.Columns)
				 Console.WriteLine("\t{0} - ({1})", col.ColumnName, col.DataType.ToString());
			 Console.WriteLine("------------");
		 }
	 }
     catch (Exception e) {	        
		 Console.WriteLine("\n*** Usage: readxml.exe <xmlfile> \n");
		 Console.WriteLine("Error:\t{0}\n\n", e.Message);
	 }

     return;
  }
}
