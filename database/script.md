### Add in data base the following tables:

1. EventLogType

`CREATE TABLE [dbo].[EventLogType] (
    [Id]   UNIQUEIDENTIFIER DEFAULT (newid()) NOT NULL,
    [name] NVARCHAR (100)   NOT NULL,
    PRIMARY KEY CLUSTERED ([Id] ASC)
);`

* EventLogSource   

`CREATE TABLE [dbo].[EventLogSource] (
    [Id]   UNIQUEIDENTIFIER DEFAULT (newid()) NOT NULL,
    [name] NVARCHAR (250)   NOT NULL,
    PRIMARY KEY CLUSTERED ([Id] ASC)
);`

* EventLogMessage

`CREATE TABLE [dbo].[EventLogMessage] (
    [Id]      UNIQUEIDENTIFIER DEFAULT (newid()) NOT NULL,
    [message] NVARCHAR (MAX)   NOT NULL,
    PRIMARY KEY CLUSTERED ([Id] ASC)
);`

* EventLogMachine

`CREATE TABLE [dbo].[EventLogMachine] (
    [Id]   UNIQUEIDENTIFIER DEFAULT (newid()) NOT NULL,
    [name] NVARCHAR (250)   NOT NULL,
    PRIMARY KEY CLUSTERED ([Id] ASC)
);`

* EventLogJournal

`CREATE TABLE [dbo].[EventLogJournal] (
    [Id]   UNIQUEIDENTIFIER DEFAULT (newid()) NOT NULL,
    [name] NVARCHAR (100)   NOT NULL,
    PRIMARY KEY CLUSTERED ([Id] ASC)
);`

* EventLog

`CREATE TABLE [dbo].[EventLog] (
    [Id]                   UNIQUEIDENTIFIER DEFAULT (newid()) NOT NULL,
    [event_log_type_id]    UNIQUEIDENTIFIER NOT NULL,
    [event_log_source_id]  UNIQUEIDENTIFIER NOT NULL,
    [event_log_machine_id] UNIQUEIDENTIFIER NOT NULL,
    [event_log_journal_id] UNIQUEIDENTIFIER NOT NULL,
    [event_log_message_id] UNIQUEIDENTIFIER NOT NULL,
    [time_generated]       DATETIME         NOT NULL,
    [time_written]         DATETIME         NOT NULL,
    [record_number]        NVARCHAR (50)    NOT NULL,
    [event_id]             NVARCHAR (50)    NOT NULL,
    [event_category]       NVARCHAR (20)    NOT NULL,
    PRIMARY KEY CLUSTERED ([Id] ASC),
    CONSTRAINT [FK_EventLog_ToEventLogMessage] FOREIGN KEY ([event_log_message_id]) REFERENCES [dbo].[EventLogMessage] ([Id]),
    CONSTRAINT [FK_EventLog_ToEventLogJournal] FOREIGN KEY ([event_log_journal_id]) REFERENCES [dbo].[EventLogJournal] ([Id]),
    CONSTRAINT [FK_EventLog_ToEventLogMachine] FOREIGN KEY ([event_log_machine_id]) REFERENCES [dbo].[EventLogMachine] ([Id]),
    CONSTRAINT [FK_EventLog_ToEventLogSource] FOREIGN KEY ([event_log_source_id]) REFERENCES [dbo].[EventLogSource] ([Id]),
    CONSTRAINT [FK_EventLog_ToEventLogType] FOREIGN KEY ([event_log_type_id]) REFERENCES [dbo].[EventLogType] ([Id])
);`

* getMessageId( ADO Adapter form nvarchar(max) )

`CREATE PROCEDURE [dbo].[getMessageId]
	@RC nvarchar(36) = null OUTPUT,
	@message nvarchar(max) = null
AS
BEGIN
	SET NOCOUNT ON;
	BEGIN TRY
		SET @RC = ( SELECT TOP(1) [Id] FROM [dbo].[EventLogMessage] WHERE [message] = @message );
	END TRY
	BEGIN CATCH
		DECLARE @ErrorMessage nvarchar(4000);  
		DECLARE @ErrorSeverity int;
		SELECT @ErrorMessage = ERROR_MESSAGE(), @ErrorSeverity = ERROR_SEVERITY();
		RAISERROR(@ErrorMessage, @ErrorSeverity, 1);
	END CATCH;
END`
