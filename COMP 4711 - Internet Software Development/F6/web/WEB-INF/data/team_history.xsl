<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : team_history.xsl
    Created on : April 1, 2009, 1:24 AM
    Author     : ironix
    Description:
        Purpose of transformation follows.
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="html"/>

    <!-- TODO customize transformation rules
         syntax recommendation http://www.w3.org/TR/xslt
    -->
    <xsl:template match="/">

        <div style="padding:10px">
            <span class="titletext">
                <xsl:value-of select="/schedule/@team"/> History
            </span>
        </div>

        <div class="bodytext" style="padding:12px;" align="justify">
            <xsl:apply-templates select="/schedule"/>
        </div>

    </xsl:template>

    <xsl:template match="/schedule">
        <table border="0" cellspacing="10" width="100%">
            <tr>
                <th>Date</th>
                <th>Status</th>
                <th>Home</th>
                <th>Score</th>
                <th>Away</th>
            </tr>
            <xsl:apply-templates select="game[(
                        not(((number(substring(@date, 6, 2)) >= 3)
                        and (number(substring(@date, 9, 2)) >= 18)
                        and (number(substring(@date, 1, 4)) >= 2009)
                        ))
                        and not ((number(substring(@date, 6, 2)) >= 4)
                        and (number(substring(@date, 1, 4)) >= 2009)
                        ))]"/>
        </table>
    </xsl:template>

    <xsl:template match="schedule/game">
        <tr>
            <td>
                <xsl:for-each select="@date">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </td>
            <td>
                <xsl:for-each select="status">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </td>
            <td>
                <xsl:for-each select="home">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </td>
            <td>
                <xsl:for-each select="score">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </td>
            <td>
                <xsl:for-each select="away">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </td>
        </tr>
    </xsl:template>
</xsl:stylesheet>
