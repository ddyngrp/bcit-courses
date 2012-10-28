<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : bbc3.xsl
    Created on : March 6, 2009, 2:21 PM
    Author     : A00696446
    Description:
        Purpose of transformation follows.
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="html"/>

    <!-- TODO customize transformation rules 
         syntax recommendation http://www.w3.org/TR/xslt 
    -->
    <xsl:template match="/">
        <html>
            <head>
                <title>bbc3.xsl</title>
            </head>
            <body>
                <xsl:variable name="total" select="count(channel/programme)"/>
                <xsl:variable name="number" select="count(channel/programme[contains(title, 'Doctor Who')])"/>
                <table border="1">
                    <tr>
                        <th>Title</th>
                        <th>Start</th>
                        <th>Runtime</th>
                        <th>Description</th>
                    </tr>
                    
                    <xsl:for-each select="channel/programme[contains(title, 'Doctor Who')]">
                        <xsl:variable name="start" select="start"/>
                        <xsl:variable name="end" select="end"/>
                        <xsl:variable name="runtime" select="$end - $start"/>
                        <tr>
                           <td><xsl:value-of select="title"/></td>
                           <td><xsl:value-of select="start"/></td>
                           <td><xsl:value-of select="$runtime"/></td>
                           <td><xsl:value-of select="desc"/></td>
                        </tr>
                    </xsl:for-each>
                    
                </table>
                <p>
                    Displaying <xsl:value-of select="$number"/> out of <xsl:value-of select="$total"/> shows.
                </p>
            </body>
        </html>
    </xsl:template>

</xsl:stylesheet>
