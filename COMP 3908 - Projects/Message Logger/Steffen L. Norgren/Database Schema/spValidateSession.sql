-- Drop the stored procedure if it exists
IF OBJECT_ID ('spValidateSession') IS NOT NULL
	DROP PROCEDURE spValidateSession
GO

USE MLogger
GO

-- Stored procedure to check if the session ID is valid
-- Returns: 1 if valid
--			0 if invalid
CREATE PROCEDURE spValidateSession(@sessionID int) AS
	IF EXISTS (SELECT * FROM tblSessions WHERE sessionID = @sessionID AND expiration >= GETDATE())
		RETURN 1
	ELSE
		RETURN 0
GO