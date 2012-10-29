using System;
using System.Collections.Generic;
using System.Text;

using System.IO;
using System.Xml;
using System.Data;
using System.Data.Common;
using System.Collections;
using System.Collections.Specialized;

namespace XMLdotNET.XMLDataReader
{
    // ******************************************************************
    // Custom XML reader class for data readers
    public class XmlDataReader : XmlReader
    {
        #region Constructor(s) and data members

        // ******************************************************************
        // Class constructor(s)
        public XmlDataReader(IDataReader dr)
        {
            InitializeClass(dr);
        }
        private void InitializeClass(IDataReader dr)
        {
            m_dataReader = dr;
            m_readState = ReadState.Initial;
            m_dataRecord = (IDataRecord)dr;
            m_currentAttributeIndex = -1;
        }
        // ******************************************************************


        // ******************************************************************
        // Data members
        protected IDataReader m_dataReader;
        protected ReadState m_readState;
        protected IDataRecord m_dataRecord;
        protected int m_currentAttributeIndex;
        // ******************************************************************

        #endregion


        #region Overridden Properties

        // ******************************************************************
        public override string Name
        {
            get
            {
                if (m_readState != ReadState.Interactive)
                    return null;

                string buf = "";
                switch (NodeType)
                {
                    case XmlNodeType.Attribute:
                        buf = m_dataRecord.GetName(m_currentAttributeIndex);
                        break;
                    case XmlNodeType.Element:
                        buf = "row";
                        break;
                }

                return buf;
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override string LocalName
        {
            get
            {
                return Name;
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override bool IsEmptyElement
        {
            get
            {
                return false;
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override XmlNodeType NodeType
        {
            get
            {
                if (m_currentAttributeIndex == -1)
                    return XmlNodeType.Element;
                else
                    return XmlNodeType.Attribute;
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override ReadState ReadState
        {
            get
            {
                return m_readState;
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override bool IsDefault
        {
            get
            {
                return false;
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override int AttributeCount
        {
            get
            {
                return m_dataRecord.FieldCount;
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override bool EOF
        {
            get
            {
                return (m_readState == ReadState.EndOfFile);
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override string this[int i]
        {
            get
            {
                return m_dataRecord.GetValue(i).ToString();
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override string this[string name]
        {
            get
            {
                return m_dataRecord[name].ToString();
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override int Depth
        {
            get
            {
                if (m_readState == ReadState.Interactive)
                    return 0;
                else
                    return -1;
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override bool HasValue
        {
            get
            {
                if (m_readState == ReadState.Interactive)
                    return true;
                else
                    return false;
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override string Value
        {
            get
            {
                if (m_readState != ReadState.Interactive)
                    return "";

                string buf = "";
                switch (NodeType)
                {
                    case XmlNodeType.Attribute:
                        buf = this[m_currentAttributeIndex].ToString();
                        break;
                }

                return buf;
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override string NamespaceURI
        {
            get
            {
                return "";
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override char QuoteChar
        {
            get
            {
                return '\"';
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override string XmlLang
        {
            get
            {
                return "";
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override XmlSpace XmlSpace
        {
            get
            {
                return System.Xml.XmlSpace.None;
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override string BaseURI
        {
            get
            {
                return "";
            }
        }
        // ******************************************************************


        // Not implemented 

        // ******************************************************************
        public override string Prefix
        {
            get
            {
                throw (new NotImplementedException());
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override string this[string name, string namespaceURI]
        {
            get
            {
                throw (new NotImplementedException());
            }
        }
        // ******************************************************************

        // ******************************************************************
        public override XmlNameTable NameTable
        {
            get
            {
                throw (new NotImplementedException());
            }
        }
        // ******************************************************************


        #endregion


        #region Overridden Methods

        // ******************************************************************
        // Read a new line from the CSV source file
        public override bool Read()
        {
            bool canReadMore = m_dataReader.Read();

            // read the new row
            if (canReadMore)
                m_readState = ReadState.Interactive;
            else
            {
                m_readState = ReadState.EndOfFile;
                return false;
            }


            // Exit
            return canReadMore;
        }
        // ******************************************************************

        // ******************************************************************
        // Close the underlying reader
        public override void Close()
        {
            m_dataReader.Close();
            m_readState = ReadState.Closed;
        }
        // ******************************************************************

        // ******************************************************************
        public override bool MoveToFirstAttribute()
        {
            m_currentAttributeIndex = 0;
            return true;
        }
        // ******************************************************************

        // ******************************************************************
        public override bool MoveToNextAttribute()
        {
            if (m_readState != ReadState.Interactive)
                return false;

            if (m_currentAttributeIndex < m_dataRecord.FieldCount - 1)
                m_currentAttributeIndex++;
            else
                return false;

            return true;
        }
        // ******************************************************************

        // ******************************************************************
        public override string GetAttribute(int i)
        {
            if (m_readState != ReadState.Interactive)
                return null;

            return m_dataRecord[i].ToString();
        }
        // ******************************************************************

        // ******************************************************************
        public override string GetAttribute(string name)
        {
            if (m_readState != ReadState.Interactive)
                return null;

            return m_dataRecord[name].ToString();
        }
        // ******************************************************************

        // ******************************************************************
        public override void MoveToAttribute(int i)
        {
            if (m_readState != ReadState.Interactive)
                return;

            m_currentAttributeIndex = i;
        }
        // ******************************************************************

        // ******************************************************************
        public override bool MoveToAttribute(string name)
        {
            if (m_readState != ReadState.Interactive)
                return false;

            for (int i = 0; i < AttributeCount; i++)
            {
                if (m_dataRecord.GetName(i) == name)
                {
                    m_currentAttributeIndex = i;
                    return true;
                }
            }
            return false;
        }
        // ******************************************************************

        // ******************************************************************
        public override bool MoveToElement()
        {
            if (m_readState != ReadState.Interactive)
                return false;

            m_currentAttributeIndex = -1;
            return true;
        }
        // ******************************************************************

        // ******************************************************************
        public override string ReadInnerXml()
        {
            if (m_readState != ReadState.Interactive)
                return null;

            return "";
        }
        // ******************************************************************

        // ******************************************************************
        public override string ReadOuterXml()
        {
            if (m_readState != ReadState.Interactive)
                return null;

            StringBuilder sb = new StringBuilder("");
            sb.Append("<row ");

            for (int i = 0; i < m_dataRecord.FieldCount; i++)
            {
                sb.Append(m_dataRecord.GetName(i));
                sb.Append("=");
                sb.Append(QuoteChar);
                sb.Append(m_dataRecord[i].ToString());
                sb.Append(QuoteChar);
                sb.Append(" ");
            }

            sb.Append("/>");
            return sb.ToString();
        }
        // ******************************************************************

        // ******************************************************************
        public override string ReadString()
        {
            if (m_readState != ReadState.Interactive)
                return null;

            return Value;
        }
        // ******************************************************************

        // Not implemented

        // ******************************************************************
        public override string GetAttribute(string name, string namespaceURI)
        {
            throw (new NotImplementedException());
        }
        // ******************************************************************

        // ******************************************************************
        public override string LookupNamespace(string prefix)
        {
            throw (new NotImplementedException());
        }
        // ******************************************************************

        // ******************************************************************
        public override bool MoveToAttribute(string name, string ns)
        {
            throw (new NotImplementedException());
        }
        // ******************************************************************

        // ******************************************************************
        public override bool ReadAttributeValue()
        {
            throw (new NotImplementedException());
        }
        // ******************************************************************

        // ******************************************************************
        public override void ResolveEntity()
        {
            throw (new NotImplementedException());
        }
        // ******************************************************************

        #endregion

    }
    // ******************************************************************
}
