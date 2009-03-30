<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : bbc3.xsl
    Created on : March 15, 2009, 10:54 PM
    Author     : A00702683
    Description:
        Purpose of transformation follows.
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"  xmlns:exsl="http://exslt.org/common" version="1.0">
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
                <h2>TV Guide Listings: Doctor Who</h2>
                <table border="1">
                    <tr bgcolor="#9acd32">
                        <th align="left">Title</th>
                        <th align="left">Time</th>
                        <th align="left">Description</th>
                    </tr>
                    <xsl:apply-templates select="channel/programme" />
                </table>
                
                <xsl:variable name="amount-matched">
                    <xsl:for-each select="channel/programme">
                        <xsl:if test="title[contains(text(), 'Doctor Who')]">
                            <value>
                                <xsl:choose>
                                    <xsl:when test="end &gt; start">
                                        <value>
                                            <xsl:value-of select="substring(end, 3, 2) - substring(start, 3, 2) + (substring(end, 1, 2) - substring(start, 1, 2)) * 60" />
                                        </value>
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <value>
                                            <xsl:value-of select="substring(end, 3, 2) - substring(start, 3, 2) + (substring(end, 1, 2) - substring(start, 1, 2) + 24) * 60" />
                                        </value>
                                    </xsl:otherwise>
                                </xsl:choose>
                            </value>
                        </xsl:if>
                    </xsl:for-each>
                </xsl:variable>
                
                <xsl:variable name="amount-total">
                    <xsl:for-each select="channel/programme">
                        <value>
                            <xsl:choose>
                                <xsl:when test="end &gt; start">
                                    <value>
                                        <xsl:value-of select="substring(end, 3, 2) - substring(start, 3, 2) + (substring(end, 1, 2) - substring(start, 1, 2)) * 60" />
                                    </value>
                                </xsl:when>
                                <xsl:otherwise>
                                    <value>
                                        <xsl:value-of select="substring(end, 3, 2) - substring(start, 3, 2) + (substring(end, 1, 2) - substring(start, 1, 2) + 24) * 60" />
                                    </value>
                                </xsl:otherwise>
                            </xsl:choose>
                        </value>
                    </xsl:for-each>
                </xsl:variable>
                
                <table border="1">
                    <tr bgcolor="#9acd32">
                        <th align="left">Total Airtime</th>
                        <th align="left">Selected Airtime</th>
                    </tr>
                    <tr>
                        <td>
                            <xsl:value-of select="sum(exsl:node-set($amount-total)/value)" /><text> min</text>

                        </td>
                        <td>
                            <xsl:value-of select="sum(exsl:node-set($amount-matched)/value)" /><text> min</text>
                        </td>
                    </tr>
                </table>

            </body>
        </html>
    </xsl:template>

    
    
    <xsl:template match="programme">
        <xsl:if test="title[contains(text(), 'Doctor Who')]">
            <tr>
                <td>
                    <xsl:value-of select="title"/>
                </td>
                <td>
                    <xsl:value-of select="substring(start, 1, 2)"/>
                    <text>:</text>
                    <xsl:value-of select="substring(start, 3, 2)"/>
                    <text> - </text>
                    <xsl:value-of select="substring(end, 1, 2)"/>
                    <text>:</text>
                    <xsl:value-of select="substring(end, 3, 2)"/>     
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
            </tr>
        </xsl:if>
    </xsl:template>

</xsl:stylesheet>
