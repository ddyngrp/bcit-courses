using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using BankLibrary;

namespace ReadSequentialAccessFileForm
{
    public partial class ReadSequentialAccessFileForm : BankUIForm
    {
        private StreamReader fileReader; // reads data from a text file
        private FileStream input;        // maintains connection to a file  

        public ReadSequentialAccessFileForm()
        {
            InitializeComponent();
        }

        private void openButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog(); // Displays an OpenFileDialog
            string fileName;

            ofd.Filter = "Data Files|*.dat";  // Hide all non .dat files
            ofd.Title = "Select a Data File"; // Sets the dialogue title

            // Creates a dialog box enabling user to open file
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                fileName = ofd.FileName; // Get specified file name

                // Show error if user specified invalid file
                if (!fileName.EndsWith(".dat"))
                {
                    MessageBox.Show("Invalid file type.", "Error",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);

                    return;
                }
            }
            else // Exit event handler if user clicked Cancel
            {
                return;
            }

            // TODO: create FileStream to obtain read access to file
            // TODO: set file from where data is read
            
            // Release resources
            ofd.Dispose();
        }

        private void nextButton_Click(object sender, EventArgs e)
        {
            try
            {
                // Get the next record
                string inputRecord = fileReader.ReadLine();
                string[] inputFields; // Stores each field of data

                if (inputRecord != null)
                {
                    inputFields = null; // TODO???

                    Record record = new Record(
                        Convert.ToInt32(inputFields[0]),
                        inputFields[1],
                        inputFields[2],
                        Convert.ToDecimal(inputFields[3]));

                    // Copy string array values to TextBox values
                    SetTextBoxValues(inputFields);
                }
                else
                {
                    // TODO: close StreamReader
                    // TODO: close FileStream if no Records in file
                    // TODO: enable Open File button
                    // TODO: disable Next Record button
                    // TODO: Clear All TextBox Controls
                    // TODO: notify user if no Records in file
                }
            }
            catch (IOException)
            {
                MessageBox.Show("Error Reading from File", "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ReadSequentialAccessFileForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (fileReader != null)
            {
                fileReader.Close();
                fileReader.Dispose();
            }

            if (input != null)
            {
                input.Close();
                input.Dispose();
            }
        }
    }
}
