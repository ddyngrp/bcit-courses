using System;

namespace AssemblyDocumenter
{
    /// <summary>
    /// Summary description for Class1.
    /// </summary>
    public class Files
    {
        public System.Collections.ArrayList AsmFiles { get { return asmFiles; } }
        private System.Collections.ArrayList asmFiles = new System.Collections.ArrayList();
        private System.Collections.ArrayList notAsmFiles = new System.Collections.ArrayList();
        private AssemblyDocumenter.Logger logger;
        System.Boolean log = false;
        public Files(string asmlocation, AssemblyDocumenter.Logger Logger, System.Boolean Log)
        {
            logger = Logger;
            log = Log;
            if (System.IO.File.Exists(asmlocation))
            {
                //just document this one single assembly
                asmFiles.Add(System.Reflection.Assembly.LoadFrom(asmlocation));
                if (log) logger.Log("Loaded:" + asmlocation + "\n");
            }
            else if (System.IO.Directory.Exists(asmlocation))
            {
                //document entire folder
                LoadFiles(asmlocation);
                if (log) logger.Log("Done Loading " + Convert.ToString(asmFiles.Count) + " Files.\n");
            }
            else
            {
                //do nothing
            }
        }
        public void LoadFiles(string location)
        {
            //first get a list of all the directories
            //now load all the files in
            foreach (string file in System.IO.Directory.GetFiles(location, "*.dll"))
            {
                try
                {
                    asmFiles.Add(System.Reflection.Assembly.LoadFrom(file));
                    if (log) logger.Log("Loaded:" + file + "\n");
                }
                catch (Exception e)
                {
                    notAsmFiles.Add(file);
                    if (log) logger.Log("Could not load:" + file + e.Message + "\n");
                }
            }
            foreach (string dir in System.IO.Directory.GetDirectories(location))
            {
                LoadFiles(dir);
            }
        }
    }

    public class Documenter
    {
        AssemblyDocumenter.Files files;
        AssemblyDocumenter.Logger logger;
        System.Boolean log = false;
        public AssemblyDocumenter.Logger Logger { get { return logger; } set { logger = value; } }
        public System.Boolean Log { get { return log; } set { log = value; } }
        public Documenter(string AssemblyLocation, string SaveLocation, AssemblyDocumenter.Logger Logger)
        {
            logger = Logger;
            log = true;
            BuildDocs(AssemblyLocation, SaveLocation);
        }

        public Documenter(string AssemblyLocation, string SaveLocation)
        {
            BuildDocs(AssemblyLocation, SaveLocation);
        }
        public void BuildDocs(string AssemblyLocation, string SaveLocation)
        {
            //load up the files
            files = new AssemblyDocumenter.Files(AssemblyLocation, logger, log);
            //and now process the asm files
            System.Text.StringBuilder xmlDocIndex = new System.Text.StringBuilder("<html><head><title>Assembly Reflection Documentation</title></head><body>Assembly Reflection Documentation for: " + AssemblyLocation + "<br /><ol>");
            System.Text.StringBuilder xmlDoc = new System.Text.StringBuilder("<?xml version=\"1.0\"?>");
            long filecount = files.AsmFiles.Count;
            if (files.AsmFiles.Count > 0)
            {
                xmlDocIndex.Append("<assemblies>");
                foreach (System.Reflection.Assembly assembly in files.AsmFiles)
                {
                    if (log) logger.Log(Convert.ToString(filecount) + ") Processing:" + assembly.CodeBase + "\n");
                    xmlDoc.Append("<assembly codebase=\"" + assembly.CodeBase + "\" fullname=\"" + assembly.FullName + "\" gac=\"" + assembly.GlobalAssemblyCache + "\" location=\"" + assembly.Location + "\" displayname=\"" + assembly.ToString() + "\">");
                    try
                    {
                        foreach (System.Type type in assembly.GetTypes())
                        {
                            if (log) logger.Log(Convert.ToString(filecount) + ") Processing:" + assembly.CodeBase + ":" + type.FullName + "\n");
                            xmlDoc.Append("<type name=\"" + type.FullName + "\" guid=\"" + type.GUID + "\">");
                            xmlDoc.Append("<constructors>");
                            if (log) logger.Log(Convert.ToString(filecount) + ") Processing:" + assembly.CodeBase + ":" + type.FullName + ":Constructor Information\n");
                            foreach (System.Reflection.ConstructorInfo cinfo in type.GetConstructors())
                            {
                                xmlDoc.Append("<constructor name=\"" + cinfo.Name + "\">");
                                xmlDoc.Append(AddParameters(cinfo.GetParameters()));
                                xmlDoc.Append("</constructor>");
                            }
                            xmlDoc.Append("</constructors>");

                            if (log) logger.Log(Convert.ToString(filecount) + ") Processing:" + assembly.CodeBase + ":" + type.FullName + ":Event Information\n");
                            xmlDoc.Append("<events>");
                            foreach (System.Reflection.EventInfo einfo in type.GetEvents())
                            {
                                xmlDoc.Append("<event handler=\"" + einfo.EventHandlerType.FullName + "\">");
                                xmlDoc.Append("<IsMulticast>" + einfo.IsMulticast + "</IsMulticast>");
                                xmlDoc.Append("<IsSpecialName>" + einfo.IsSpecialName + "</IsSpecialName>");
                                xmlDoc.Append("<RaiseMethod>");
                                xmlDoc.Append(AddMethod(einfo.GetRaiseMethod()));
                                xmlDoc.Append("</RaiseMethod>");
                                xmlDoc.Append("<RemoveMethod>");
                                xmlDoc.Append(AddMethod(einfo.GetRemoveMethod()));
                                xmlDoc.Append("</RemoveMethod>");
                                xmlDoc.Append("</event>");
                            }
                            xmlDoc.Append("</events>");

                            if (log) logger.Log(Convert.ToString(filecount) + ") Processing:" + assembly.CodeBase + ":" + type.FullName + ":Method Information\n");
                            xmlDoc.Append(AddMethods(type.GetMethods()));
                            if (log) logger.Log(Convert.ToString(filecount) + ") Processing:" + assembly.CodeBase + ":" + type.FullName + ":Member Information\n");
                            xmlDoc.Append(AddMembers(type.GetMembers()));

                            if (log) logger.Log(Convert.ToString(filecount) + ") Processing:" + assembly.CodeBase + ":" + type.FullName + ":Property Information\n");
                            xmlDoc.Append(AddProperties(type.GetProperties()));

                            if (log) logger.Log(Convert.ToString(filecount) + ") Processing:" + assembly.CodeBase + ":" + type.FullName + ":Interface Information\n");
                            xmlDoc.Append("<interfaces>");
                            foreach (System.Type IFace in type.GetInterfaces())
                                xmlDoc.Append("<interface name=\"" + IFace.FullName + "\"/>");
                            xmlDoc.Append("</interfaces>");

                            if (log) logger.Log(Convert.ToString(filecount) + ") Processing:" + assembly.CodeBase + ":" + type.FullName + ":Other Information\n");
                            xmlDoc.Append("<other>");
                            xmlDoc.Append("<IsAbstract>" + type.IsAbstract + "</IsAbstract>");
                            xmlDoc.Append("<IsAnsiClass>" + type.IsAnsiClass + "</IsAnsiClass>");
                            xmlDoc.Append("<IsArray>" + type.IsArray + "</IsArray>");
                            xmlDoc.Append("<IsAutoClass>" + type.IsAutoClass + "</IsAutoClass>");
                            xmlDoc.Append("<IsAutoLayout>" + type.IsAutoLayout + "</IsAutoLayout>");
                            xmlDoc.Append("<IsByRef>" + type.IsByRef + "</IsByRef>");
                            xmlDoc.Append("<IsClass>" + type.IsClass + "</IsClass>");
                            xmlDoc.Append("<IsCOMObject>" + type.IsCOMObject + "</IsCOMObject>");
                            xmlDoc.Append("<IsContextful>" + type.IsContextful + "</IsContextful>");
                            xmlDoc.Append("<IsEnum>" + type.IsEnum + "</IsEnum>");
                            xmlDoc.Append("<IsExplicitLayout>" + type.IsExplicitLayout + "</IsExplicitLayout>");
                            xmlDoc.Append("<IsImport>" + type.IsImport + "</IsImport>");
                            xmlDoc.Append("<IsInterface>" + type.IsInterface + "</IsInterface>");
                            xmlDoc.Append("<IsLayoutSequential>" + type.IsLayoutSequential + "</IsLayoutSequential>");
                            xmlDoc.Append("<IsMarshalByRef>" + type.IsMarshalByRef + "</IsMarshalByRef>");
                            xmlDoc.Append("<IsNestedAssembly>" + type.IsNestedAssembly + "</IsNestedAssembly>");
                            xmlDoc.Append("<IsNestedFamANDAssem>" + type.IsNestedFamANDAssem + "</IsNestedFamANDAssem>");
                            xmlDoc.Append("<IsNestedFamily>" + type.IsNestedFamily + "</IsNestedFamily>");
                            xmlDoc.Append("<IsNestedFamORAssem>" + type.IsNestedFamORAssem + "</IsNestedFamORAssem>");
                            xmlDoc.Append("<IsNestedPrivate>" + type.IsNestedPrivate + "</IsNestedPrivate>");
                            xmlDoc.Append("<IsNestedPublic>" + type.IsNestedPublic + "</IsNestedPublic>");
                            xmlDoc.Append("<IsNotPublic>" + type.IsNotPublic + "</IsNotPublic>");
                            xmlDoc.Append("<IsPointer>" + type.IsPointer + "</IsPointer>");
                            xmlDoc.Append("<IsPrimitive>" + type.IsPrimitive + "</IsPrimitive>");
                            xmlDoc.Append("<IsPublic>" + type.IsPublic + "</IsPublic>");
                            xmlDoc.Append("<IsSealed>" + type.IsSealed + "</IsSealed>");
                            xmlDoc.Append("<IsSerializable>" + type.IsSerializable + "</IsSerializable>");
                            xmlDoc.Append("<IsSpecialName>" + type.IsSpecialName + "</IsSpecialName>");
                            xmlDoc.Append("<IsUnicodeClass>" + type.IsUnicodeClass + "</IsUnicodeClass>");
                            xmlDoc.Append("<IsValueType>" + type.IsValueType + "</IsValueType>");
                            if (type.IsArray) xmlDoc.Append("<ArrayRank>" + type.GetArrayRank() + "</ArrayRank>");
                            xmlDoc.Append("</other>");
                            xmlDoc.Append("</type>");
                            if (log) logger.Log(Convert.ToString(filecount) + ") Finished Processing:" + assembly.CodeBase + ":" + type.FullName + "\n");
                        }
                    }
                    catch (Exception e)
                    {
                        xmlDoc.Append("<error>" + assembly.FullName + "</error>");
                    }
                    xmlDoc.Append("</assembly>");
                    string newfile = (assembly.FullName).Substring(0, assembly.FullName.IndexOf(",")) + Convert.ToString(filecount);
                    SaveDoc(xmlDoc, SaveLocation + newfile + ".xml");
                    xmlDocIndex.Append("<li><a href=\"" + newfile + ".xml\">" + newfile + "</a></li>");
                    xmlDoc = new System.Text.StringBuilder("<?xml version=\"1.0\"?>");
                    filecount--;
                }
                xmlDocIndex.Append("</ol></body></html>");
                SaveDoc(xmlDocIndex, SaveLocation + "index.html");
            }
        }

        public void SaveDoc(System.Text.StringBuilder xmlDoc, string SaveLocation)
        {
            byte[] doc = System.Text.ASCIIEncoding.ASCII.GetBytes(xmlDoc.ToString());
            try
            {
                if (log) logger.Log("Writing:" + SaveLocation + "\n");
                System.IO.FileStream outfile = System.IO.File.OpenWrite(SaveLocation);
                outfile.Write(doc, 0, doc.Length);
                outfile.Close();
            }
            catch (Exception e)
            {
                throw (new Exception(SaveLocation + " could not be written to."));
            }

        }
        public string AddParameters(System.Reflection.ParameterInfo[] parameters)
        {
            System.Text.StringBuilder xmlDoc = new System.Text.StringBuilder();
            xmlDoc.Append("<parameters>");
            foreach (System.Reflection.ParameterInfo pinfo in parameters)
                xmlDoc.Append("<parameter name=\"" + pinfo.Name + "\" />"); // type=\""+(pinfo.ParameterType).FullName+"\" />");
            xmlDoc.Append("</parameters>");
            return xmlDoc.ToString();
        }
        public string AddMethods(System.Reflection.MethodInfo[] methods)
        {
            System.Text.StringBuilder xmlDoc = new System.Text.StringBuilder();
            xmlDoc.Append("<methods>");
            foreach (System.Reflection.MethodInfo method in methods)
                xmlDoc.Append(AddMethod(method));
            xmlDoc.Append("</methods>");
            return xmlDoc.ToString();
        }
        public string AddMethod(System.Reflection.MethodInfo methinfo)
        {
            System.Text.StringBuilder xmlDoc = new System.Text.StringBuilder();
            try
            {
                xmlDoc.Append("<MethodInfo name=\"" + methinfo.Name + "\">");
                xmlDoc.Append(AddParameters(methinfo.GetParameters()));
                xmlDoc.Append("<ReturnType>" + methinfo.ReturnType.FullName + "</ReturnType>");
                xmlDoc.Append("<Other>");
                xmlDoc.Append("<Attributes>" + methinfo.Attributes.ToString() + "</Attributes>");
                xmlDoc.Append("<IsAbstract>" + methinfo.IsAbstract + "</IsAbstract>");
                xmlDoc.Append("<IsAssembly>" + methinfo.IsAssembly + "</IsAssembly>");
                xmlDoc.Append("<IsConstructor>" + methinfo.IsConstructor + "</IsConstructor>");
                xmlDoc.Append("<IsFamily>" + methinfo.IsFamily + "</IsFamily>");
                xmlDoc.Append("<IsFamilyAndAssembly>" + methinfo.IsFamilyAndAssembly + "</IsFamilyAndAssembly>");
                xmlDoc.Append("<IsFamilyOrAssembly>" + methinfo.IsFamilyOrAssembly + "</IsFamilyOrAssembly>");
                xmlDoc.Append("<IsFinal>" + methinfo.IsFinal + "</IsFinal>");
                xmlDoc.Append("<IsHideBySig>" + methinfo.IsHideBySig + "</IsHideBySig>");
                xmlDoc.Append("<IsPrivate>" + methinfo.IsPrivate + "</IsPrivate>");
                xmlDoc.Append("<IsPublic>" + methinfo.IsPublic + "</IsPublic>");
                xmlDoc.Append("<IsSpecialName>" + methinfo.IsSpecialName + "</IsSpecialName>");
                xmlDoc.Append("<IsStatic>" + methinfo.IsStatic + "</IsStatic>");
                xmlDoc.Append("<IsVirtual>" + methinfo.IsVirtual + "</IsVirtual>");
                xmlDoc.Append("</Other>");
                xmlDoc.Append("</MethodInfo>");
            }
            catch (Exception e)
            {
                xmlDoc.Append("<error>Could not add method</error>");
            }
            return xmlDoc.ToString();
        }
        public string AddMembers(System.Reflection.MemberInfo[] meminfo)
        {
            System.Text.StringBuilder xmlDoc = new System.Text.StringBuilder();
            xmlDoc.Append("<members>");
            foreach (System.Reflection.MemberInfo member in meminfo)
            {
                xmlDoc.Append("<member name=\"" + member.Name + "\">");
                xmlDoc.Append("<DeclaringType>" + member.DeclaringType.FullName + "</DeclaringType>");
                xmlDoc.Append("<MemberType>" + member.MemberType.ToString() + "</MemberType>");
                xmlDoc.Append("</member>");
            }
            xmlDoc.Append("</members>");
            return xmlDoc.ToString();
        }
        public string AddProperties(System.Reflection.PropertyInfo[] properties)
        {
            System.Text.StringBuilder xmlDoc = new System.Text.StringBuilder();
            xmlDoc.Append("<properties>");
            foreach (System.Reflection.PropertyInfo property in properties)
                xmlDoc.Append(AddProperty(property));
            xmlDoc.Append("</properties>");
            return xmlDoc.ToString();
        }
        public string AddProperty(System.Reflection.PropertyInfo property)
        {
            System.Text.StringBuilder xmlDoc = new System.Text.StringBuilder();
            //foreach(System.Reflection.PropertyInfo property in properties) {
            xmlDoc.Append("<property name=\"" + property.Name + "\">");
            xmlDoc.Append("<CanRead>" + property.CanRead + "</CanRead>");
            xmlDoc.Append("<CanWrite>" + property.CanWrite + "</CanWrite>");
            xmlDoc.Append("<IsSpecialName>" + property.IsSpecialName + "</IsSpecialName>");
            xmlDoc.Append("<Type>" + property.PropertyType.FullName + "</Type>");
            xmlDoc.Append("</property>");
            //}

            return xmlDoc.ToString();
        }
    }

    public abstract class Logger
    {
        public abstract void Log(string content);
    }

    public class ConsoleLog : Logger
    {
        public override void Log(string content)
        {
            Console.WriteLine(content);
        }
    }

    public class FileLog : Logger
    {
        private string loglocation;
        System.IO.FileStream outfile;
        public string LogLocation { get { return loglocation; } set { loglocation = value; } }
        public FileLog(string loglocation)
        {
            outfile = System.IO.File.OpenWrite(loglocation);
        }
        public override void Log(string content)
        {
            byte[] bContent = System.Text.ASCIIEncoding.ASCII.GetBytes(content);
            outfile.Write(bContent, 0, bContent.Length);
        }
        ~FileLog()
        {
            outfile.Close();
        }
    }

}
