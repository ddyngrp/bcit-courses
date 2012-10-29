using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using FinalExam;

namespace FinalExamGUI
{
    public partial class MainForm : Form
    {
        private WritingUtensilCollection writeCollection;
        private int blueCount, redCount, blackCount, otherCount;

        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            writeCollection = new WritingUtensilCollection();

            writeCollection.Add(new BallPointPen("Blue", "fine"));
            writeCollection.Add(new BallPointPen("Blue", "medium"));
            writeCollection.Add(new BallPointPen("Red", "broad"));
            writeCollection.Add(new BallPointPen("Green", "fine"));
            writeCollection.Add(new Pencil("Black", "HB"));
            writeCollection.Add(new MechanicalPencil("Black", "HB", 10));

            lstWritingUtensils.DataSource = writeCollection;
            ColourInformation();
        }

        private void ColourInformation()
        {
            blueCount = writeCollection.GetColourCount("Blue");
            redCount = writeCollection.GetColourCount("Red");
            blackCount = writeCollection.GetColourCount("Black");
            otherCount = writeCollection.Count - blueCount - redCount - blackCount;

            lblItems.Text = String.Format("Items: {0}", writeCollection.Count);
            lblItemDetails.Text = String.Format("Blues: {0}, Reds: {1}, Blacks: {2}, Others: {3}",
                blueCount, redCount, blackCount, otherCount);
        }

        private void lstWritingUtensils_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (writeCollection[lstWritingUtensils.SelectedIndex]
                .ToString().ToLower().Contains("mechanical"))
            {
                PencilDetailsForm dlg = new PencilDetailsForm(
                    (MechanicalPencil)writeCollection[lstWritingUtensils.SelectedIndex]);
                dlg.ShowDialog();
                dlg.Dispose();
                ColourInformation();
            }
        }

        private void lstWritingUtensils_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}