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
CREATE TABLE tblExample (
	a_key		INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
	a_Number	INT,
	a_String	varchar(30))

/* Create an auditing table for the database */
CREATE TABLE Audit (
	AuditID	INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
	Type 		CHAR(6),		-- the type of change: Update, Insert, Delete
	PK			VARCHAR(1000),	-- the primary key on the changed table
	TableName	VARCHAR(128),	-- the table where the change occurred
	FieldName	VARCHAR(128),	-- the field name where data changed
	OldValue	VARCHAR(30),	-- the old value in the field
	NewValue 	VARCHAR(30),	-- the updated value in the field
	UpdateDate	datetime DEFAULT(GetDate()), -- defaults to today's date
	UserName	VARCHAR(128))	-- the user who made the change
GO

/* Create the trigger itself. You need to create a trigger for every
   table that you want to monitor. */
CREATE TRIGGER trigTest ON tblExample FOR INSERT, UPDATE, DELETE
AS

/* Setting variables that store all the event information */
DECLARE @bit INT, @field INT, @maxfield INT, @char INT,
		@fieldname VARCHAR(128), @tableName VARCHAR(128),
		@PKCols VARCHAR(1000), @sql VARCHAR(2000),
		@UpdateDate VARCHAR(21), @UserName VARCHAR(128),
		@Type CHAR(6), @PKSelect VARCHAR(1000)

/* Change the tableName to the name of the table you are auditing */
SELECT @TableName = 'tblExample'

/* Set the date and the user */
SELECT @UserName = SYSTEM_USER

/* Set the type of action that occurred */
IF EXISTS (SELECT * FROM inserted)		-- checks for entries in inserted
	IF EXISTS (SELECT * FROM deleted)	-- checks for entries in deleted
		SELECT @Type = 'UPDATE'			-- if entry in inserted & deleted
	ELSE
		SELECT @Type = 'INSERT'			-- if entry only in inserted
ELSE
	SELECT @Type = 'DELETE'				-- if not in inserted & deleted

/* Store inserted & deleted data in temp tables */
SELECT * INTO #ins FROM inserted
SELECT * INTO #del FROM deleted

/* Get primary key columns for full outer join */
SELECT @PKCols = COALESCE(@PKCols + ' and', ' on') 
	 + ' i.' + c.COLUMN_NAME + ' = d.' + c.COLUMN_NAME
FROM	INFORMATION_SCHEMA.TABLE_CONSTRAINTS pk,
		INFORMATION_SCHEMA.KEY_COLUMN_USAGE c
WHERE	pk.TABLE_NAME = @tableName
	AND	CONSTRAINT_TYPE = 'PRIMARY KEY'
	AND	c.TABLE_NAME = pk.TABLE_NAME
	AND	c.CONSTRAINT_NAME = pk.CONSTRAINT_NAME

/* Get primary key select for insert */
SELECT @PKSelect = COALESCE(@PKSelect+'+','') 
	 	+ '''<' + COLUMN_NAME + '=''+convert(varchar(100),
	 	coalesce(i.' + COLUMN_NAME +',d.' + COLUMN_NAME + '))+''>'''
FROM	INFORMATION_SCHEMA.TABLE_CONSTRAINTS pk ,
		INFORMATION_SCHEMA.KEY_COLUMN_USAGE c
WHERE	pk.TABLE_NAME = @tableName
	AND	CONSTRAINT_TYPE = 'PRIMARY KEY'
	AND	c.TABLE_NAME = pk.TABLE_NAME
	AND	c.CONSTRAINT_NAME = pk.CONSTRAINT_NAME

SELECT @field = 0, @maxfield = MAX(ORDINAL_POSITION) 
FROM	INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = @tableName
WHILE @field < @maxfield
BEGIN
	SELECT @field = MIN(ORDINAL_POSITION) 
	FROM	INFORMATION_SCHEMA.COLUMNS 
	WHERE	TABLE_NAME = @tableName 
		AND	ORDINAL_POSITION > @field
	SELECT @bit = (@field - 1 )% 8 + 1
	SELECT @bit = POWER(2,@bit - 1)
	SELECT @char = ((@field - 1) / 8) + 1

	IF SUBSTRING(COLUMNS_UPDATED(),@char, 1) & @bit > 0
	   OR @Type IN ('INSERT','DELETE')
	BEGIN
		SELECT @fieldname = COLUMN_NAME 
		FROM INFORMATION_SCHEMA.COLUMNS 
		WHERE TABLE_NAME = @tableName
		AND	ORDINAL_POSITION = @field
		/* This is generates a dynamic SQL query from all our variables,
		   allowing us to add multiple entries into the Audit table
		   within a single trigger */
		SELECT @sql = ' INSERT Audit (Type, TableName, PK, FieldName,
			OldValue, NewValue, UserName)
			SELECT ''' + @Type + ''',''' + @tableName + ''','
			+ @PKSelect + ',''' + @fieldname + ''''
			+ ',CONVERT(VARCHAR(1000),d.' + @fieldname + ')'
			+ ',CONVERT(VARCHAR(1000),i.' + @fieldname + ')' + ','''
			+ @UserName + ''''
			+ ' FROM #ins i FULL OUTER JOIN #del d' + @PKCols
			+ ' WHERE i.' + @fieldname + ' <> d.' + @fieldname 
			+ ' OR (i.' + @fieldname + ' IS NULL AND  d.' + @fieldname
			+ ' IS NOT NULL)' + ' OR (i.' + @fieldname
			+ ' IS NOT NULL AND  d.' + @fieldname + ' IS NULL)' 
		EXEC (@sql) -- Executes the dynamic SQL query.
	END
END
GO

/* Now we can test the above using some simple queries */
USE auditing

INSERT INTO tblExample (a_Number, a_String) values(100,'first entry')
INSERT INTO tblExample (a_Number, a_String) values(101,'second entry')

UPDATE tblExample
	SET a_String = 'replaced first entry', a_Number = '99'
	WHERE a_number = '100'

DELETE FROM tblExample WHERE a_Number = '101'

SELECT * FROM Audit
