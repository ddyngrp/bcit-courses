<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:key name="countries" match="country" use="@name" />

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
			<xsl:for-each select="//country[not(@exports='0')]">
				<xsl:sort select="@name"/>
				<xsl:if test="count(. | key('countries', @name)[1]) = 1">
					<tr>
						<td><xsl:value-of select="@name"/></td>
							<xsl:variable name="me" select="@name"/>
							<td><xsl:value-of select="sum(//year[@number='2003']//country[@name=$me]//@exports)"/></td>
							<td><xsl:value-of select="sum(//year[@number='2004']//country[@name=$me]//@exports)"/></td>
							<td><xsl:value-of select="sum(//year[@number='2005']//country[@name=$me]//@exports)"/></td>
							<td><xsl:value-of select="sum(//year[@number='2006']//country[@name=$me]//@exports)"/></td>
							<td><xsl:value-of select="sum(//year[@number='2007']//country[@name=$me]//@exports)"/></td>
						</tr>
				</xsl:if>
			</xsl:for-each>
			<tr>
				<td><b>Subtotals</b></td>
				<td><b><xsl:value-of 
					select="sum(//year[@number='2003']//country//@exports)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//year[@number='2004']//country//@exports)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//year[@number='2005']//country//@exports)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//year[@number='2006']//country//@exports)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//year[@number='2007']//country//@exports)"/></b></td>
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
			<xsl:for-each select="//country[not(@imports='0')]">
				<xsl:sort select="@name"/>
				<xsl:if test="count(. | key('countries', @name)[1]) = 1">
					<tr>
						<td><xsl:value-of select="@name"/></td>
							<xsl:variable name="me" select="@name"/>
							<td><xsl:value-of select="sum(//year[@number='2003']//country[@name=$me]//@imports)"/></td>
							<td><xsl:value-of select="sum(//year[@number='2004']//country[@name=$me]//@imports)"/></td>
							<td><xsl:value-of select="sum(//year[@number='2005']//country[@name=$me]//@imports)"/></td>
							<td><xsl:value-of select="sum(//year[@number='2006']//country[@name=$me]//@imports)"/></td>
							<td><xsl:value-of select="sum(//year[@number='2007']//country[@name=$me]//@imports)"/></td>
						</tr>
				</xsl:if>
			</xsl:for-each>
			<tr>
				<td><b>Subtotals</b></td>
				<td><b><xsl:value-of 
					select="sum(//year[@number='2003']//country//@imports)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//year[@number='2004']//country//@imports)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//year[@number='2005']//country//@imports)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//year[@number='2006']//country//@imports)"/></b></td>
				<td><b><xsl:value-of 
					select="sum(//year[@number='2007']//country//@imports)"/></b></td>
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
					<xsl:for-each select="//year[@number='2003']//country">
							<xsl:if test="not(@imports='0')">
								<xsl:value-of select="@name"/>, 
							</xsl:if>
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//year[@number='2003']//country">
							<xsl:if test="not(@exports='0')">
								<xsl:value-of select="@name"/>, 
							</xsl:if>
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2004</td>
				<td>
					<xsl:for-each select="//year[@number='2004']//country">
							<xsl:if test="not(@imports='0')">
								<xsl:value-of select="@name"/>, 
							</xsl:if>
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//year[@number='2004']//country">
							<xsl:if test="not(@exports='0')">
								<xsl:value-of select="@name"/>, 
							</xsl:if>
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2005</td>
				<td>
					<xsl:for-each select="//year[@number='2005']//country">
							<xsl:if test="not(@imports='0')">
								<xsl:value-of select="@name"/>, 
							</xsl:if>
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//year[@number='2005']//country">
							<xsl:if test="not(@exports='0')">
								<xsl:value-of select="@name"/>, 
							</xsl:if>
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2006</td>
				<td>
					<xsl:for-each select="//year[@number='2006']//country">
							<xsl:if test="not(@imports='0')">
								<xsl:value-of select="@name"/>, 
							</xsl:if>
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//year[@number='2006']//country">
							<xsl:if test="not(@exports='0')">
								<xsl:value-of select="@name"/>, 
							</xsl:if>
					</xsl:for-each>
				</td>
			</tr>
			<tr>
				<td>2007</td>
				<td>
					<xsl:for-each select="//year[@number='2007']//country">
							<xsl:if test="not(@imports='0')">
								<xsl:value-of select="@name"/>, 
							</xsl:if>
					</xsl:for-each>
				</td>
				<td>
					<xsl:for-each select="//year[@number='2007']//country">
							<xsl:if test="not(@exports='0')">
								<xsl:value-of select="@name"/>, 
							</xsl:if>
					</xsl:for-each>
				</td>
			</tr>
		</table>

  </body>
  </html>
</xsl:template>


</xsl:stylesheet>