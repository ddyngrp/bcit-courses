-- Drop the stored procedure if it exists
IF OBJECT_ID ('spPostMsgAttachment') IS NOT NULL
	DROP PROCEDURE spPostMsgAttachment
GO

USE MLogger
GO

-- Stored procedure for posting new message
CREATE PROCEDURE spPostMsgAttachment(@sessionID int, @messageID int, @mediaType varchar(50), @mediaLocation varchar(255)) AS
	DECLARE @count		INT
	DECLARE @maxMediaID	INT
	DECLARE @userID		INT

	SELECT @count = COUNT(*) FROM tblMedia
	
	-- Set the new message ID
	IF @count > 0
		SELECT @maxMediaID = MAX(mediaID + 1) FROM tblMedia
	ELSE
		SET @maxMediaID = 0


	INSERT INTO tblMedia(mediaID, messageID, mediaType, mediaLocation) VALUES(@maxMediaID, @messageID, @mediaType, @mediaLocation)
GO