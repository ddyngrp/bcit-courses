/*
 * ctlValidatingData.cs - Assignment Three - Composite Control for Validating Data
 * 
 * Copyright (C) Steffen L. Norgren 2009 <ironix@trollop.org>
 *               A00683006
 *               
 * Created: 2009-06-29
 * 
 * ctlValidatingData.cs is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * ctlValidatingData.cs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.Collections;

namespace ctlValidatingDataLib
{
    public partial class ctlValidatingData : UserControl
    {
        /// <summary>
        /// Default constructor, initializes the component
        /// </summary>
        public ctlValidatingData()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Manages email address validation
        /// </summary>
        /// <param name="sender">Reference to the object that raised the event</param>
        /// <param name="e">Provides data for a cancelable event</param>
        private void txtEmail_Validating(object sender, CancelEventArgs e)
        {
            String emailRegex = @"^(([^<>()[\]\\.,;:\s@\""]+"
                  + @"(\.[^<>()[\]\\.,;:\s@\""]+)*)|(\"".+\""))@"
                  + @"((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}"
                  + @"\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+"
                  + @"[a-zA-Z]{2,}))$";

            Regex reEmail = new Regex(emailRegex);

            // Allows a blank entry
            if (!reEmail.IsMatch(txtEmail.Text) && txtEmail.Text.Length != 0)
            {
                MessageBox.Show("Error: Please enter a valid email address.",
                    "Validation Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txtEmail.Focus();
            }
        }

        /// <summary>
        /// Manages validation of credit card numbers
        /// </summary>
        /// <param name="sender">Reference to the object that raised the event</param>
        /// <param name="e">Provides data for a cancelable event</param>
        private void txtCreditCard_Validating(object sender, CancelEventArgs e)
        {
            // Does not allow a blank entry
            if (!ValidateCardNumber(txtCreditCard.Text) || txtCreditCard.Text.Length == 0)
            {
                MessageBox.Show("Error: Please enter a valid credit card number.",
                    "Validation Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txtCreditCard.Focus();
            }
        }

        /// <summary>
        /// Manages validation of the credit card's expiration date
        /// </summary>
        /// <param name="sender">Reference to the object that raised the event</param>
        /// <param name="e">Provides data for a cancelable event</param>
        private void txtValidTo_Validating(object sender, CancelEventArgs e)
        {
            String expiryRegex = @"(0[1-9]|1[012])[- /.]\d\d";

            Regex reExpiry = new Regex(expiryRegex);

            if (!reExpiry.IsMatch(txtValidTo.Text))
            {
                MessageBox.Show("Error: Please enter a valid expiry date.",
                    "Validation Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txtValidTo.Focus();
            }
        }

        /// <summary>
        /// Manages validation of numerical amounts
        /// </summary>
        /// <param name="sender">Reference to the object that raised the event</param>
        /// <param name="e">Provides data for a cancelable event</param>
        private void txtAmount_Validating(object sender, CancelEventArgs e)
        {
            String amountRegex = @"([0-9]*\.)?[0-9]";

            Regex reAmount = new Regex(amountRegex);

            if (!reAmount.IsMatch(txtAmount.Text))
            {
                MessageBox.Show("Error: Please enter a valid amount.",
                    "Validation Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txtAmount.Focus();
            }
        }

        /// <summary>
        /// Validates a credit card number based on Luhn's formula
        /// </summary>
        /// <param name="cardNumber"></param>
        /// <returns>true if valid, otherwise false</returns>
        private static bool ValidateCardNumber(String cardNumber)
        {
            try
            {
                // Array to contain individual numbers
                System.Collections.ArrayList CheckNumbers = new ArrayList();

                // Get length of card
                int CardLength = cardNumber.Length;

                // Double the value of alternate digits, starting with the second digit
                // from the right, i.e. back to front.
                // Loop through starting at the end
                for (int i = CardLength - 2; i >= 0; i = i - 2)
                {
                    // Now read the contents at each index, this
                    // can then be stored as an array of integers
                    // Double the number returned
                    CheckNumbers.Add(Int32.Parse(cardNumber[i].ToString()) * 2);
                }

                int CheckSum = 0;    // Will hold the total sum of all checksum digits

                // Second stage, add separate digits of all products
                for (int iCount = 0; iCount <= CheckNumbers.Count - 1; iCount++)
                {
                    int _count = 0;    // will hold the sum of the digits

                    // determine if current number has more than one digit
                    if ((int)CheckNumbers[iCount] > 9)
                    {
                        int _numLength = ((int)CheckNumbers[iCount]).ToString().Length;

                        // add count to each digit
                        for (int x = 0; x < _numLength; x++)
                        {
                            _count = _count + Int32.Parse(
                                ((int)CheckNumbers[iCount]).ToString()[x].ToString());
                        }
                    }
                    else
                    {
                        // single digit, just add it by itself
                        _count = (int)CheckNumbers[iCount];
                    }
                    CheckSum = CheckSum + _count;    // add sum to the total sum

                }

                // Stage 3, add the unaffected digits
                // Add all the digits that we didn't double still starting from the
                // right but this time we'll start from the rightmost number with 
                // alternating digits
                int OriginalSum = 0;

                for (int y = CardLength - 1; y >= 0; y = y - 2)
                {
                    OriginalSum = OriginalSum + Int32.Parse(cardNumber[y].ToString());
                }

                // Perform the final calculation, if the sum Mod 10 results in 0 then
                // it's valid, otherwise its false.
                return (((OriginalSum + CheckSum) % 10) == 0);
            }
            catch
            {
                return false;
            }
        }
    }
}
