<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : tvdata.xsl
    Created on : March 1, 2009, 11:47 PM
    Author     : Steffen L. Norgren
    Description:
        Stylesheet for TVData.xml
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="html"/>
    <xsl:template match="/">
        <html>
            <head>
                <title>TV Guide Listings</title>
            </head>
            <body>
                <font face="helvetica, verdana, arial">
                    <h2>TV Guide Listings</h2>
                    <xsl:apply-templates/>
                </font>
            </body>
        </html>
    </xsl:template>
    
    <xsl:template match="/tv">
        <table border="0" cellspacing="10" width="100%">
            <tr>
                <th>Title</th>
                <th>Time</th>
                <th>Description</th>
                <th>Categories</th>
            </tr>
            <xsl:apply-templates select="programme"/>
        </table>
    </xsl:template>

    <xsl:template match="programme">
        <tr>
            <td width="15%">
                <xsl:for-each select="title">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </td>
            <td width="10%">
                <xsl:value-of select="@start"/>
            </td>
            <td width="60%">
                <xsl:for-each select="desc">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </td>
            <td width="15%">
                <xsl:for-each select="category">
                    <xsl:value-of select="."/>
                    <xsl:text disable-output-escaping="yes">,&amp;nbsp;</xsl:text>
                </xsl:for-each>
            </td>
        </tr>
    </xsl:template>

</xsl:stylesheet>