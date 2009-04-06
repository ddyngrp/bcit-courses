<%@page
    import="server.*"
    %>
<%-- 
    Document   : index
    Created on : 6-Apr-2009, 2:38:08 AM
    Author     : ironix
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<%
        SurveyHandler handler = SurveyHandler.instance();

        String survey[] = handler.survey();
%>

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Lab #11</title>
        <script type="text/javascript" src="./dojo.js"
                djConfig="parseOnLoad: true">
                    
            dojo.require("dijit.form.Button");
        </script>
        <script type='text/javascript'>
            function submitVote() {
                dojo.xhrPost({
                    // Page to that parses the POST request
                    url: 'VotingServlet',
                    // Name of the form we want to submit
                    form: voteForm,
                    // Load this funtion on success
                    load: function(data) {
                        // Put the data into the appropriate <div>
                        dojo.byId('results').innerHTML = data
                            + '<br />' + "<a href=\".\" style=\"padding-left:22px;\">Go Back</a>";
                    },
                    // Load this function on failure
                    error: function(error) {
                        console.error('Error: ', error);
                    }
                });
            }
        </script>
    </head>
    <body>
        <div id="response"></div>
        <form name="voteForm" method="POST">
            <div id="results">
                <%
                for (int i = 0; i < survey.length; i++) {
                    if (i == 0) {
                        out.print("<b>" + survey[i] + "</b><br />");
                    } else {
                        out.println("<input type=\"radio\" name=\"vote\" value=\""
                                + i + "\" /> " + survey[i] + "<br />");
                    }
                }
                %>
                <br />
                <a href="#" onClick="submitVote();" style="padding-left:22px;">Submit Vote</a>
            </div>
            <br />
        </form>
    </body>
</html>
