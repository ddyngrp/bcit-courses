<%@ page
  import="javax.xml.transform.*,
          javax.xml.transform.stream.*,
          java.io.*"
%>

<%
String  ls_path = request.getServletPath();
        ls_path = ls_path.substring(0,ls_path.lastIndexOf("/")) ;

String  ls_xml  = application.getRealPath(ls_path + "/cdcatalog.xml");
String  ls_xsl  = application.getRealPath(ls_path + "/cdcatalog6.xsl");

StreamSource xml = new StreamSource(new File(ls_xml));
StreamSource xsl = new StreamSource(new File(ls_xsl));
StreamResult result = new StreamResult(out);

TransformerFactory tFactory = TransformerFactory.newInstance();
Transformer transformer = tFactory.newTransformer(xsl);
transformer.transform(xml, result);
%>
