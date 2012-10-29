-- Drop the stored procedure if it exists
IF OBJECT_ID ('spDeleteUser') IS NOT NULL
	DROP PROCEDURE spDeleteUser
GO

USE MLogger
GO

-- Stored procedure for user deletion
-- Returns: 1 if existed and deleted
--			0 if didn't exist
CREATE PROCEDURE spDeleteUser(@userID INT) AS
	IF EXISTS (SELECT * FROM tblUsers WHERE userID = @userID)
	BEGIN
		DELETE FROM tblUsers WHERE userID = @userID
		RETURN 1
	END
	ELSE
		RETURN 0
GO