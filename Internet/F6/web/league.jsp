<%--
    Document   : league
    Created on : 2-Feb-2009, 3:06:16 AM
    Author     : Steffen L. Norgren
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page
    import="javax.xml.transform.*,
    javax.xml.transform.stream.*,
    java.io.*"
    %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title><%=application.getInitParameter("title")%> - League</title>
        <link rel="stylesheet" href="images/style.css" type="text/css" />
    </head>
    <body>
        <div id="page" align="center">
            <div id="content" style="width:800px">
                <jsp:include page="WEB-INF/jspf/header.jspf" />
                <div id="submenu">
                    <div align="right" class="smallgraytext" style="padding:9px;">
                    </div>
                </div>
                <div id="contenttext">
                    <%
                        String ls_xml = application.getRealPath("/WEB-INF/data/4711teams.xml");
                        String ls_xsl = application.getRealPath("/WEB-INF/data/teams.xsl");

                        StreamSource xml = new StreamSource(new File(ls_xml));
                        StreamSource xsl = new StreamSource(new File(ls_xsl));
                        StreamResult result = new StreamResult(out);

                        TransformerFactory tFactory = TransformerFactory.newInstance();
                        Transformer transformer = tFactory.newTransformer(xsl);
                        transformer.transform(xml, result);
                    %>
                </div>
                <div id="leftpanel">
                    <jsp:include page="WEB-INF/jspf/upcoming_games.jsp" />
                </div>
                <jsp:include page="WEB-INF/jspf/footer.jspf" />
            </div>
        </div>
    </body>
</html>
