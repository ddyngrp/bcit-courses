using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Xml.Serialization;

namespace Serialize_People
{
    // A simple program that accepts a name, year, month date,
    // creates a Person object from that information, 
    // and then displays that person's age on the console.
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                // If they provide no arguments, display the last person
                Person p = Deserialize();
                Console.WriteLine(p.ToString());
            }
            else
            {
                try
                {
                    if (args.Length != 4)
                    {
                        throw new ArgumentException("You must provide four arguments.");
                    }

                    DateTime dob = new DateTime(Int32.Parse(args[1]), Int32.Parse(args[2]), Int32.Parse(args[3]));
                    Person p = new Person(args[0], dob);
                    Console.WriteLine(p.ToString());

                    Serialize(p);
                }
                catch (Exception ex)
                {
                    DisplayUsageInformation(ex.Message);
                }
            }
        }

        private static void DisplayUsageInformation(string message)
        {
            Console.WriteLine("\nERROR: Invalid parameters. " + message);
            Console.WriteLine("\nSerialize_People \"Name\" Year Month Date");
            Console.WriteLine("\nFor example:\nSerialize_People \"Tony\" 1922 11 22");
            Console.WriteLine("\nOr, run the command with no arguments to display that previous person.");
        }

        private static void Serialize(Person sp)
        {
            // Create file to save the data to
            FileStream fs = new FileStream("Person.XML", FileMode.Create);

            // Create an XmlSerializer object to perform the serialization
            XmlSerializer xs = new XmlSerializer(typeof(Person));

            // Use the XmlSerializer object to serialize the data to the file
            xs.Serialize(fs, sp);

            // Close the file
            fs.Close();
        }

        private static Person Deserialize()
        {
            Person dsp = new Person();

            // Create file to save the data to
            FileStream fs = new FileStream("Person.XML", FileMode.Open);

            // Create an XmlSerializer object to perform the serialization
            XmlSerializer xs = new XmlSerializer(typeof(Person));

            // Use the XmlSerializer object to serialize the data to the file
            dsp = (Person)xs.Deserialize(fs);

            // Close the file
            fs.Close();
            return dsp;
        }
    }
}
