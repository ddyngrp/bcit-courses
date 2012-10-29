<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
  <html>
  <body>
    <h1>Rice Production</h1>

		<!-- E X P O R T -->
		<h2>Exports</h2>
    <table border="1">
			<tr bgcolor="#9acd32">
				<th align="left">Country</th>
				<th align="left">2003</th>
				<th align="left">2004</th>
				<th align="left">2005</th>
				<th align="left">2006</th>
				<th align="left">2007</th>
			</tr>
			<xsl:for-each select="/rice/exports/country">
				<xsl:sort select="@country_id"/>
				<tr>
					<td><xsl:value-of select="@country_id"/></td>
					<td><xsl:value-of select="year[@year_id='2003']"/></td>
					<td><xsl:value-of select="year[@year_id='2004']"/></td>
					<td><xsl:value-of select="year[@year_id='2005']/weight"/></td>
					<td><xsl:value-of select="year[@year_id='2006']/weight"/></td>
					<td><xsl:value-of select="year[@year_id='2007']/weight"/></td>
				</tr>
			</xsl:for-each>
			<tr>
				<td><b>Subtotals</b></td>
				<td><b><xsl:value-of 
					select="sum(//exports/country/year[@year_id='2003'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//exports/country/year[@year_id='2004'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//exports/country/year[@year_id='2005'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//exports/country/year[@year_id='2006'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//exports/country/year[@year_id='2007'])"/></b></td>
			</tr>
    </table>

		<!-- I M P O R T -->
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
			<xsl:for-each select="/rice/imports/country">
				<xsl:sort select="@country_id"/>
				<tr>
					<td><xsl:value-of select="@country_id"/></td>
					<td><xsl:value-of select="year[@year_id='2003']"/></td>
					<td><xsl:value-of select="year[@year_id='2004']"/></td>
					<td><xsl:value-of select="year[@year_id='2005']/weight"/></td>
					<td><xsl:value-of select="year[@year_id='2006']/weight"/></td>
					<td><xsl:value-of select="year[@year_id='2007']/weight"/></td>
				</tr>
			</xsl:for-each>
			<tr>
				<td><b>Subtotals</b></td>
				<td><b><xsl:value-of 
					select="sum(//imports/country/year[@year_id='2003'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//imports/country/year[@year_id='2004'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//imports/country/year[@year_id='2005'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//imports/country/year[@year_id='2006'])"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//imports/country/year[@year_id='2007'])"/></b></td>
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
					<xsl:for-each select="//exports/country/year[@year_id='2003']">
						<xsl:value-of select="../@country_id"/>, 
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//imports/country/year[@year_id='2003']">
						<xsl:value-of select="../@country_id"/>, 
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2004</td>
				<td>
					<xsl:for-each select="//exports/country/year[@year_id='2004']">
						<xsl:value-of select="../@country_id"/>, 
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//imports/country/year[@year_id='2004']">
						<xsl:value-of select="../@country_id"/>, 
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2005</td>
				<td>
					<xsl:for-each select="//exports/country/year[@year_id='2005']">
						<xsl:value-of select="../@country_id"/>, 
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//imports/country/year[@year_id='2005']">
						<xsl:value-of select="../@country_id"/>, 
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2006</td>
				<td>
					<xsl:for-each select="//exports/country/year[@year_id='2006']">
						<xsl:value-of select="../@country_id"/>, 
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//imports/country/year[@year_id='2006']">
						<xsl:value-of select="../@country_id"/>, 
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2007</td>
				<td>
					<xsl:for-each select="//exports/country/year[@year_id='2007']">
						<xsl:value-of select="../@country_id"/>, 
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//imports/country/year[@year_id='2007']">
						<xsl:value-of select="../@country_id"/>, 
					</xsl:for-each>
				</td>
			</tr>
	</table>
    

  </body>
  </html>
</xsl:template>


</xsl:stylesheet>