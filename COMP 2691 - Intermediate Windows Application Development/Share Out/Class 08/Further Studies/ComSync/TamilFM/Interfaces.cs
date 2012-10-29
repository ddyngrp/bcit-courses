
using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Runtime.Remoting.Proxies;
using System.Runtime.InteropServices;
using System.Runtime.Remoting.Messaging;
using System.Runtime.Remoting;
using System.Reflection;
using ManagedOffice;

namespace TamilFM
{
    #region IWMPCore
    /// <summary>
    /// windows media player interface
    /// </summary>
    [ComProgId("WMPlayer.OCX.7")]
    public interface IWMPCore : IDisposable
    {
        bool isOnline
        {
            get;
        }

        string status
        {
            get;
        }

        string URL
        {
            get;
            set;
        }
        string uiMode
        {
            get;
            set;
        }
    } 
    #endregion

    #region IVLCCore
    /// <summary>
    /// vlc player default interface
    /// </summary>
    [ComProgId("VideoLAN.VLCPlugin.1")]
    public interface IVLCCore : IDisposable
    {
        bool AutoPlay
        {
            get;
            set;
        }

        string MRL
        {
            get;
            set;
        }
        bool Playing
        {
            get;
        }
        int Volume
        {
            get;
            set;
        }
        void addTarget(string uri, object options, VLCPlaylistMode mode, int position);
        void playlistClear();
        void play();
        void stop();
    }
    #endregion
}
