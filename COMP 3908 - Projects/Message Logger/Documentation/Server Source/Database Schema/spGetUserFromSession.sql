-- Drop the stored procedure if it exists
IF OBJECT_ID ('spGetUserFromSession') IS NOT NULL
	DROP PROCEDURE spGetUserFromSession
GO

USE MLogger
GO

-- Stored procedure for posting new message
-- Returns: userName
CREATE PROCEDURE spGetUserFromSession(@sessionID int) AS
	DECLARE @userID		INT
	DECLARE @userName	VARCHAR(50)
	
	-- Retrieve the UserID associated with the current session
	SELECT @userID = userID FROM tblSessions WHERE sessionID = @sessionID

	-- Retrieve the User Name associated with the UserID
	SELECT @userName = userName FROM tblUsers WHERE userID = @userID
	
	SELECT @userName AS 'UserName'
GO