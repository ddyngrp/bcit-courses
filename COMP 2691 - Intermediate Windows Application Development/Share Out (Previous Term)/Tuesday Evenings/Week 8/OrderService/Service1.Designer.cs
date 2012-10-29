namespace WindowsService_SectionTen
{
    partial class Service1
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            this.ServiceName = "Service1";



            this.fswOrders = new System.IO.FileSystemWatcher();
            ((System.ComponentModel.ISupportInitialize)(this.fswOrders)).BeginInit();
            // 
            // fswOrders
            // 
            this.fswOrders.EnableRaisingEvents = true;
            this.fswOrders.Filter = "*.xml";
            this.fswOrders.Path = "c:\\orders";
            this.fswOrders.Created += new System.IO.FileSystemEventHandler(this.fswOrders_Created);
            // 
            // OrderService
            // 
            this.CanPauseAndContinue = true;
         //   this.ServiceName = "OrderService";
            ((System.ComponentModel.ISupportInitialize)(this.fswOrders)).EndInit();

        }

        #endregion
    }
}
