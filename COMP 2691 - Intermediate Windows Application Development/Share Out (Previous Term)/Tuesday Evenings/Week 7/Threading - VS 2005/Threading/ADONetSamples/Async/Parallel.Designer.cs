namespace Threading.ADONetSamples.Async
{
    partial class Parallel
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
            this.components = new System.ComponentModel.Container();
            this.CustomerList = new System.Windows.Forms.ComboBox();
            this.QueryButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.Info = new System.Windows.Forms.Label();
            this.bindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.gridOrders = new System.Windows.Forms.DataGrid();
            this.northwindDataSet = new Threading.northwindDataSet();
            this.customersTableAdapter = new Threading.northwindDataSetTableAdapters.CustomersTableAdapter();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridOrders)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.northwindDataSet)).BeginInit();
            this.SuspendLayout();
            // 
            // CustomerList
            // 
            this.CustomerList.FormattingEnabled = true;
            this.CustomerList.Location = new System.Drawing.Point(12, 52);
            this.CustomerList.Name = "CustomerList";
            this.CustomerList.Size = new System.Drawing.Size(267, 21);
            this.CustomerList.TabIndex = 0;
            // 
            // QueryButton
            // 
            this.QueryButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.QueryButton.Location = new System.Drawing.Point(285, 52);
            this.QueryButton.Name = "QueryButton";
            this.QueryButton.Size = new System.Drawing.Size(117, 23);
            this.QueryButton.TabIndex = 1;
            this.QueryButton.Text = "Go get data";
            this.QueryButton.UseVisualStyleBackColor = true;
            this.QueryButton.Click += new System.EventHandler(this.QueryButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(161, 20);
            this.label1.TabIndex = 2;
            this.label1.Text = "Pick up a customer";
            // 
            // splitter1
            // 
            this.splitter1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitter1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.splitter1.Location = new System.Drawing.Point(0, 95);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(740, 415);
            this.splitter1.TabIndex = 3;
            this.splitter1.TabStop = false;
            // 
            // Info
            // 
            this.Info.AutoSize = true;
            this.Info.Location = new System.Drawing.Point(25, 112);
            this.Info.Name = "Info";
            this.Info.Size = new System.Drawing.Size(0, 13);
            this.Info.TabIndex = 4;
            // 
            // bindingSource1
            // 
            this.bindingSource1.DataMember = "Customers";
            this.bindingSource1.DataSource = this.northwindDataSet;
            // 
            // gridOrders
            // 
            this.gridOrders.DataMember = "";
            this.gridOrders.HeaderForeColor = System.Drawing.SystemColors.ControlText;
            this.gridOrders.Location = new System.Drawing.Point(310, 134);
            this.gridOrders.Name = "gridOrders";
            this.gridOrders.Size = new System.Drawing.Size(294, 229);
            this.gridOrders.TabIndex = 5;
            // 
            // northwindDataSet
            // 
            this.northwindDataSet.DataSetName = "northwindDataSet";
            this.northwindDataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // customersTableAdapter
            // 
            this.customersTableAdapter.ClearBeforeFill = true;
            // 
            // Parallel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(740, 510);
            this.Controls.Add(this.gridOrders);
            this.Controls.Add(this.Info);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.QueryButton);
            this.Controls.Add(this.CustomerList);
            this.Name = "Parallel";
            this.Text = "Parallel";
            this.Load += new System.EventHandler(this.Parallel_Load);
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.gridOrders)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.northwindDataSet)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox CustomerList;
        private System.Windows.Forms.Button QueryButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.Label Info;
        private System.Windows.Forms.BindingSource bindingSource1;
        private System.Windows.Forms.DataGrid gridOrders;
        private northwindDataSet northwindDataSet;
        private Threading.northwindDataSetTableAdapters.CustomersTableAdapter customersTableAdapter;
    }
}