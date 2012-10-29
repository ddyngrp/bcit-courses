-- Drop the stored procedure if it exists
IF OBJECT_ID ('spNewSessionID') IS NOT NULL
	DROP PROCEDURE spNewSessionID
GO

USE MLogger
GO

-- Creates a new session ID and stores it in the Session table
-- Returns: Session ID
CREATE PROCEDURE spNewSessionID(@userName varchar(50)) AS
	DECLARE @sessionID	INT
	DECLARE @userID		INT
	
	-- Grab the user's ID
	SELECT @userID = userID FROM tblUsers WHERE userName = @userName
	
	-- Set the new session ID
	SELECT @sessionID = ABS(CAST(CAST(NEWID() AS VARBINARY) AS INT));
	
	-- Clear all previous sessions for the user
	DELETE FROM tblSessions WHERE userID = @userID
	
	-- Insert the new userID/session ID pair into the table with a 2-hour expiration
	INSERT INTO tblSessions(userID, sessionID, expiration) VALUES(@userID, @sessionID, DATEADD(hh, 2, GETDATE()))
	
	-- Returns the session ID
	RETURN @sessionID
GO