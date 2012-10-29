-- Drop the stored procedure if it exists
IF OBJECT_ID ('spCreateUser') IS NOT NULL
	DROP PROCEDURE spCreateUser
GO

USE MLogger
GO

-- Stored procedure for creating a new user
-- Returns: 1 if created
--			0 if user name existed and not created
CREATE PROCEDURE spCreateUser(@userName varchar(50), @password varchar(50)) AS
	DECLARE @count		INT
	DECLARE @maxUserID	INT

	SELECT @count = COUNT(*) FROM tblUsers
	
	IF @count > 0
		SELECT @maxUserID = MAX(userID + 1) FROM tblUsers
	ELSE
		SET @maxUserID = 0
		
	IF NOT EXISTS (SELECT * FROM tblUsers WHERE userName = @userName)
	BEGIN
		INSERT INTO tblUsers(userID, userName, [password]) VALUES(@maxUserID, @userName, @password)
		RETURN 1
	END
	ELSE
		RETURN 0
GO