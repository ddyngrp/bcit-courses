<%-- 
    Document   : index
    Created on : 25-Jan-2009, 7:27:51 PM
    Author     : Steffen L. Norgren
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@page import="model.Model.Order" %>

<%
    Order order = new Order();
    int orderNum = order.getOrderNum();
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title><%=application.getInitParameter("title")%></title>
    </head>
    <body>
        <h1><%=application.getInitParameter("title")%></h1>

        <form id="ordering" name="ordering" method="post" action="order.jsp">
            <input type="hidden" name="orderNum" value="<%=orderNum%>">
            <table width="0" border="0">
                <tr>
                    <td>Order #:&nbsp;</td>
                    <td>&nbsp;<%=orderNum%></td>
                </tr>
                <tr>
                    <td>Customer Name:&nbsp;</td>
                    <td>&nbsp;<input name="name" type="text" /></td>
                </tr>
                <tr>
                    <td>Cookie:&nbsp;</td>
                    <td>&nbsp;
                        <%
                        String[] cookies = order.getCookies();

                        out.println("<select name=\"cookie\" id=\"cookie\">");

                        for (int i = 0; i < cookies.length; i++) {
                            out.println("<option value=\"" + cookies[i] +
                                        "\">" + cookies[i] + "</option>");
                        }

                        out.println("</select>");
                        %>
                    </td>
                </tr>
                <tr>
                    <td>Size:&nbsp;</td>
                    <td>
                        &nbsp;Small&nbsp;<input name="size" type="radio" value="small" />
                        &nbsp;Medium&nbsp;<input name="size" type="radio" value="medium" checked="checked" />
                        &nbsp;Large&nbsp;<input name="size" type="radio" value="large" />
                    </td>
                </tr>
                <tr>
                    <td>Options:&nbsp;</td>
                    <td>
                    	&nbsp;Sprinkles&nbsp;<input name="sprinkles" type="checkbox" value="sprinkles" />
                        &nbsp;Napkins&nbsp;<input name="napkins" type="checkbox" value="napkins" />
                        &nbsp;Ice Cream&nbsp;<input name="icecream" type="checkbox" value="icecream" />
                        &nbsp;Liver Paté&nbsp;<input name="liverpate" type="checkbox" value="liverpate" />
                    </td>
                <tr>
                    <td>Proceed&nbsp;</td>
                    <td>&nbsp;<input name="submit" type="submit" /></td>
                </tr>
            </table>
        </form>
    </body>
</html>
