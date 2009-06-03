<%--
    Document   : predict
    Created on : 2-Feb-2009, 3:06:16 AM
    Author     : Steffen L. Norgren
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title><%=application.getInitParameter("title")%> - Predict Outcomes</title>
        <link rel="stylesheet" href="images/style.css" type="text/css" />
    </head>
    <body>
        <div id="page" align="center">
            <div id="content" style="width:800px">
                <jsp:include page="WEB-INF/jspf/header.jspf" />
                <div id="submenu">
                    <div align="right" class="smallgraytext" style="padding:9px;">
                        <a href="?team=1">AC Horsens</a> |
                        <a href="?team=2">Odense BK</a>
                    </div>
                </div>
                <div id="contenttext">
                    <div style="padding:10px">
                    <span class="titletext">Predict Outcomes</span></div>
                    <div class="bodytext" style="padding:12px;" align="justify">
                        <strong>(content generated based on submenu selection)</strong>
                    </div>
                </div>
                <div id="leftpanel">
                    <jsp:include page="WEB-INF/jspf/upcoming_games.jsp" />
                </div>
                <jsp:include page="WEB-INF/jspf/footer.jspf" />
            </div>
        </div>
    </body>
</html>
