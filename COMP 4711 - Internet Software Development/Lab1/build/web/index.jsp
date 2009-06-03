<%-- 
    Document   : index
    Created on : 18-Jan-2009, 8:16:54 PM
    Author     : Steffen L. Norgren
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<%
    String includePage;

    if (request.getParameter("page").equals("home")) {
        includePage = "includes/home.html";
    }
    else if (request.getParameter("page").equals("about_us")) {
        includePage = "includes/about_us.html";
    }
    else if (request.getParameter("page").equals("products")) {
        includePage = "includes/products.html";
    }
    else if (request.getParameter("page").equals("services")) {
        includePage = "includes/services.html";
    }
    else if (request.getParameter("page").equals("contact")) {
        includePage = "includes/contact.html";
    }
    else { // Default configuration
        includePage = "includes/home.html";
    }
%>

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" href="images/style.css" type="text/css" />
        <title>COMP 4711 - Lab #1</title>
    </head>
    <body>
        <div id="page" align="center">
            <div id="content" style="width:800px">
                <div id="logo">
                    <div style="margin-top:70px" class="whitetitle">Lab #1</div>
                </div>
                <div id="topheader">
                    <div align="left" class="bodytext">
                        <br />
                        <strong>Esurient Systems Inc.</strong><br />
                        13872 Malabar Ave.<br />
                        White Rock, B.C.<br />
                        Phone: 604-536-6621<br />
                        ironix@trollop.org
                    </div>
                </div>
                <div id="menu">
                    <div align="right" class="smallwhitetext" style="padding:9px;">
                        <a href="?page=home">Home</a> | <a href="?page=about_us">About Us</a> | <a href="?page=products">Products</a> | <a href="?page=services">Our Services</a> | <a href="?page=contact">Contact Us</a>
                    </div>
                </div>
                <div id="submenu">
                    <div align="right" class="smallgraytext" style="padding:9px;">
                    </div>
                </div>
                <div id="contenttext">
                    <!-- Change the content based on what page we're on -->
                    <jsp:include page="<%=includePage%>" flush="true"/>
                </div>
                <div id="leftpanel">
                    <div align="justify" class="graypanel">
                        <span class="smalltitle">News</span><br /><br />
                        <span class="smallredtext">September 27, 2006</span><br />
                        <span class="bodytext">Curabitur arcu tellus, suscipit in, aliquam eget, ultricies id, sapien. Nam est.</span><br />
                        <a href="#" class="smallgraytext">More...</a><br /><br />
                        <span class="smallredtext">September 27, 2006</span><br />
                        <span class="bodytext">Curabitur arcu tellus, suscipit in, aliquam eget, ultricies id, sapien. Nam est.</span><br />
                        <a href="#" class="smallgraytext">More...</a><br /><br />
                        <span class="smallredtext">September 27, 2006</span><br />
                        <span class="bodytext">Curabitur arcu tellus, suscipit in, aliquam eget, ultricies id, sapien. Nam est.</span><br />
                        <a href="#" class="smallgraytext">More...</a><br /><br />
                    </div>
                </div>
                <div id="footer" class="smallgraytext">
                    <a href="#">Home</a> | <a href="#">About Us</a> | <a href="#">Products</a> | <a href="#">Our Services</a> | <a href="#">Contact Us</a>
                    | Your Company Name
                    &copy; 2007 | <a href="http://www.winkhosting.com" target="_blank">Hosting Colombia</a>
                </div>
            </div>
        </div>
    </body>
</html>
