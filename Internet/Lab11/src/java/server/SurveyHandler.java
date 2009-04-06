package server;

public class SurveyHandler implements SurveyServer {

    static private SurveyHandler _instance = null;

    static String[] stuff = {"Which is your favorite movie/franchise of all time?",
        "Bladerunner", "Rambo", "Serenity", "Star Trek", "Star Wars"};
    static int[] votes = new int[stuff.length];

    /**
     * Creates an instance of the class only if one does not
     * yet exist.
     * @return current instance
     */
    static public SurveyHandler instance() {
        if (null == _instance) {
            _instance = new SurveyHandler();
        }
        return _instance;
    }

    /** Return a survey questionaire, with the question
    as the first array element and the possible
    responses as subsequent elements (numbered 1-?) */
    public String[] survey() {
        return stuff;
    }

    /** Process a response, returning the most commonly
    chosen one so far. */
    public int vote(int item) {
        if ((item < 1) || (item > stuff.length)) {
            return 0;
        }
        votes[0]++;
        votes[item]++;
        System.out.println("Got a vote for #" + item);
        int max = 1;
        for (int i = 1; i < votes.length; i++) {
            if (votes[i] > votes[max]) {
                max = i;
            }
        }
        return max;
    }

    /** Produce a “report”, showing the survey results
    as a text message, with embedded newlines for
    formatting. */
    public String report() {
        StringBuilder sb = new StringBuilder();
        sb.append("<b>" + stuff[0] + "</b><br />");
        for (int i=1; i<votes.length; i++)
            sb.append("<div style='padding-left:22px;'>" + stuff[i] + " [" + votes[i] + "]</div>");
        return sb.toString();
    }
}
