<?xml version="1.0"?>
<xsl:stylesheet version="1.0" 
        xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/">
<HTML>
  <HEAD>
    <TITLE>First Performance Stylesheet</TITLE>
  </HEAD>
  <BODY>
  <xsl:for-each select="SHOWS/PERFORMANCE">
    <FONT color="red">
    <B><xsl:value-of select="TITLE" /></B> - 
    <I><xsl:value-of select="AUTHOR" /></I>&#160;
    </FONT>
    <xsl:value-of select="DATE" />&#160;
    <xsl:value-of select="DESCRIPTION" />
    <BR/>
  </xsl:for-each>
  </BODY>
</HTML>
</xsl:template>
</xsl:stylesheet> 
