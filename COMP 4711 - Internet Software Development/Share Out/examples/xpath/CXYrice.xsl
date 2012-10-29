<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xx="http://exslt.org/common" 
	extension-element-prefixes="xx">


<xsl:template match="/">
  <html>
  <body>
    <h1>Rice Production</h1>
    <h2>Exports</h2>

		<!-- E X P O R T S -->
    <table border="1">
			<tr bgcolor="#9acd32">
				<th align="left">Country</th>
				<th align="left">2003</th>
				<th align="left">2004</th>
				<th align="left">2005</th>
				<th align="left">2006</th>
				<th align="left">2007</th>
			</tr>
			<xsl:for-each select="/rice_trade_statistics/country_info[export_statistics]">
				<xsl:sort select="@name"/>
				<tr>
					<td><xsl:value-of select="@name"/></td>
					<td><xsl:value-of select="export_statistics[@year='2003']"/></td>
					<td><xsl:value-of select="export_statistics[@year='2004']"/></td>
					<td><xsl:value-of select="export_statistics[@year='2005']"/></td>
					<td><xsl:value-of select="export_statistics[@year='2006']"/></td>
					<td><xsl:value-of select="export_statistics[@year='2007']"/></td>
				</tr>
			</xsl:for-each>
			<tr>
				<td><b>Subtotals</b></td>
				<td><b><xsl:value-of 
					select="sum(/rice_trade_statistics/country_info[export_statistics]//export_statistics[@year='2003'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(/rice_trade_statistics/country_info[export_statistics]//export_statistics[@year='2004'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(/rice_trade_statistics/country_info[export_statistics]//export_statistics[@year='2005'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(/rice_trade_statistics/country_info[export_statistics]//export_statistics[@year='2006'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(/rice_trade_statistics/country_info[export_statistics]//export_statistics[@year='2007'])"/></b></td>
			</tr>
    </table>
    
		<!-- I M P O R T S -->
    <h2>Imports</h2>
    <table border="1">
			<tr bgcolor="#9acd32">
				<th align="left">Country</th>
				<th align="left">2003</th>
				<th align="left">2004</th>
				<th align="left">2005</th>
				<th align="left">2006</th>
				<th align="left">2007</th>
			</tr>
			<xsl:for-each select="/rice_trade_statistics/country_info[import_statistics]">
				<xsl:sort select="@name"/>
				<tr>
					<td><xsl:value-of select="@name"/></td>
					<td><xsl:value-of select="import_statistics[@year='2003']"/></td>
					<td><xsl:value-of select="import_statistics[@year='2004']"/></td>
					<td><xsl:value-of select="import_statistics[@year='2005']"/></td>
					<td><xsl:value-of select="import_statistics[@year='2006']"/></td>
					<td><xsl:value-of select="import_statistics[@year='2007']"/></td>
				</tr>
			</xsl:for-each>
			<tr>
				<td><b>Subtotals</b></td>
				<td><b><xsl:value-of 
					select="sum(/rice_trade_statistics/country_info[import_statistics]//import_statistics[@year='2003'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(/rice_trade_statistics/country_info[import_statistics]//import_statistics[@year='2004'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(/rice_trade_statistics/country_info[import_statistics]//import_statistics[@year='2005'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(/rice_trade_statistics/country_info[import_statistics]//import_statistics[@year='2006'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(/rice_trade_statistics/country_info[import_statistics]//import_statistics[@year='2007'])"/></b></td>
			</tr>
    </table>

		<!-- P I V O T -->
		<h2>Pivot List of Countries</h2>
		<table border="1">
			<tr bgcolor="#9acd32">
				<th align="left">Year</th>
				<th align="left">Exporting Countries</th>
				<th align="left">Importing Countries</th>
			</tr>
			<tr>
				<td>2003</td>
				<td>
					<xsl:for-each select="//country_info/export_statistics[@year='2003']">
						<xsl:value-of select="../@name"/>, 
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//country_info/import_statistics[@year='2003']">
						<xsl:value-of select="../@name"/>, 
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2004</td>
				<td>
					<xsl:for-each select="//country_info/export_statistics[@year='2004']">
						<xsl:value-of select="../@name"/>, 
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//country_info/import_statistics[@year='2004']">
						<xsl:value-of select="../@name"/>, 
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2005</td>
				<td>
					<xsl:for-each select="//country_info/export_statistics[@year='2005']">
						<xsl:value-of select="../@name"/>, 
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//country_info/import_statistics[@year='2005']">
						<xsl:value-of select="../@name"/>, 
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2006</td>
				<td>
					<xsl:for-each select="//country_info/export_statistics[@year='2006']">
						<xsl:value-of select="../@name"/>, 
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//country_info/import_statistics[@year='2006']">
						<xsl:value-of select="../@name"/>, 
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2007</td>
				<td>
					<xsl:for-each select="//country_info/export_statistics[@year='2007']">
						<xsl:value-of select="../@name"/>, 
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//country_info/import_statistics[@year='2007']">
						<xsl:value-of select="../@name"/>, 
					</xsl:for-each>
				</td>
			</tr>
	</table>
    
  </body>
  </html>
</xsl:template>


</xsl:stylesheet>