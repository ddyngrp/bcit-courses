/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package server;

public interface SurveyServer {

    /** Return a survey questionaire, with the question
    as the first array element and the possible
    responses as subsequent elements (numbered 1-?) */
    public String[] survey();

    /** Process a response, returning the most commonly
    chosen one so far. */
    public int vote(int item);

    /** Produce a “report”, showing the survey results
    as a text message, with embedded newlines for
    formatting. */
    public String report();
}