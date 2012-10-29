
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;
using System.Runtime.Remoting.Proxies;
using System.Runtime.InteropServices;
using System.Runtime.Remoting.Messaging;
using System.Runtime.Remoting;
using System.Runtime.CompilerServices;
using ManagedOffice;
using TamilFM.Properties;

namespace TamilFM
{
    /// <summary>
    /// station data structure
    /// </summary>
    struct Station
    {
        #region Private fields
        /// <summary>
        /// station name
        /// </summary>
        string name;
        /// <summary>
        /// station url
        /// </summary>
        string url;
        /// <summary>
        /// player hint , which player to use to playback this url
        /// </summary>
        string playerHint; 
        #endregion

        /// <summary>
        /// public level expose of the all private fields
        /// </summary>
        #region Public properties
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
            }
        }
        public string URL
        {
            get
            {
                return url;
            }
            set
            {
                url = value;
            }
        }
        public string PlayerHint
        {
            get
            {
                return playerHint;
            }
            set
            {
                playerHint = value;
            }
        }
        #endregion
    }
    public partial class mainForm : Form
    {
        #region Private fields
        private Dictionary<string, Station> stationsList = new Dictionary<string, Station>();
        private Station curStation;

        AxWMPPlayer mediaPlayer = null;
        AxVLCPlayer vlcPlayer = null;

        private Dictionary<string, Panel> panelList = new Dictionary<string, Panel>();

        private NotifyIcon notifyIcon;

        private List<ToolStripMenuItem> mainMenuList = new List<ToolStripMenuItem>();

        #endregion

        #region PInvoke related

        /// <summary>
        /// to add about menu to system menu
        /// </summary>

        public const Int32 WM_SYSCOMMAND = 0x112;
        public const Int32 MF_SEPARATOR = 0x800;
        public const Int32 MF_BYPOSITION = 0x400;
        public const Int32 MF_STRING = 0x0;
        public const Int32 IDM_ABOUT = 1000;

        [DllImport("user32.dll")]
        private static extern IntPtr GetSystemMenu(IntPtr hWnd, bool bRevert);
        [DllImport("user32.dll")]
        private static extern bool InsertMenu(IntPtr hMenu,
            Int32 wPosition, Int32 wFlags, Int32 wIDNewItem,
            string lpNewItem);

        #endregion

        #region Constructors
        public mainForm()
        {
            InitializeComponent();

            InitializeStations();

        } 
        #endregion

        #region Helper methods
        /// <summary>
        /// resize the player and panel
        /// </summary>
        /// <param name="strName"></param>
        private void resizePlayer(string strName)
        {
            try
            {
                foreach (Panel panel in panelList.Values)
                {
                    panel.Visible = false;
                }
                panelList[strName].Visible = true;
                laStation.Location = new Point(panelList[strName].Location.X, panelList[strName].Height + 7);
                comboStation.Location = new Point(panelList[strName].Location.X + laStation.Width + 5, panelList[strName].Height + 5);
            }
            catch (Exception ex)
            {
                ThrowError(ex.Message);
            }
        }
        /// <summary>
        /// get the prog-id corresponding to the given clisid
        /// </summary>
        /// <param name="strProgid"></param>
        /// <returns></returns>
        private static string getClsidFromProgId(string strProgid)
        {
            ComProgIdAttribute progID = new ComProgIdAttribute(strProgid);
            if (null == progID || null == progID.Value || 0 == progID.Value.Length)
                throw new ArgumentException("The specified type must define a ComProgId attribute.", "type");

            Type comType = Type.GetTypeFromProgID(progID.Value, true);

            return comType.GUID.ToString("D");
        }
        /// <summary>
        /// throw the error
        /// </summary>
        /// <param name="strMsg"></param>
        private void ThrowError(string strMsg)
        {
            MessageBox.Show(strMsg, "Error",MessageBoxButtons.OK,MessageBoxIcon.Error);
        }
        private void ResetPlayers(string strPlayer)
        {
            try
            {
                switch (strPlayer)
                {
                    case "MPLAYER":
                        if (vlcPlayer != null)
                        {
                            vlcPlayer.stop();
                        }
                        break;
                    case "VLCPLAYER":
                        if (mediaPlayer != null)
                        {
                            mediaPlayer.URL = "";
                        }
                        break;
                }
            }
            catch (Exception ex)
            {
                ThrowError(ex.Message);
            }
        }
        /// <summary>
        /// change the station
        /// </summary>
        /// <param name="strStationName">station name</param>
        private void ApplyStation(string strStationName)
        {
            try
            {
                curStation = stationsList[strStationName];
                ResetPlayers(curStation.PlayerHint);
                switch (curStation.PlayerHint)
                {
                    case "MPLAYER":
                        if (mediaPlayer == null)
                        {
                            try
                            {
                                loadPlayer("MPLAYER");
                                if (mediaPlayer == null)
                                {
                                    MessageBox.Show("Please install windows media player 7 or higher", "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
                                    return;
                                }
                            }
                            catch (Exception ex)
                            {
                                MessageBox.Show("Please install windows media player 7 or higher\n\nError:\n" + ex.Message, "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
                                return;
                            }
                        }
                        mediaPlayer.URL = curStation.URL;
                        break;
                    case "VLCPLAYER":
                        if (vlcPlayer == null)
                        {
                            try
                            {
                                loadPlayer("VLCPLAYER");
                                if (vlcPlayer == null)
                                {
                                    MessageBox.Show("Please install vlc player\n and \n register the vlc player activex", "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
                                    return;
                                }
                            }
                            catch(Exception ex)
                            {
                                MessageBox.Show("Please install vlc player\n and \n register the vlc player activex\n\nError:\n" + ex.Message, "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
                                return;
                            }
                        }
                        vlcVolumeCtrl.Value = vlcPlayer.Volume;
                        vlcPlayer.playlistClear();
                        vlcPlayer.addTarget(curStation.URL, null, VLCPlaylistMode.VLCPlayListAppendAndGo, 0);
                        laVlcDesc.Text = "Playing...";
                        break;
                }
                resizePlayer(curStation.PlayerHint);
                this.Text = "Radio Tamil - " + curStation.Name;
                notifyIcon.Text = this.Text;
            }
            catch (Exception ex)
            {
                ThrowError(ex.Message);
            }
        }
        /// <summary>
        /// load the xml file
        /// </summary>
        private void InitializeStations()
        {
            try
            {
                notifyIcon = new NotifyIcon();
                notifyIcon.Text = "Tamil FM";
                notifyIcon.Visible = true;
                notifyIcon.Icon = new Icon(GetType(), "Tamil16.ICO"); //Thanks to Hasaki for this.
                notifyIcon.ContextMenuStrip = ctxtMenu;
                notifyIcon.MouseClick += new MouseEventHandler(notifyIcon_MouseClick);

                Station st = new Station();
                DataSet set = new DataSet();
                FileInfo fileInfo = new FileInfo(Application.ExecutablePath);
                set.ReadXml(fileInfo.DirectoryName + "\\stations.xml");
                foreach (DataRow rw in set.Tables["station"].Rows)
                {
                    st.Name = rw["Name"] as string;
                    st.URL = rw["URL"] as string;
                    st.PlayerHint = rw["PlayerHint"] as string;
                    stationsList.Add(st.Name, st);
                    comboStation.Items.Add(st.Name);
                    stationsToolStripMenuItem.DropDownItems.Add(st.Name);
                }
                comboStation.SelectedIndex = 0;

            }
            catch (Exception ex)
            {
                ThrowError(ex.Message);
                Application.Exit();
            }

        } 
        #endregion

        #region Player initialization
        /// <summary>
        /// load the player on-demand by name
        /// </summary>
        /// <param name="strName"></param>
        private void loadPlayer(string strName)
        {
            switch (strName)
            {
                case "MPLAYER":
                    ///Initialize the windows media player
                    mediaPlayer = new AxWMPPlayer(getClsidFromProgId("WMPlayer.OCX.7"));
                    if (mediaPlayer != null)
                    {
                        Panel panel = new Panel();
                        panel.SuspendLayout();
                        this.SuspendLayout();

                        panel.Controls.Add(mediaPlayer);
                        panel.Location = new System.Drawing.Point(6, 0);
                        panel.Name = "mediaPlayerPanel";
                        panel.Size = new System.Drawing.Size(504, 65);

                        ((System.ComponentModel.ISupportInitialize)(mediaPlayer)).BeginInit();
                        mediaPlayer.Enabled = true;
                        mediaPlayer.Location = new System.Drawing.Point(1, 0);
                        mediaPlayer.Name = "mediaPlayer";
                        mediaPlayer.Size = new System.Drawing.Size(503, 65);

                        Controls.Add(panel);

                        panel.ResumeLayout();
                        ((System.ComponentModel.ISupportInitialize)(mediaPlayer)).EndInit();
                        mediaPlayer.uiMode = "mini";

                        this.ResumeLayout(false);
                        this.PerformLayout();

                        panelList.Add("MPLAYER", panel);
                    }
                    else
                    {
                        return;
                    }
                    break;
                case "VLCPLAYER":
                    ///Initialize the vlc media player
                    vlcPlayer = new AxVLCPlayer(getClsidFromProgId("VideoLAN.VLCPlugin.1"));
                    vlcVolumeCtrl = new VolumeControl();
                    lavlcVolume = new Label();
                    vlcPlayBttn = new Button();
                    vlcStopBttn = new Button();
                    laVlcDesc = new Label();
                    if (vlcPlayer != null)
                    {
                        Panel panel = new Panel();

                        panel.SuspendLayout();
                        this.SuspendLayout();

                        panel.Controls.Add(this.vlcStopBttn);
                        panel.Controls.Add(this.vlcPlayBttn);
                        panel.Controls.Add(this.lavlcVolume);
                        panel.Controls.Add(this.vlcVolumeCtrl);
                        panel.Controls.Add(this.laVlcDesc);
                        panel.Controls.Add(vlcPlayer);
                        panel.Location = new System.Drawing.Point(6, 0);
                        panel.Name = "vlcPlayerPanel";
                        panel.Size = new System.Drawing.Size(504, 65);

                        // 
                        // vlcVolumeCtrl
                        // 
                        vlcVolumeCtrl.BackColor = System.Drawing.Color.White;
                        vlcVolumeCtrl.ForeColor = System.Drawing.Color.Blue;
                        vlcVolumeCtrl.Location = new System.Drawing.Point(402, 45);
                        vlcVolumeCtrl.Name = "vlcVolumeCtrl";
                        vlcVolumeCtrl.Size = new System.Drawing.Size(87, 10);
                        vlcVolumeCtrl.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
                        vlcVolumeCtrl.TabIndex = 4;
                        vlcVolumeCtrl.VolumeChanged += new TamilFM.volumeChanged(this.vlcVolumeCtrl_VolumeChanged);
                        // 
                        // lavlcVolume
                        // 
                        lavlcVolume.AutoSize = true;
                        lavlcVolume.Location = new System.Drawing.Point(348, 45);
                        lavlcVolume.Name = "lavlcVolume";
                        lavlcVolume.Size = new System.Drawing.Size(48, 13);
                        lavlcVolume.TabIndex = 6;
                        lavlcVolume.Text = "Volume :";
                        // 
                        // vlcPlayBttn
                        // 
                        vlcPlayBttn.Location = new System.Drawing.Point(79, 39);
                        vlcPlayBttn.Name = "vlcPlayBttn";
                        vlcPlayBttn.Size = new System.Drawing.Size(42, 24);
                        vlcPlayBttn.TabIndex = 7;
                        vlcPlayBttn.Text = "Play";
                        vlcPlayBttn.UseVisualStyleBackColor = true;
                        vlcPlayBttn.Click += new System.EventHandler(this.vlcPlayBttn_Click);
                        // 
                        // vlcStopBttn
                        // 
                        vlcStopBttn.Location = new System.Drawing.Point(161, 39);
                        vlcStopBttn.Name = "vlcStopBttn";
                        vlcStopBttn.Size = new System.Drawing.Size(42, 24);
                        vlcStopBttn.TabIndex = 8;
                        vlcStopBttn.Text = "Stop";
                        vlcStopBttn.UseVisualStyleBackColor = true;
                        vlcStopBttn.Click += new System.EventHandler(this.vlcStopBttn_Click);
                        // 
                        // laVlcDesc
                        // 
                        laVlcDesc.Location = new System.Drawing.Point(225, 39);
                        laVlcDesc.Name = "laVlcDesc";
                        laVlcDesc.Size = new System.Drawing.Size(42, 24);
                        vlcStopBttn.TabIndex = 8;
                        laVlcDesc.Text = "Stopped...";

                        ((System.ComponentModel.ISupportInitialize)(vlcPlayer)).BeginInit();

                        vlcPlayer.Enabled = true;
                        vlcPlayer.Location = new System.Drawing.Point(0, 9);
                        vlcPlayer.Name = "vlcPlayer";
                        vlcPlayer.Size = new System.Drawing.Size(55, 50);

                        Controls.Add(panel);

                        panel.ResumeLayout();

                        ((System.ComponentModel.ISupportInitialize)(vlcPlayer)).EndInit();

                        this.ResumeLayout(false);
                        this.PerformLayout();
                        ///workaround for vlc player size problem
                        vlcPlayer.Location = new System.Drawing.Point(0, 9);
                        vlcPlayer.Size = new System.Drawing.Size(55, 50);
                        vlcPlayer.AutoPlay = true;

                        panelList.Add("VLCPLAYER", panel);
                    }
                    else
                    {
                        return;
                    }
                    break;
            }
        } 
        #endregion
        
        #region Control/menu event handlers
        /// <summary>
        /// select radio stations by clicking combo box
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboStation_SelectedIndexChanged(object sender, EventArgs e)
        {
            ApplyStation(comboStation.SelectedItem as string);
        }
        /// <summary>
        /// play vlc player
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void vlcPlayBttn_Click(object sender, EventArgs e)
        {
            try
            {
                if (vlcPlayer != null)
                {
                    vlcPlayer.play();
                    laVlcDesc.Text = "Playing...";
                }
            }
            catch (Exception ex)
            {
                ThrowError(ex.Message);
            }
        }
        /// <summary>
        /// stop vlc player
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void vlcStopBttn_Click(object sender, EventArgs e)
        {
            try
            {
                if (vlcPlayer != null)
                {
                    vlcPlayer.stop();
                    laVlcDesc.Text = "Stopped...";
                }
            }
            catch (Exception ex)
            {
                ThrowError(ex.Message);
            }
        }
        /// <summary>
        /// change the vlc volume
        /// </summary>
        private void vlcVolumeCtrl_VolumeChanged()
        {
            try
            {
                if (vlcPlayer != null)
                {
                    vlcPlayer.Volume = vlcVolumeCtrl.Value;
                }
            }
            catch (Exception ex)
            {
                ThrowError(ex.Message);
            }
        }
        /// <summary>
        /// select stations by clicking menu
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void stationsToolStripMenuItem_DropDownItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            try
            {
                comboStation.SelectedIndex = comboStation.FindString(e.ClickedItem.ToString());
            }
            catch (Exception ex)
            {
                ThrowError(ex.Message);
            }
        }
        /// <summary>
        /// exit from the player
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        /// <summary>
        /// handle the close button message
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                e.Cancel = true;
                Hide();
            }
        }
        /// <summary>
        /// show the main window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void showMainToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Show();
            WindowState = FormWindowState.Normal;
            BringToFront();
        }
        /// <summary>
        /// about menu clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            aboutForm frm = new aboutForm();
            frm.ShowDialog();
            frm.Dispose();
        }
        /// <summary>
        /// to handle the minimize button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mainForm_SizeChanged(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Minimized)
            {
                Hide();
            }
        }
        /// <summary>
        /// to edit system menu
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void mainForm_Load(object sender, EventArgs e)
        {
            IntPtr sysMenuHandle = GetSystemMenu(this.Handle, false);
            InsertMenu(sysMenuHandle, 5, MF_BYPOSITION | MF_SEPARATOR, 0, string.Empty);
            InsertMenu(sysMenuHandle, 6, MF_BYPOSITION, IDM_ABOUT, "About");
        }
        private void notifyIcon_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                showMainToolStripMenuItem_Click(sender, e);
            }
        }
        #endregion

        #region Override methods
        protected override void WndProc(ref System.Windows.Forms.Message m)
        {
            if (m.Msg == WM_SYSCOMMAND)
            {
                switch (m.WParam.ToInt32())
                {
                    case IDM_ABOUT:
                        aboutToolStripMenuItem_Click(this, new EventArgs());
                        break;
                }
            }
            base.WndProc(ref m);
        } 
        #endregion


    }
}