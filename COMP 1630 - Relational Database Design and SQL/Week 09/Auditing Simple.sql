/* Checking to see if database exists, if so, drop it and recreate */
USE master
IF EXISTS (SELECT * FROM sysdatabases WHERE name = 'auditing')
BEGIN
	raiserror('Dropping existing auditing database ....',0,1)
	DROP database auditing
END
CHECKPOINT -- Checkpoint basically writes all changes in memory to the disk
GO

/* Create a database we can use for our auditing tests */
raiserror('Creating auditing  database....',0,1)
CREATE DATABASE auditing
CHECKPOINT
GO

USE auditing

/* Create the table we wish to audit */
CREATE TABLE Employee (
	EmployeeID	INT IDENTITY(1,1) PRIMARY KEY CLUSTERED, 
	FullName	VARCHAR(50) NOT NULL, 
	Salary		INT			NOT NULL 
)

/* Create an auditing table for the table we're auditing */
CREATE TABLE AuditEmployee (
	AuditID	INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
	Type 		CHAR(6),		-- the type of change
	EmployeeID	INT,			-- the primary key
	oldFullName	VARCHAR(50),	-- original full name
	newFullName	VARCHAR(50),	-- new full name
	oldSalary	INT,			-- original salary
	newSalary	INT,			-- new salary
	UpdateDate	datetime DEFAULT(GetDate()), -- defaults to today's date
	UserName	VARCHAR(128)	-- the user who made the change
)
GO

/* Create the trigger itself. */
CREATE TRIGGER trAudit_Employee ON Employee FOR INSERT, UPDATE, DELETE
AS

/* Setting variables that store all the event information */
DECLARE	@UserName		VARCHAR(128),
		@Type			CHAR(6)

/* Set the date and the user */
SELECT @UserName = SYSTEM_USER

/* Set the type of action that occurred and store the changes */
IF EXISTS (SELECT * FROM inserted)		-- checks for entries in inserted
	IF EXISTS (SELECT * FROM deleted)	-- checks for entries in deleted
	  BEGIN
		SELECT @Type = 'UPDATE'			-- if entry in inserted & deleted
		INSERT INTO AuditEmployee (Type, EmployeeID, oldFullName, newFullName,
					oldSalary, newSalary, UserName)
		SELECT @Type, inserted.EmployeeID, deleted.FullName, inserted.FullName,
			   deleted.Salary, inserted.Salary, @UserName
		FROM inserted, deleted
		WHERE inserted.EmployeeID = deleted.EmployeeID
	  END
	ELSE
	  BEGIN
		SELECT @Type = 'INSERT'			-- if entry only in inserted
		INSERT INTO AuditEmployee (Type, EmployeeID, newFullName,
					newSalary, UserName)
		SELECT @Type, inserted.EmployeeID, inserted.FullName,
			   inserted.Salary, @UserName
		FROM inserted
	  END
ELSE
  BEGIN
	SELECT @Type = 'DELETE'				-- if not in inserted & deleted
	INSERT INTO AuditEmployee (Type, EmployeeID, oldFullName,
				oldSalary, UserName)
	SELECT @Type, deleted.EmployeeID, deleted.FullName,
		   deleted.Salary, @UserName
	FROM deleted
  END
GO

/* Now we can test the above using some simple queries */
USE auditing

INSERT INTO Employee(FullName, Salary) 
    VALUES('Aaron Bertrand', 10000);
 
INSERT INTO Employee(FullName, Salary) 
    VALUES('Joe Schmoe', 15000);
 
UPDATE Employee SET salary = 30000 
    WHERE EmployeeID = 1;
 
/* handles multiple rows as well! 
   let's give everyone a raise to demonstrate */
 
UPDATE Employee SET Salary = Salary + 2000;
 
DELETE Employee WHERE EmployeeID = 2;

SELECT * FROM AuditEmployee;

USE master