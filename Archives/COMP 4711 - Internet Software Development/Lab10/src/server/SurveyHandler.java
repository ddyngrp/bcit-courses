package server;

/**
 *
 * @author Steffen L. Norgren
 */
public class SurveyHandler implements SurveyServer {

    /**
     * Return a survey questionaire, with the question
     * as the first array element and the possible
     * responses as subsequent elements (numbered 1-?)
     */
    public String[] survey() {
        return survey;
    }

    /**
     * Process a response, returning the most commonly
     * chosen one so far.
     */
    public int vote(int item) {
        int maxVotes = 1;

        System.out.println("Vote registered for: " + survey[0]);
        System.out.println("\tUser voted: " + survey[item]);
        vote[0]++; // Increment the total votes for the question
        vote[item]++; // Increment the votes for the question

        // Return the item with the most votes
        for (int i = 1; i < vote.length; i++) {
            if (vote[i] > vote[maxVotes]) {
                maxVotes = i;
            }
        }

        return maxVotes;
    }

    /**
     * Produce a “report”, showing the survey results
     * as a text message, with embedded newlines for
     * formatting.
     */
    public String report() {
        String report = "Survey Report:\n\n";
        // Set the question title
        report += survey[0] + "\n";

        for (int i = 1; i < survey.length; i++) {
            report += "\t" + i + ". " + survey[i] + "\n";
            report += "\t   votes = " + vote[i] + "\n";
        }

        return report;
    }
}
