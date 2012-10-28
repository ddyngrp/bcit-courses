/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package server;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class VotingServlet extends HttpServlet {

    private ServletContext context;

    @Override
    public void init(ServletConfig config) throws ServletException {
        this.context = config.getServletContext();
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        SurveyHandler handler = SurveyHandler.instance();

        int vote = Integer.parseInt(request.getParameter("vote"));

        handler.vote(vote);
        
        response.getWriter().write(handler.report());
    }
}