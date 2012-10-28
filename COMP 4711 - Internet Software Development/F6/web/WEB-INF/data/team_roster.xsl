<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : team_roster.xsl
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
                <xsl:value-of select="/team/@name"/> Roster
            </span>
        </div>

        <div class="bodytext" style="padding:12px;" align="justify">
            <xsl:apply-templates/>
        </div>

    </xsl:template>

    <xsl:template match="/team">
        <table border="0" cellspacing="10" width="100%">
            <tr>
                <th>Jersey</th>
                <th>Name</th>
                <th>Position</th>
                <th>Birthdate</th>
            </tr>
            <xsl:apply-templates select="player"/>
        </table>
    </xsl:template>

    <xsl:template match="player">
        <tr>
            <td>
                <xsl:for-each select="@jersey">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </td>
            <td>
                <xsl:for-each select="name">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </td>
            <td>
                <xsl:for-each select="position">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </td>
            <td>
                <xsl:for-each select="birthdate">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </td>
        </tr>
    </xsl:template>
</xsl:stylesheet>
