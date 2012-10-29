
using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.IO;
using System.Runtime.Remoting.Proxies;
using System.Runtime.InteropServices;
using System.Runtime.Remoting.Messaging;
using System.Runtime.Remoting;
using System.Reflection;
using ManagedOffice;

namespace TamilFM
{
    /// <summary>
    /// windows media player activex host
    /// </summary>
    [System.ComponentModel.DesignTimeVisibleAttribute(true)]
    public class AxWMPPlayer : System.Windows.Forms.AxHost
    {
        #region Private field
        /// <summary>
        /// windows media player core interface
        /// </summary>
        IWMPCore ocx; 
        #endregion

        #region Constructor
        public AxWMPPlayer(string strClaid)
            : base(strClaid)
        {

        } 
        #endregion

        #region override methods
        /// <summary>
        /// must be overrided to initialize the ocx field
        /// </summary>
        protected override void AttachInterfaces()
        {
            try
            {
                this.ocx = (IWMPCore)COMWrapper.Wrap(this.GetOcx(), typeof(IWMPCore));
            }
            catch (System.Exception)
            {

            }
        } 
        #endregion

        #region mediaplayer public properties
        public string URL
        {
            get
            {
                if (ocx == null)
                    throw new AxHost.InvalidActiveXStateException("URL", AxHost.ActiveXInvokeKind.PropertyGet);
                return ocx.URL;
            }
            set
            {
                if (ocx == null)
                    throw new AxHost.InvalidActiveXStateException("URL", AxHost.ActiveXInvokeKind.PropertySet);
                ocx.URL = value;
            }
        }
        public string uiMode
        {
            get
            {
                if (ocx == null)
                    throw new AxHost.InvalidActiveXStateException("uiMode", AxHost.ActiveXInvokeKind.PropertyGet);
                return ocx.uiMode;
            }
            set
            {
                if (ocx == null)
                    throw new AxHost.InvalidActiveXStateException("uiMode", AxHost.ActiveXInvokeKind.PropertySet);
                ocx.uiMode = value;
            }
        } 
        #endregion
    }
}
