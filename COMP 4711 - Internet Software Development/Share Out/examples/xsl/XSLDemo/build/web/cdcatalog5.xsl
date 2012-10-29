<?xml version="1.0" encoding="ISO-8859-1"?>
<!-- Edited with XML Spy v2006 (http://www.altova.com) -->
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method='html' version='1.0' encoding='UTF-8' indent='yes'/>

<xsl:template match="/">
  <html>
  <body>
  <h2>My CD Collection</h2>
    <table border="1">
      <tr bgcolor="#9acd32">
        <th align="left">Title</th>
        <th align="left">Artist</th>
      </tr>
      <xsl:for-each select="catalog/cd">
      <tr>
        <td><xsl:value-of select="title"/></td>
        <xsl:choose> 
          <xsl:when test="price &gt; 10"> 
            <td bgcolor="#ff0000"> 
            <xsl:value-of select="artist"/></td> 
          </xsl:when> 
          <xsl:when test="price &gt; 8"> 
            <td bgcolor="#0000ff"> 
            <xsl:value-of select="artist"/></td> 
          </xsl:when> 
          <xsl:otherwise> 
            <td><xsl:value-of select="artist"/></td> 
          </xsl:otherwise> 
        </xsl:choose> 
      </tr>
      </xsl:for-each>
    </table>
  </body>
  </html>
</xsl:template>
</xsl:stylesheet>