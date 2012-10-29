using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace GUIConceptsPart2
{
    public partial class ImageListControl : Form
    {
        protected Graphics myGraphics;
        private int currentImage = 0;
        
        public ImageListControl()
        {
            InitializeComponent();
            imageList1 = new ImageList();

            // The default image size is 16 x 16
            imageList1.ImageSize = new Size(64, 64);
            // imageList1.TransparentColor = Color.White; // not for icons
            
            // Assigns the graphics object to use in the draw options.
            myGraphics = Graphics.FromHwnd(pnlImage.Handle);

        }

        // Display the image.
        private void btnShowNextImage_Click(object sender, System.EventArgs e)
        {
            if (imageList1.Images.Empty != true)
            {
                if (imageList1.Images.Count - 1 > currentImage)
                {
                    currentImage++;
                }
                else
                {
                    currentImage = 0;
                }

                lstImageLocation.SelectedIndex = currentImage;
                
                showImage(currentImage);
               
            }
        }

        // Show the image
        private void showImage(int intSelectedImage)
        {
            pnlImage.Refresh();
            //clear out the picture box 
            picImage.Image = null;

            // Draw the image in the panel.
            imageList1.Draw(myGraphics, 10, 10, intSelectedImage);
            // Notice that myGraphics refer to Graphics.FromHwnd(pnlImage.Handle);

            // Show the image in the PictureBox.
            picImage.Image = imageList1.Images[intSelectedImage];
            lblCurrentImage.Text = "Current image is " + intSelectedImage;
            lblImageLocation.Text = "Image is " + lstImageLocation.Text;

        }

        // Remove the image.
        private void btnRemoveImage_Click(object sender, System.EventArgs e)
        {
            int intSelectedIndex;
            try
            {
                intSelectedIndex = lstImageLocation.SelectedIndex;
                imageList1.Images.RemoveAt(lstImageLocation.SelectedIndex);
                lstImageLocation.Items.Remove(lstImageLocation.SelectedItem);

                lstImageLocation.SelectedIndex = intSelectedIndex - 1;

                showImage(intSelectedIndex - 1);
            }
            catch
            {
               // if (imageList1.Images.Empty != true)
               // MessageBox.Show("Please select the image first.");
              
            }
        }

        // Clear all images.
        private void btnClearList_Click(object sender, System.EventArgs e)
        {
            imageList1.Images.Clear();
            lstImageLocation.Items.Clear();
        }

        // Browse for an image.
        private void btnOpenImage_Click(object sender, System.EventArgs e)
        {
            openFileDialog1.Multiselect = true;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if (openFileDialog1.FileNames != null)
                {
                    for (int i = 0; i < openFileDialog1.FileNames.Length; i++)
                    {
                        addImage(openFileDialog1.FileNames[i]);
                    }
                }
                else
                        addImage(openFileDialog1.FileName);
            }
        }
        // Add the image
        private void addImage(string imageToLoad)
        {
            if (imageToLoad != "")
            {
                imageList1.Images.Add(Image.FromFile(imageToLoad));
                lstImageLocation.BeginUpdate();
                lstImageLocation.Items.Add(imageToLoad);
                lstImageLocation.EndUpdate();
            }
        }
       

    }
}