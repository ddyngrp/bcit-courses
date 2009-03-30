<%@page 
  import="javax.xml.transform.*,
          javax.xml.transform.stream.*,
          java.io.*"
%>


<%

String  ls_xml  = application.getRealPath("/WEB-INF/data/tvdata.xml");
String  ls_xsl  = application.getRealPath("/WEB-INF/data/tvdata.xsl");

StreamSource xml = new StreamSource(new File(ls_xml));
StreamSource xsl = new StreamSource(new File(ls_xsl));
StreamResult result = new StreamResult(out);

TransformerFactory tFactory = TransformerFactory.newInstance();
Transformer transformer = tFactory.newTransformer(xsl);
transformer.transform(xml, result);
%>
