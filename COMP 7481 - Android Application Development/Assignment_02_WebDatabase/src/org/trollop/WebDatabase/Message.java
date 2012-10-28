package org.trollop.WebDatabase;

import java.io.Serializable;

public class Message implements Serializable {
	private static final long serialVersionUID = 7526472295622776147L;

	public String message = "";
	public int messageID = 0;
	
	public String getMessage() {
        return message;
    }
    public void setMessage(String name) {
        this.message = name;
    }
    public int getMessageID() {
        return messageID;
    }
    public void setMessageID(Integer eventID) {
        this.messageID = eventID;
    }
}
