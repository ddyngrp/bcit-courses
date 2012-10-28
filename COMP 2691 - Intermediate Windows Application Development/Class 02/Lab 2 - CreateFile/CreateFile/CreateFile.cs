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

namespace CreateFile
{
    public partial class CreateFile : BankUIForm
    {
        private StreamWriter fileWriter; // writes data to text file
        private FileStream output; // maintains connection to file  

        public CreateFile()
        {
            InitializeComponent();
        }

        private void saveButton_Click(object sender, EventArgs e)
        {
            // create dialog box enabling user to save file
            SaveFileDialog fileChooser = new SaveFileDialog();
            DialogResult result = fileChooser.ShowDialog();
            string fileName; // name of file to save data

            fileChooser.CheckFileExists = false; // allow user to create file

            // exit event handler if user clicked "Cancel"
            if (result == DialogResult.Cancel)
                return;

            fileName = fileChooser.FileName; // get specified file name

            // show error if user specified invalid file
            if (fileName == "" || fileName == null)
                MessageBox.Show("Invalid File Name", "Error",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
            else
            {
                // save file via FileStream if user specified valid file
                try
                {
                    // open file with write access
                    output = new FileStream(fileName,
                    FileMode.OpenOrCreate, FileAccess.Write);

                    // sets file to where data is written
                    fileWriter = new StreamWriter(output);

                    // disable Save button and enable Enter button
                    saveButton.Enabled = false;
                    enterButton.Enabled = true;
                } // end try
                // handle exception if there is a problem opening the file
                catch (IOException)
                {
                    // notify user if file does not exist
                    MessageBox.Show("Error opening file", "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                } // end catch
            } // end else
        }

        private void enterButton_Click(object sender, EventArgs e)
        {
            // store TextBox values string array
            string[] values = GetTextBoxValues();

            // Record containing TextBox values to serialize
            Record record = new Record();

            // determine whether TextBox account field is empty
            if (values[(int)TextBoxIndices.ACCOUNT] != "")
            {
                // store TextBox values in Record and serialize Record
                try
                {
                    // get account number value from TextBox
                    int accountNumber = Int32.Parse(
                    values[(int)TextBoxIndices.ACCOUNT]);

                    // determine whether accountNumber is valid
                    if (accountNumber > 0)
                    {
                        // store TextBox fields in Record
                        record.Account = accountNumber;
                        record.FirstName = values[(int)TextBoxIndices.FIRST];
                        record.LastName = values[(int)TextBoxIndices.LAST];
                        record.Balance = Decimal.Parse(
                        values[(int)TextBoxIndices.BALANCE]);

                        // write Record to file, fields separated by commas
                        fileWriter.WriteLine(
                        record.Account + "," + record.FirstName + "," +
                        record.LastName + "," + record.Balance);
                    } // end if
                    else
                    {
                        // notify user if invalid account number
                        MessageBox.Show("Invalid Account Number", "Error",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                    } // end else
                } // end try
                // notify user if error occurs in serialization
                catch (IOException)
                {
                    MessageBox.Show("Error Writing to File", "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                } // end catch
                // notify user if error occurs regarding parameter format
                catch (FormatException)
                {
                    MessageBox.Show("Invalid Format", "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                } // end catch
            }
        }

        private void exitButton_Click(object sender, EventArgs e)
        {
            // determine whether file exists
            if (output != null)
            {
                try
                {
                    fileWriter.Close(); // close StreamWriter
                    output.Close(); // close file
                } // end try
                // notify user of error closing file
                catch (IOException)
                {
                    MessageBox.Show("Cannot close file", "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                } // end catch
            } // end if

            Application.Exit();

        }
    }
}
