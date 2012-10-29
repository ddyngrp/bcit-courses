using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;

// All of the types in News.dll are in this namespace.
using COMP2690.News;

namespace COMP2690_Ass05
{
    public partial class NewsReader : Form
    {
        private NewsgroupCollection groups;
        private ArticleCollection articleHeaders;
        private String article;

        private Hashtable groupHistory; // will be of the format <Newsgroup, articleHistory>
        private Hashtable articleHistory; // will be of the format <articleHeader, article>

        public NewsReader()
        {
            InitializeComponent();
        }

        private void NewsReader_Load(object sender, EventArgs e)
        {
            CheckFilterGroups();
            groupHistory = new Hashtable();
            articleHistory = new Hashtable();
        }

        private void fileExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void onlineGetGroupList_Click(object sender, EventArgs e)
        {
            this.Cursor = Cursors.WaitCursor;

            clearGroupsList();
            downloadGroups();
            populateGroupsList();

            this.Cursor = Cursors.Default;
        }

        private void lstGroups_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            Newsgroup selectedGroup = (Newsgroup)lstGroups.SelectedItem;

            if (!groupHistory.ContainsKey(selectedGroup))
            {
                this.Cursor = Cursors.WaitCursor;

                clearArticleHeaderList();
                downloadArticleHeaders();
                populateArticleHeaders();

                this.Cursor = Cursors.Default;
            }
        }

        private void lstArticleHeaders_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            Article selectedArticle = (Article)lstArticleHeaders.SelectedItem;

            if (!articleHistory.ContainsKey(selectedArticle))
            {
                this.Cursor = Cursors.WaitCursor;

                clearArticle();
                downloadArticle();
                populateArticle();

                this.Cursor = Cursors.Default;
            }
        }

        private void chkFilterGroups_CheckedChanged(object sender, EventArgs e)
        {
            CheckFilterGroups();
        }

        private void chkFilterArticles_CheckedChanged(object sender, EventArgs e)
        {
            CheckFilterGroups();
        }

        private void lstGroups_SelectedIndexChanged(object sender, EventArgs e)
        {
            clearArticleHeaderList();

            if (lstGroups.SelectedItem != null)
            {
                Newsgroup selectedGroup = (Newsgroup)lstGroups.SelectedItem;

                if (groupHistory.ContainsKey(selectedGroup))
                {
                    lstArticleHeaders.DataSource = groupHistory[selectedGroup];
                }
            }
        }

        private void lstArticleHeaders_SelectedIndexChanged(object sender, EventArgs e)
        {
            clearArticle();

            if (lstArticleHeaders.SelectedItem != null)
            {
                Article selectedArticle = (Article)lstArticleHeaders.SelectedItem;

                if (articleHistory.ContainsKey(selectedArticle))
                {
                    txtArticle.Text = (string)articleHistory[selectedArticle];
                }
            }
        }

        private bool downloadGroups()
        {
            string server = txtServer.Text;

            // add an item to the group filter list
            addGroupFilters();

            string[] filterList = cboGroupFilters.Text.Split(' ');

            try
            {
                // Temporary connection to the server.
                NewsConnection connection = new NewsConnection();
                connection.Connect(server);

                if (chkFilterGroups.Checked)
                {
                    if (radInclude.Checked)
                    {
                        groups = connection.GetNewsgroups(filterList, null);
                    }
                    else
                    {
                        groups = connection.GetNewsgroups(null, filterList);
                    }
                }
                else
                {
                    groups = connection.GetNewsgroups();
                }

                connection.Disconnect();

                return true;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Download Articles", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return false;
            }
        }

        private bool downloadArticleHeaders()
        {
            string server = txtServer.Text;

            try
            {
                // Temporary connection to the server.
                NewsConnection connection = new NewsConnection();

                connection.Connect(server);

                Newsgroup selectedGroup = (Newsgroup)lstGroups.SelectedItem;

                if (chkFilterArticles.Checked)
                {
                    int articleLimit;
                    int.TryParse(txtGetNumber.Text, out articleLimit);

                    articleHeaders = connection.GetArticleHeaders(selectedGroup, articleLimit);
                }
                else
                {
                    articleHeaders = connection.GetArticleHeaders(selectedGroup);
                }

                connection.Disconnect();

                if (!groupHistory.ContainsKey(selectedGroup))
                {
                    groupHistory.Add(selectedGroup, articleHeaders);
                }

                return true;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Download Newsgroups", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return false;
            }
        }

        private bool downloadArticle()
        {
            string server = txtServer.Text;

            try
            {
                // Temporary connection to the server.
                NewsConnection connection = new NewsConnection();

                connection.Connect(server);

                Newsgroup selectedGroup = (Newsgroup)lstGroups.SelectedItem;
                Article selectedArticle = (Article)lstArticleHeaders.SelectedItem;

                connection.GetArticle(selectedGroup, selectedArticle);
                article = selectedArticle.Body;

                connection.Disconnect();

                if (!articleHistory.ContainsKey(selectedArticle))
                {
                    articleHistory.Add(selectedArticle, article);
                }

                return true;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Download Article", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return false;
            }
        }

        private void addGroupFilters()
        {
            if (chkFilterGroups.Checked && cboGroupFilters.Text != "")
            {
                if (!cboGroupFilters.Items.Contains(cboGroupFilters.Text))
                {
                    cboGroupFilters.Items.Add(cboGroupFilters.Text);
                }
            }
        }

        private void populateGroupsList()
        {
            lstGroups.DataSource = groups;
        }

        private void populateArticleHeaders()
        {
            lstArticleHeaders.DataSource = articleHeaders;
        }

        private void populateArticle()
        {
            txtArticle.Text = article.ToString();
        }

        private void clearGroupsList()
        {
            lstGroups.DataSource = null;
            lstGroups.Refresh();
        }

        private void clearArticleHeaderList()
        {
            lstArticleHeaders.DataSource = null;
            lstArticleHeaders.Refresh();
        }

        private void clearArticle()
        {
            txtArticle.Clear();
            txtArticle.Refresh();
        }

        /// <summary>
        /// Makes sure that group elements are enabled or disabled depending
        /// on whether their checkboxes are on or off.
        /// </summary>
        private void CheckFilterGroups()
        {
            if (!chkFilterGroups.Checked)
            {
                radExclude.Enabled = false;
                radInclude.Enabled = false;
                lblGroupFilters.Enabled = false;
                cboGroupFilters.Enabled = false;
            }
            else
            {
                radExclude.Enabled = true;
                radInclude.Enabled = true;
                lblGroupFilters.Enabled = true;
                cboGroupFilters.Enabled = true;
            }

            if (!chkFilterArticles.Checked)
            {
                lblGetNumber.Enabled = false;
                lblGetNumber2.Enabled = false;
                txtGetNumber.Enabled = false;
            }
            else
            {
                lblGetNumber.Enabled = true;
                lblGetNumber2.Enabled = true;
                txtGetNumber.Enabled = true;
            }
        }
    }
}