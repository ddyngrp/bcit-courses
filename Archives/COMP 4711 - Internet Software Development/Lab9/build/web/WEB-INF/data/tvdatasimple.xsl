<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : tvdata.xsl
    Created on : February 27, 2009, 2:01 PM
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

                <h1>TV Listings</h1>
                <xsl:variable name="total" select="count(tv/programme)"/>
                <xsl:variable name="number" select="count(tv/programme[((number(substring(@start, 9, 2)) >= 8)
                        and not (number(substring(@start, 9, 2)) > 11))
                        or ((number(substring(@stop, 9, 2)) >= 8)
                        and not (number(substring(@stop, 9, 2)) > 11))])"/>
                <table border="1">
                    <tr>
                        <th>Title</th>
                        <th>Channel</th>
                        <th>Time</th>
                        <th>Description</th>
                        <th>Categories</th>
                    </tr>
                    <xsl:apply-templates select="tv/programme[((number(substring(@start, 9, 2)) >= 8)
                        and not (number(substring(@start, 9, 2)) > 11))
                        or ((number(substring(@stop, 9, 2)) >= 8)
                        and not (number(substring(@stop, 9, 2)) > 11))]"/>
                </table>
                <p>
                    Displaying <xsl:value-of select="$number"/> out of <xsl:value-of select="$total"/> shows.
                </p>

    </xsl:template>

    <xsl:template match="programme">
        <tr>
            <td>
                <xsl:value-of select="title"/>
            </td>
            <td>
                <xsl:value-of select="@channel"/>
            </td>
            <td>
                <xsl:value-of select="@start"/> to
                <xsl:value-of select="@stop"/>
            </td>
            <td>
                <xsl:value-of select="desc"/>
            </td>
            <td>
                <xsl:apply-templates select="category"/>
            </td>
        </tr>
    </xsl:template>
    
    <xsl:template match="category">
        <xsl:value-of select="."/>,
    </xsl:template>
</xsl:stylesheet>
