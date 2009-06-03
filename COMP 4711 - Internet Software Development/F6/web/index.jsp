<%-- 
    Document   : index
    Created on : 2-Feb-2009, 3:06:16 AM
    Author     : Steffen L. Norgren
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title><%=application.getInitParameter("title")%> - Home</title>
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
                    <div style="padding:10px">
                    <span class="titletext">by Steffen L. Norgren</span></div>
                    <div class="bodytext" style="padding:12px;" align="justify">
                        <strong>Following Teams:</strong><br />
                        <table width="100%">
                            <tr>
                                <td>
                                    <h1 style="margin-bottom: 10px;">
                                    Odense BK</h1>
                                    <p>
                                        Founded: 1889<br />
                                        Colors: Blue / White<br />
                                        Stadium: Odense Stadion<br />
                                        Website: <a href="http://www.ob.dk">http://www.ob.dk</a></p>
                                    <p><a href="roster.jsp?team=1" class="smallredtext">Team Roster</a></p>
                                </td>
                                <td>
                                    <h1 style="margin-bottom: 10px;">
                                    AC Horsens</h1>
                                    <p>
                                        Founded: 1994<br />
                                        Colors: Yellow / Black<br />
                                        Stadium: Horsens Indrætspark<br />
                                        Website: <a href="http://www.achorsens.dk">http://www.achorsens.dk</a></p>
                                        <p><a href="roster.jsp?team=2" class="smallredtext">Team Roster</a></p>
                                </td>
                            </tr>
                        </table>
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
