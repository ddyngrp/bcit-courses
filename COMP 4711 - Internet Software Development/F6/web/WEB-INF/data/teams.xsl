<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : teams.xsl
    Created on : March 31, 2009, 11:02 PM
    Author     : Steffen L. Norgren
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
            <span class="titletext">League Members</span>
        </div>

        <div class="bodytext" style="padding:12px;" align="justify">
            <ul style="margin-lef:20px;">
                <xsl:apply-templates/>
            </ul>
        </div>

    </xsl:template>

    <xsl:template match="team">
        <li>
            <a href="/{@id}" class="smallredtext">
                <xsl:for-each select="league">
                    <xsl:value-of select="."/>
                </xsl:for-each>
            </a>
            <xsl:for-each select="members">
                <xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text>
                (<xsl:value-of select="."/>)
            </xsl:for-each>
        </li><br/>
    </xsl:template>
</xsl:stylesheet>
