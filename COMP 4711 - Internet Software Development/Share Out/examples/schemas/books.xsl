<?xml version = "1.0"?>
<!-- books1.xsl      -->
<xsl:stylesheet version = "1.0" 
  xmlns:xsl = "http://www.w3.org/1999/XSL/Transform">
   <xsl:template match = "/">
      <html><body>
         <p>List of books with Japanese translations:</p>
         <ul>
            <xsl:for-each select = "books/book/translation">
               <xsl:if test = ". = 'Japanese'">
                  <li>
                     <strong><xsl:value-of select = "../title"/></strong>
                     - Edition:
                     <strong><xsl:value-of select = "@edition"/></strong>
                  </li>
               </xsl:if>
            </xsl:for-each>
         </ul>
      </body></html>
   </xsl:template>
</xsl:stylesheet>
