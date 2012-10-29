using System;
using AssemblyDocumenter;

namespace DosApp 
{
    /// <summary>
    /// Handles the Main() entry for the application
    /// </summary>
    class ASMDoc
    {
        /// <summary>
        /// Parses the command parameters and handles them appropriately
        /// </summary>
        static void Main(string[] args)
        {
            System.DateTime start = System.DateTime.Now;
            string asmpath = System.Reflection.Assembly.GetExecutingAssembly().Location;
            string outputpath = "";
            string loggingtype = "Console";
            string logpath = "";
            System.Boolean cont = true;
            //string[] args1 = {"/s:c:\\","/o:D:\\dev\\Santra\\OppCenter\\docs\\","/l:file","/p:D:\\dev\\Santra\\OppCenter\\docs\\log.txt"};
            foreach (string arg in args)
            {
                if (arg.Length > 3)
                {
                    if (arg.Substring(0, 3) == "/s:")
                        asmpath = arg.Substring(3);
                    if (arg.Substring(0, 3) == "/o:")
                        outputpath = arg.Substring(3);
                    if (arg.Substring(0, 3) == "/l:")
                        loggingtype = arg.Substring(3);
                    if (arg.Substring(0, 3) == "/p:")
                        logpath = arg.Substring(3);
                }
                else if (arg.Length == 2)
                {
                    if (arg.Substring(0, 2) == "/?")
                        if (cont) ShowHelp();
                    cont = false;
                }
                else
                {
                    if (cont) ShowHelp();
                    cont = false;
                }
            }
            if (outputpath == "")
            {
                if (cont) ShowHelp();
                cont = false;
            }
            else
            {
                if (cont)
                {
                    AssemblyDocumenter.Documenter doc;
                    if (loggingtype.ToUpper() == "FILE" && logpath != "")
                        doc = new AssemblyDocumenter.Documenter(asmpath, outputpath, new AssemblyDocumenter.FileLog(logpath));
                    else
                        doc = new AssemblyDocumenter.Documenter(asmpath, outputpath, new AssemblyDocumenter.ConsoleLog());
                }
            }
            System.DateTime ptime = new System.DateTime(System.DateTime.Now.Ticks - start.Ticks);
            Console.WriteLine("Total Processing Time: " + Convert.ToString(ptime.Hour) + "h, " + Convert.ToString(ptime.Minute) + "m, " + Convert.ToString(ptime.Second) + "s, " + Convert.ToString(ptime.Millisecond) + "ms");
        }
        public static void ShowHelp()
        {
            System.Text.StringBuilder help = new System.Text.StringBuilder();
            help.Append("Syntax For Assembly Documentor v0.1\n");
            help.Append("/s:{PATH/FILE}\t\tSpecify the location of the source assembly(s)\n");
            help.Append("/o:PATH\t\tSpecify the location of the report\n");
            help.Append("/l:[Console][File]\t\tSpecify the type of logging.\n");
            help.Append("/p:FILE\t\tWhen using file logging, specify the path to the log file.\n");
            help.Append("/?\t\tHelp\n");
            help.Append("\n");
            Console.WriteLine(help.ToString());
        }
    }
}
