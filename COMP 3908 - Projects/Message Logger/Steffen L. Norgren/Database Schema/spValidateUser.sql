-- Drop the stored procedure if it exists
IF OBJECT_ID ('spValidateUser') IS NOT NULL
	DROP PROCEDURE spValidateUser
GO

USE MLogger
GO

-- Stored procedure for user validation
-- Returns: 1 if valid
--			0 if invalid
CREATE PROCEDURE spValidateUser(@userName varchar(50), @password varchar(50)) AS
	IF EXISTS (SELECT * FROM tblUsers WHERE userName = @userName AND [password] = @password)
		RETURN 1
	ELSE
		RETURN 0
GO