
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
    #region Vlc player related enums
    public enum VLCPlaylistMode
    {
        VLCPlayListInsert = 1,
        VLCPlayListInsertAndGo = 9,
        VLCPlayListReplace = 2,
        VLCPlayListReplaceAndGo = 10,
        VLCPlayListAppend = 4,
        VLCPlayListAppendAndGo = 12,
        VLCPlayListCheckInsert = 16
    } 
    #endregion

    /// <summary>
    /// vlc player activex control host class
    /// </summary>
    [System.ComponentModel.DesignTimeVisibleAttribute(true)]
    public class AxVLCPlayer : AxHost
    {
        #region Private fields
        /// <summary>
        /// vlc activex control default interface
        /// </summary>
        IVLCCore ocx; 
        #endregion

        #region Constructors
        public AxVLCPlayer(string strClaid)
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
                this.ocx = (IVLCCore)COMWrapper.Wrap(this.GetOcx(), typeof(IVLCCore));
            }
            catch (System.Exception)
            {
            }
        } 
        #endregion

        #region All public vlc player properties
        /// <summary>
        /// enable autoplay mode
        /// </summary>
        public bool AutoPlay
        {
            get
            {
                if (ocx == null)
                    throw new AxHost.InvalidActiveXStateException("AutoPlay", AxHost.ActiveXInvokeKind.PropertyGet);
                return ocx.AutoPlay;
            }
            set
            {
                if (ocx == null)
                    throw new AxHost.InvalidActiveXStateException("AutoPlay", AxHost.ActiveXInvokeKind.PropertySet);
                ocx.AutoPlay = value;
            }
        }
        /// <summary>
        /// get/set mrl links
        /// </summary>
        public string MRL
        {
            get
            {
                if (ocx == null)
                    throw new AxHost.InvalidActiveXStateException("MRL", AxHost.ActiveXInvokeKind.PropertyGet);
                return ocx.MRL;
            }
            set
            {
                if (ocx == null)
                    throw new AxHost.InvalidActiveXStateException("MRL", AxHost.ActiveXInvokeKind.PropertySet);
                ocx.MRL = value;
            }
        }
        /// <summary>
        /// check wheather the player is playing its content or not
        /// </summary>
        public bool Playing
        {
            get
            {
                if (ocx == null)
                    throw new AxHost.InvalidActiveXStateException("Playing", AxHost.ActiveXInvokeKind.PropertyGet);
                return ocx.Playing;
            }
        }
        /// <summary>
        /// get/set volume
        /// </summary>
        public int Volume
        {
            get
            {
                if (ocx == null)
                    throw new AxHost.InvalidActiveXStateException("Volume", AxHost.ActiveXInvokeKind.PropertyGet);
                return ocx.Volume;
            }
            set
            {
                if (ocx == null)
                    throw new AxHost.InvalidActiveXStateException("Volume", AxHost.ActiveXInvokeKind.PropertySet);
                ocx.Volume = value;
            }
        } 
        #endregion

        #region vlc player public methods
        /// <summary>
        /// add target to play list
        /// </summary>
        /// <param name="uri">URL</param>
        /// <param name="options">most cases null</param>
        /// <param name="mode">VLCPlaylistMode</param>
        /// <param name="position">in play list</param>
        public void addTarget(string uri, object options, VLCPlaylistMode mode, int position)
        {
            if (ocx == null)
                throw new AxHost.InvalidActiveXStateException("addTarget", AxHost.ActiveXInvokeKind.MethodInvoke);
            ocx.addTarget(uri, options, mode, position);
        }
        /// <summary>
        /// clear play list
        /// </summary>
        public void playlistClear()
        {
            if (ocx == null)
                throw new AxHost.InvalidActiveXStateException("playlistClear", AxHost.ActiveXInvokeKind.MethodInvoke);
            ocx.playlistClear();
        }
        /// <summary>
        /// start/resume play
        /// </summary>
        public void play()
        {
            if (ocx == null)
                throw new AxHost.InvalidActiveXStateException("play", AxHost.ActiveXInvokeKind.MethodInvoke);
            ocx.play();
        }
        /// <summary>
        /// stop playing
        /// </summary>
        public void stop()
        {
            if (ocx == null)
                throw new AxHost.InvalidActiveXStateException("stop", AxHost.ActiveXInvokeKind.MethodInvoke);
            ocx.stop();
        } 
        #endregion

    }

}
