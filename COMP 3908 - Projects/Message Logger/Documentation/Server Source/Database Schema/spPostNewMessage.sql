-- Drop the stored procedure if it exists
IF OBJECT_ID ('spPostNewMessage') IS NOT NULL
	DROP PROCEDURE spPostNewMessage
GO

USE MLogger
GO

-- Stored procedure for posting new message
-- Returns: messageID
CREATE PROCEDURE spPostNewMessage(@sessionID int, @title varchar(MAX), @message varchar(MAX)) AS
	DECLARE @count			INT
	DECLARE @maxMessageID	INT
	DECLARE @userID			INT

	SELECT @count = COUNT(*) FROM tblMessages
	
	-- Set the new message ID
	IF @count > 0
		SELECT @maxMessageID = MAX(messageID + 1) FROM tblMessages
	ELSE
		SET @maxMessageID = 0
		
	-- Retrieve the UserID associated with the current session
	SELECT @userID = userID FROM tblSessions WHERE sessionID = @sessionID
	
	INSERT INTO tblMessages(messageID, userID, postDate, title, [message]) VALUES(@maxMessageID, @userID, GETDATE(), @title, @message)
	
	RETURN @maxMessageID
GO