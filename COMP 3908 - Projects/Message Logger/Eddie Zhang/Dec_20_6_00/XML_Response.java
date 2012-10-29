/*
 * XML_Response.java
 *
 * MLogger, 2008
 * Confidential and proprietary.
 */
 package src;
 public interface XML_Response {

    public static final int PARSING_ERROR = -2;
    public static final int SERVER_ERROR = -1;
    public static final int INVALID_AUTHORIZATION = 0;
    public static final int SUCCESS = 1;

    // Note all implementations SHOULD have a _(String data) constructur
    
    public boolean success();
    
    public int status();

}
