<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : tvdata.xsl
    Created on : February 27, 2009, 1:54 PM
    Author     : A00702683
    Description:
        Purpose of transformation follows.
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" version="1.0">
    <xsl:output method="html"/>

    <!-- TODO customize transformation rules 
         syntax recommendation http://www.w3.org/TR/xslt 
    -->
    <xsl:template match="/">
        <html>
            <head>
                <title>TV Guide Listings</title>
            </head>
            
            <body>
                <h2>TV Guide Listings: News</h2>
                <table border="1">
                    <tr bgcolor="#9acd32">
                        <th align="left">Title</th>
                        <th align="left">Time</th>
                        <th align="left">Description</th>
                        <th align="left">Categories</th>
                    </tr>
                    <xsl:apply-templates select="tv/programme" />
                </table>
                
                <xsl:variable name="has-match">
                    <xsl:for-each select="tv/programme">
                        <xsl:if test="category[contains(text(), 'News')]">
                            <value>
                                1
                            </value>
                        </xsl:if>
                    </xsl:for-each>
                </xsl:variable>
                
                <table border="1">
                    <tr bgcolor="#9acd32">
                        <th align="left">Total</th>
                        <th align="left">Selected</th>
                    </tr>
                    <tr>
                        <td>
                            <xsl:value-of select="count(tv/programme)" />
                        </td>
                        <td>
                            <xsl:value-of select="sum(exsl:node-set($has-match)/value)" />
                        </td>
                    </tr>
                </table>

            </body>
        </html>
    </xsl:template>

    
    
    <xsl:template match="programme">
        <xsl:if test="category[contains(text(), 'News')]">
            <tr>
                <td>
                    <xsl:value-of select="title"/>
                </td>
                <td>
                    <xsl:value-of select="substring(@start, 9, 2)"/>
                    <text>:</text>
                    <xsl:value-of select="substring(@start, 11, 2)"/>
                    <text> - </text>
                    <xsl:value-of select="substring(@stop, 9, 2)"/>
                    <text>:</text>
                    <xsl:value-of select="substring(@stop, 11, 2)"/>     
                </td>
                <td>
                    <xsl:choose>
                        <xsl:when test="not(desc)">
                            <text>None Given</text>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:value-of select="desc"/>
                        </xsl:otherwise>
                    </xsl:choose>
                </td>
                <td>
                    <xsl:for-each select="category">
                        <xsl:value-of select="." />
                        <text>, </text>
                    </xsl:for-each>
                </td>
            </tr>
        </xsl:if>
    </xsl:template>

</xsl:stylesheet>
