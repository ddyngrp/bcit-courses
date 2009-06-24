/*
 * ReadSequentialAccessFileForm.cs - Assignment Two - Sequential File Reader
 * 
 * Copyright (C) Steffen L. Norgren 2009 <ironix@trollop.org>
 *               A00683006
 *               
 * Created: 2009-06-24
 * 
 * ReadSequentialAccessFileForm.cs is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 * 
 * ReadSequentialAccessFileForm.cs is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

        /// <summary>
        /// 
        /// </summary>
        public ReadSequentialAccessFileForm()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Displays the open file dialog box, allowing the user to select a
        /// .dat file for the application to use for reading records.
        /// </summary>
        /// <param name="sender">The object sending the event</param>
        /// <param name="e">The arguments being sent by the event</param>
        private void openButton_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog(); // Displays an OpenFileDialog

            ofd.Filter = "Data Files|*.dat";  // Hide all non .dat files
            ofd.Title = "Select a Data File"; // Sets the dialogue title

            // Creates a dialog box enabling user to open file
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                // Show error if user specified invalid file
                if (!ofd.FileName.EndsWith(".dat"))
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

            // Try and create FileStream to obtain read access to file
            try
            {
                input = File.Open(ofd.FileName, FileMode.Open);
            }
            catch (IOException err)
            {
                MessageBox.Show(err.Message, "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);

                return;
            }

            // Set file from where data is read
            fileReader = new StreamReader(input);

            // Enable the next record button
            nextButton.Enabled = true;

            // Disable the open file button
            openButton.Enabled = false;
            
            // Release resources
            ofd.Dispose();
        }

        /// <summary>
        /// Cycles through all the records in the file and closes all open file
        /// handles once the end has been reached.
        /// </summary>
        /// <param name="sender">The object sending the event</param>
        /// <param name="e">The arguments being sent by the event</param>
        private void nextButton_Click(object sender, EventArgs e)
        {
            try
            {
                // Get the next record
                string inputRecord = fileReader.ReadLine();
                string[] inputFields; // Stores each field of data

                if (inputRecord != null)
                {
                    // Split the string into records
                    inputFields = inputRecord.Split(',');

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
                    // Close StreamReader
                    fileReader.Close();

                    // Close FileStream if no Records in file
                    input.Close();

                    // Enable Open File button
                    openButton.Enabled = true;

                    // Disable Next Record button
                    nextButton.Enabled = false;

                    // Clear All TextBox Controls
                    this.ClearTextBoxes();

                    // Notify user if no Records in file
                    MessageBox.Show("There are no more records left in the file.", "End of Records",
                        MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            catch (IOException err)
            {
                MessageBox.Show("Error Reading from File: " + err.Message, "Error",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);

                // Enable Open File button
                openButton.Enabled = true;

                // Disable Next Record button
                nextButton.Enabled = false;
            }
        }

        /// <summary>
        /// Close all open resources and release all associated resources.
        /// </summary>
        /// <param name="sender">The object sending the event</param>
        /// <param name="e">The arguments being sent by the event</param>
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
