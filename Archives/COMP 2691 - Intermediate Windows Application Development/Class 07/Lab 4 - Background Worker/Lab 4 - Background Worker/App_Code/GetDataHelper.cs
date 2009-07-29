using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace Threading
{
    public class GetDataHelper
    {
        //The method getDataSetCities that returns dataSet with 
        //one dataTable "DataTableCities". The dataTable consists of
        //two columns :  "SYMBOL_CITY" and "CITY".
        //The dataTable is filled with the help of 
        //the "for" loop; the number of the rows is input parameter.

        public DataSet getDataSetCities(int iRows)
        {
            DataTable dt = new DataTable("DataTableCities");
            DataColumn dc_SYMBOL_CITY;
            DataColumn dc_CITY;
            DataRow dRow;
            DataSet ds = new DataSet();
            string sHelp = "";
            string sHelp_0 = "City";

            ds.Clear();
            dc_SYMBOL_CITY = new DataColumn("SYMBOL_CITY", Type.GetType("System.String"));
            dt.Columns.Add(dc_SYMBOL_CITY);
            dc_CITY = new DataColumn("CITY", Type.GetType("System.String"));
            dt.Columns.Add(dc_CITY);

            for (int i = 0; i < iRows; i++)
            {
                dRow = dt.NewRow();
                if (i < 10)
                {
                    dRow["SYMBOL_CITY"] = "00000" + i.ToString();
                }
                else
                {
                    if (i < 100 && i >= 10)
                    {
                        dRow["SYMBOL_CITY"] = "0000" + i.ToString();
                    }
                    else
                    {
                        if (i < 1000 && i >= 100)
                        {
                            dRow["SYMBOL_CITY"] = "000" + i.ToString();
                        }
                        else
                        {
                            dRow["SYMBOL_CITY"] = i.ToString();
                        }
                    }
                }

                sHelp = sHelp_0;
                sHelp = sHelp + "_" + i.ToString();

                if (i % 2 == 0)
                {
                    sHelp = sHelp + "g";
                }
                else if (i % 3 == 0)
                {
                    sHelp = sHelp + "gff";
                }
                else if (i % 5 == 0)
                {
                    sHelp = "abc" + sHelp;
                }
                else if (i % 7 == 0)
                {
                    sHelp = "awc" + sHelp;
                }
                else
                {
                    sHelp = "awt" + sHelp + "g";
                }
                if (i == 0)
                {
                    sHelp = "Sun City";
                }
                dRow["CITY"] = sHelp;
                dt.Rows.Add(dRow);
            }

            ds.Tables.Add(dt);
            return ds;
        }
    }
}