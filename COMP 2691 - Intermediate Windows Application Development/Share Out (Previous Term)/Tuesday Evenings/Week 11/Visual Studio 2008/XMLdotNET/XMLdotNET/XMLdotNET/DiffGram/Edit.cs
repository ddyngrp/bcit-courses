using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Collections;

//    Child form to edit DataSet and see effects on the DiffGram schema

namespace XMLdotNET.DiffGram
{
    public partial class Edit : Form
    {
        public Edit()
        {
            InitializeComponent();
        }

        // ***************************************************************************
        // DataInstance property
        private DataSet m_dataInstance;
        public DataSet DataInstance
        {
            get { return m_dataInstance; }
            set
            {
                m_dataInstance = value;
                CurrentData.DataSource = m_dataInstance;
                m_bmbEmployees = (CurrencyManager)this.BindingContext[m_dataInstance, "Employees"];
                m_bmbEmployees.CurrentChanged += new EventHandler(CurrentChanged);
                m_bmbTerritories = (CurrencyManager)this.BindingContext[m_dataInstance, "Territories"];
                m_bmbTerritories.CurrentChanged += new EventHandler(CurrentChanged);
            }
        }
        // ***************************************************************************

        // ***************************************************************************
        // CurrencyManager properties
        private CurrencyManager m_bmbEmployees;
        private CurrencyManager m_bmbTerritories;
        // ***************************************************************************

        // ***************************************************************************
        // Rejects all pending changes
        private void ButtonReject_Click(object sender, System.EventArgs e)
        {
            m_dataInstance.RejectChanges();
            CurrentData.Refresh();
        }
        // ***************************************************************************

        // ***************************************************************************
        // Expands the available tables
        private void EditForm_Load(object sender, System.EventArgs e)
        {
            CurrentData.Expand(-1);
        }
        // ***************************************************************************

        // ***************************************************************************
        // Refresh the application's UI whenever a change is detected
        private void CurrentChanged(object sender, EventArgs e)
        {
            ButtonDelete.Enabled = true;
        }
        // ***************************************************************************

        // ***************************************************************************
        // Delete the current grid row
        private void ButtonDelete_Click(object sender, System.EventArgs e)
        {
            CurrencyManager cm = (CurrencyManager)this.BindingContext[m_dataInstance, CurrentData.DataMember];
            DataRowView row = (DataRowView)cm.Current;
            row.Delete();
        }
        // ***************************************************************************

        // ***************************************************************************
        // Set a column error message on the row
        private void ButtonSetError_Click(object sender, System.EventArgs e)
        {
            CurrencyManager cm = (CurrencyManager)this.BindingContext[m_dataInstance, CurrentData.DataMember];
            DataRowView dr = (DataRowView)cm.Current;
            dr.Row.SetColumnError(ErrorColumn.Text, ErrorMessage.Text);
        }
        // ***************************************************************************

        // ***************************************************************************
        // Clear all errors on the row
        private void ButtonClear_Click(object sender, System.EventArgs e)
        {
            CurrencyManager cm = (CurrencyManager)this.BindingContext[m_dataInstance, CurrentData.DataMember];
            DataRowView dr = (DataRowView)cm.Current;
            dr.Row.ClearErrors();
        }
        // ***************************************************************************

        // ***************************************************************************
        // Set a general row error message on the row
        private void ButtonRowError_Click(object sender, System.EventArgs e)
        {
            CurrencyManager cm = (CurrencyManager)this.BindingContext[m_dataInstance, CurrentData.DataMember];
            DataRowView dr = (DataRowView)cm.Current;
            dr.Row.RowError = ErrorMessage.Text;
        }

        // ***************************************************************************
        // Save all the manual changes to the DataSet
        private void ButtonSave_Click(object sender, System.EventArgs e)
        {
            CurrentData.Update();
            CurrentData.Refresh();
        }
        // ***************************************************************************




    }
}