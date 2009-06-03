<%-- 
    Document   : order
    Created on : 25-Jan-2009, 9:13:29 PM
    Author     : Steffen L. Norgren
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<%
        String orderNum = request.getParameter("orderNum");
        String name = request.getParameter("name");
        String cookie = request.getParameter("cookie");
        String size = request.getParameter("size");

        String sprinkles = request.getParameter("sprinkles");
        String napkins = request.getParameter("napkins");
        String icecream = request.getParameter("icecream");
        String liverpate = request.getParameter("liverpate");

        if (name == null) {
            name = "name not entered";
        }

        if (sprinkles == null) {
            sprinkles = "";
        }
        else {
            sprinkles = "Sprinkles ";
        }
        if (napkins == null) {
            napkins = "";
        }
        else {
            napkins = "Napkins ";
        }
        if (icecream == null) {
            icecream = "";
        }
        else {
            icecream = "Ice Cream ";
        }
        if (liverpate == null) {
            liverpate = "";
        }
        else {
            liverpate = "Liver Paté ";
        }

        String options = sprinkles + napkins + icecream + liverpate;
%>

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title><%=application.getInitParameter("orderTitle")%></title>
    </head>
    <body>
        <h1><%=application.getInitParameter("orderTitle")%></h1>

        <table width="0" border="0">
            <tr>
                <td>Order #:</td>
                <td>&nbsp;<%=orderNum%></td>
            </tr>
            <tr>
                <td>Customer Name:</td>
                <td>&nbsp;<%=name%></td>
            </tr>
            <tr>
                <td>Cookie:</td>
                <td>&nbsp;<%=cookie%></td>
            </tr>
            <tr>
                <td>Size:</td>
                <td>&nbsp;<%=size%></td>
            </tr>
            <tr>
                <td>Options:</td>
                <td>&nbsp;<%=options%></td>
            </tr>

        </table>
        <p><a href ="index.jsp">Home</a></p>
    </body>
</html>
