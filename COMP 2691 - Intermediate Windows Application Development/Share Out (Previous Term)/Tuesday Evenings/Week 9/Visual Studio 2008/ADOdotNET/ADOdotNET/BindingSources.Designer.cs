namespace ADOdotNET
{
    partial class BindingSources
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnNext = new System.Windows.Forms.Button();
            this.btnPrevious = new System.Windows.Forms.Button();
            this.btnFirst = new System.Windows.Forms.Button();
            this.tbHireDate = new System.Windows.Forms.TextBox();
            this.Label3 = new System.Windows.Forms.Label();
            this.tbFullName = new System.Windows.Forms.TextBox();
            this.Label2 = new System.Windows.Forms.Label();
            this.tbEmployeeID = new System.Windows.Forms.TextBox();
            this.Label1 = new System.Windows.Forms.Label();
            this.btnLast = new System.Windows.Forms.Button();
            this.btnCreateEmployees = new System.Windows.Forms.Button();
            this.dgvOrders = new System.Windows.Forms.DataGridView();
            this.Label4 = new System.Windows.Forms.Label();
            this.txtPosition = new System.Windows.Forms.TextBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.dgvOrders)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // btnNext
            // 
            this.btnNext.Location = new System.Drawing.Point(331, 295);
            this.btnNext.Name = "btnNext";
            this.btnNext.Size = new System.Drawing.Size(38, 23);
            this.btnNext.TabIndex = 68;
            this.btnNext.Text = ">";
            this.btnNext.Click += new System.EventHandler(this.btnNext_Click);
            // 
            // btnPrevious
            // 
            this.btnPrevious.Location = new System.Drawing.Point(86, 294);
            this.btnPrevious.Name = "btnPrevious";
            this.btnPrevious.Size = new System.Drawing.Size(38, 23);
            this.btnPrevious.TabIndex = 67;
            this.btnPrevious.Text = "<";
            this.btnPrevious.Click += new System.EventHandler(this.btnPrevious_Click);
            // 
            // btnFirst
            // 
            this.btnFirst.Location = new System.Drawing.Point(42, 294);
            this.btnFirst.Name = "btnFirst";
            this.btnFirst.Size = new System.Drawing.Size(38, 23);
            this.btnFirst.TabIndex = 66;
            this.btnFirst.Text = "|<<";
            this.btnFirst.Click += new System.EventHandler(this.btnFirst_Click);
            // 
            // tbHireDate
            // 
            this.tbHireDate.Location = new System.Drawing.Point(101, 148);
            this.tbHireDate.Name = "tbHireDate";
            this.tbHireDate.Size = new System.Drawing.Size(96, 20);
            this.tbHireDate.TabIndex = 65;
            // 
            // Label3
            // 
            this.Label3.AutoSize = true;
            this.Label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label3.Location = new System.Drawing.Point(16, 155);
            this.Label3.Name = "Label3";
            this.Label3.Size = new System.Drawing.Size(65, 13);
            this.Label3.TabIndex = 64;
            this.Label3.Text = "Hire Date:";
            // 
            // tbFullName
            // 
            this.tbFullName.Location = new System.Drawing.Point(101, 122);
            this.tbFullName.Name = "tbFullName";
            this.tbFullName.Size = new System.Drawing.Size(96, 20);
            this.tbFullName.TabIndex = 63;
            // 
            // Label2
            // 
            this.Label2.AutoSize = true;
            this.Label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label2.Location = new System.Drawing.Point(17, 129);
            this.Label2.Name = "Label2";
            this.Label2.Size = new System.Drawing.Size(43, 13);
            this.Label2.TabIndex = 62;
            this.Label2.Text = "Name:";
            // 
            // tbEmployeeID
            // 
            this.tbEmployeeID.Location = new System.Drawing.Point(101, 96);
            this.tbEmployeeID.Name = "tbEmployeeID";
            this.tbEmployeeID.Size = new System.Drawing.Size(96, 20);
            this.tbEmployeeID.TabIndex = 61;
            // 
            // Label1
            // 
            this.Label1.AutoSize = true;
            this.Label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label1.Location = new System.Drawing.Point(17, 103);
            this.Label1.Name = "Label1";
            this.Label1.Size = new System.Drawing.Size(82, 13);
            this.Label1.TabIndex = 60;
            this.Label1.Text = "Employee ID:";
            // 
            // btnLast
            // 
            this.btnLast.Location = new System.Drawing.Point(375, 295);
            this.btnLast.Name = "btnLast";
            this.btnLast.Size = new System.Drawing.Size(38, 23);
            this.btnLast.TabIndex = 69;
            this.btnLast.Text = ">>|";
            this.btnLast.Click += new System.EventHandler(this.btnLast_Click);
            // 
            // btnCreateEmployees
            // 
            this.btnCreateEmployees.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnCreateEmployees.Location = new System.Drawing.Point(20, 10);
            this.btnCreateEmployees.Name = "btnCreateEmployees";
            this.btnCreateEmployees.Size = new System.Drawing.Size(178, 37);
            this.btnCreateEmployees.TabIndex = 73;
            this.btnCreateEmployees.Text = "Create bsEmployees";
            this.btnCreateEmployees.Click += new System.EventHandler(this.btnCreateEmployees_Click);
            // 
            // dgvOrders
            // 
            this.dgvOrders.Location = new System.Drawing.Point(243, 59);
            this.dgvOrders.Name = "dgvOrders";
            this.dgvOrders.Size = new System.Drawing.Size(144, 220);
            this.dgvOrders.TabIndex = 72;
            this.dgvOrders.Text = "DataGridView1";
            // 
            // Label4
            // 
            this.Label4.AutoSize = true;
            this.Label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Label4.Location = new System.Drawing.Point(200, 74);
            this.Label4.Name = "Label4";
            this.Label4.Size = new System.Drawing.Size(44, 13);
            this.Label4.TabIndex = 71;
            this.Label4.Text = "Orders";
            // 
            // txtPosition
            // 
            this.txtPosition.Location = new System.Drawing.Point(130, 295);
            this.txtPosition.Name = "txtPosition";
            this.txtPosition.Size = new System.Drawing.Size(190, 20);
            this.txtPosition.TabIndex = 70;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(204, 59);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(235, 220);
            this.pictureBox1.TabIndex = 76;
            this.pictureBox1.TabStop = false;
            // 
            // BindingSources
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(451, 335);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.btnNext);
            this.Controls.Add(this.btnPrevious);
            this.Controls.Add(this.btnFirst);
            this.Controls.Add(this.tbHireDate);
            this.Controls.Add(this.Label3);
            this.Controls.Add(this.tbFullName);
            this.Controls.Add(this.Label2);
            this.Controls.Add(this.tbEmployeeID);
            this.Controls.Add(this.Label1);
            this.Controls.Add(this.btnLast);
            this.Controls.Add(this.btnCreateEmployees);
            this.Controls.Add(this.dgvOrders);
            this.Controls.Add(this.Label4);
            this.Controls.Add(this.txtPosition);
            this.Name = "BindingSources";
            this.Text = "BindingSources";
            ((System.ComponentModel.ISupportInitialize)(this.dgvOrders)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        internal System.Windows.Forms.Button btnNext;
        internal System.Windows.Forms.Button btnPrevious;
        internal System.Windows.Forms.Button btnFirst;
        internal System.Windows.Forms.TextBox tbHireDate;
        internal System.Windows.Forms.Label Label3;
        internal System.Windows.Forms.TextBox tbFullName;
        internal System.Windows.Forms.Label Label2;
        internal System.Windows.Forms.TextBox tbEmployeeID;
        internal System.Windows.Forms.Label Label1;
        internal System.Windows.Forms.Button btnLast;
        internal System.Windows.Forms.Button btnCreateEmployees;
        internal System.Windows.Forms.DataGridView dgvOrders;
        internal System.Windows.Forms.Label Label4;
        internal System.Windows.Forms.TextBox txtPosition;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}