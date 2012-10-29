-- Drop the stored procedure if it exists
IF OBJECT_ID ('spClearExpiredSessions') IS NOT NULL
	DROP PROCEDURE spClearExpiredSessions
GO

USE MLogger
GO

-- Clear expired sessions from the Session table
CREATE PROCEDURE spClearExpiredSessions AS
	DELETE FROM tblSessions WHERE expiration < GETDATE()
GO