<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:key name="countries" match="Country" use="@name" />

<xsl:template match="/">
  <html>
  <body>

		<!-- E X P O R T S -->
		<h2>Rice Production Exports</h2>
    <table border="1">
			<tr bgcolor="#9acd32">
				<th align="left">Country</th>
				<th align="left">2003</th>
				<th align="left">2004</th>
				<th align="left">2005</th>
				<th align="left">2006</th>
				<th align="left">2007</th>
			</tr>
			<xsl:for-each select="/WorldRiceTrade/Exports//Country[count(. | key('countries', @name)[1]) = 1]">
				<xsl:sort select="@name"/>
				<tr>
					<td>
						<xsl:variable name="thename" select="@name"/>
						<xsl:value-of select="$thename"/>
					</td>
					<xsl:for-each select="key('countries',$thename)">
						<td>
							<xsl:value-of select="Amount"/>
						</td>
					</xsl:for-each>
				</tr>
			</xsl:for-each>
			<tr>
				<td><b>Subtotals</b></td>
				<td><b><xsl:value-of 
					select="sum(//Exports/Year[@date='2003']//Amount)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//Exports/Year[@date='2004']//Amount)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//Exports/Year[@date='2005']//Amount)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//Exports/Year[@date='2006']//Amount)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//Exports/Year[@date='2007']//Amount)"/></b></td>
			</tr>
    </table>

			<!-- I M P O R T S -->
		<h2>Rice Production Imports</h2>
    <table border="1">
			<tr bgcolor="#9acd32">
				<th align="left">Country</th>
				<th align="left">2003</th>
				<th align="left">2004</th>
				<th align="left">2005</th>
				<th align="left">2006</th>
				<th align="left">2007</th>
			</tr>
			<xsl:for-each select="/WorldRiceTrade/Imports//Country[count(. | key('countries', @name)[1]) = 1]">
				<xsl:sort select="@name"/>
				<tr>
					<td>
						<xsl:variable name="thename" select="@name"/>
						<xsl:value-of select="$thename"/>
					</td>
					<xsl:for-each select="key('countries',$thename)">
						<td>
							<xsl:value-of select="Amount"/>
						</td>
					</xsl:for-each>
				</tr>
			</xsl:for-each>
			<tr>
				<td><b>Subtotals</b></td>
				<td><b><xsl:value-of 
					select="sum(//Imports/Year[@date='2003']//Amount)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//Imports/Year[@date='2004']//Amount)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//Imports/Year[@date='2005']//Amount)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//Imports/Year[@date='2006']//Amount)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//Imports/Year[@date='2007']//Amount)"/></b></td>
			</tr>
    </table>

		<!-- P I V O T -->
		<h2>Rice Production Countries</h2>
    <table border="1">
			<tr bgcolor="#9acd32">
				<th align="left">Year</th>
				<th align="left">Exporting Countries</th>
				<th align="left">Importing Countries</th>
			</tr>
			<tr>
				<td>2003</td>
				<td>
					<xsl:for-each select="//Exports/Year[@date='2003']">
						<xsl:for-each select="Country">
							<xsl:value-of select="@name"/>, 
						</xsl:for-each>
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//Imports/Year[@date='2003']">
						<xsl:for-each select="Country">
							<xsl:value-of select="@name"/>, 
						</xsl:for-each>
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2004</td>
				<td>
					<xsl:for-each select="//Exports/Year[@date='2004']">
						<xsl:for-each select="Country">
							<xsl:value-of select="@name"/>, 
						</xsl:for-each>
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//Imports/Year[@date='2004']">
						<xsl:for-each select="Country">
							<xsl:value-of select="@name"/>, 
						</xsl:for-each>
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2005</td>
				<td>
					<xsl:for-each select="//Exports/Year[@date='2005']">
						<xsl:for-each select="Country">
							<xsl:value-of select="@name"/>, 
						</xsl:for-each>
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//Imports/Year[@date='2005']">
						<xsl:for-each select="Country">
							<xsl:value-of select="@name"/>, 
						</xsl:for-each>
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2006</td>
				<td>
					<xsl:for-each select="//Exports/Year[@date='2006']">
						<xsl:for-each select="Country">
							<xsl:value-of select="@name"/>, 
						</xsl:for-each>
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//Imports/Year[@date='2006']">
						<xsl:for-each select="Country">
							<xsl:value-of select="@name"/>, 
						</xsl:for-each>
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2007</td>
				<td>
					<xsl:for-each select="//Exports/Year[@date='2007']">
						<xsl:for-each select="Country">
							<xsl:value-of select="@name"/>, 
						</xsl:for-each>
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//Imports/Year[@date='2007']">
						<xsl:for-each select="Country">
							<xsl:value-of select="@name"/>, 
						</xsl:for-each>
					</xsl:for-each>
				</td>
			</tr>
		</table>

	</body>
  </html>
</xsl:template>


</xsl:stylesheet>