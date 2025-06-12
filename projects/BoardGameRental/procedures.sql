

USE BoardGameRental;
GO

-- PROCEDURS
CREATE PROCEDURE RentGame
    @UserID INT,
    @GameID INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        BEGIN TRANSACTION;

        -- Check whether user exists
        IF NOT EXISTS (SELECT 1 FROM Users WHERE UserID = @UserID)
        BEGIN
            RAISERROR('User does not exist.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Check whether the game exists and is available
        DECLARE @AvailableCopies INT;

        SELECT @AvailableCopies = AvailableCopies
        FROM Games
        WHERE GameID = @GameID;

        IF @AvailableCopies IS NULL
        BEGIN
            RAISERROR('Game does not exist.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        IF @AvailableCopies <= 0
        BEGIN
            RAISERROR('No available copies of this game.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Add rental for 7 days
        DECLARE @Today DATE = GETDATE();
        DECLARE @Due DATE = DATEADD(DAY, 7, @Today);

        INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate)
        VALUES (@UserID, @GameID, @Today, @Due);

        -- Get ID of the newly inserted rental
        DECLARE @RentalID INT = SCOPE_IDENTITY();

        -- Insert log entry
        INSERT INTO RentalLogs (RentalID, Operation)
        VALUES (@RentalID, 'RENT');

        -- Decrease available copies
        UPDATE Games
        SET AvailableCopies = AvailableCopies - 1
        WHERE GameID = @GameID;

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;

        DECLARE @ErrorMessage NVARCHAR(4000) = ERROR_MESSAGE();
        RAISERROR(@ErrorMessage, 16, 1);
    END CATCH
END;


-- USAGE EXAMPLE:
EXEC RentGame @UserID = 6, @GameID = 21;

-- check whether it is created
SELECT 
    Rentals.RentalDate, Rentals.GameID, Games.Title
FROM Rentals
LEFT JOIN Games ON Rentals.GameID = Games.GameID
WHERE Rentals.UserID = 6;

--------------
GO
CREATE PROCEDURE ReturnGame
    @RentalID INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        BEGIN TRANSACTION;

        -- - Check if the rental exists
        IF NOT EXISTS (SELECT 1 FROM Rentals WHERE RentalID = @RentalID)
        BEGIN
            RAISERROR('Rental does not exist.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Check if the rental has already been returned
        IF EXISTS (
            SELECT 1 FROM Rentals
            WHERE RentalID = @RentalID AND ReturnDate IS NOT NULL
        )
        BEGIN
            RAISERROR('Game has already been returned.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        --  Get GameID from the rental
        DECLARE @GameID INT;

        SELECT @GameID = GameID
        FROM Rentals
        WHERE RentalID = @RentalID;

        --Set today's date as ReturnDate
        UPDATE Rentals
        SET ReturnDate = GETDATE()
        WHERE RentalID = @RentalID;

        --  Increase available copies
        UPDATE Games
        SET AvailableCopies = AvailableCopies + 1
        WHERE GameID = @GameID;

        -- Insert entry into RentalLogs
        INSERT INTO RentalLogs (RentalID, Operation)
        VALUES (@RentalID, 'RETURN');

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;

        DECLARE @ErrorMessage NVARCHAR(4000) = ERROR_MESSAGE();
        RAISERROR(@ErrorMessage, 16, 1);
    END CATCH
END;

-- USAGE

EXEC ReturnGame @RentalID = 2;

SELECT 
    Rentals.RentalID, Rentals.GameID, Rentals.UserID, Games.Title, Rentals.ReturnDate
FROM Rentals
LEFT JOIN Games ON Rentals.GameID=Games.GameID
WHERE  Rentals.GameID = 7;
-----------------------------
GO
CREATE PROCEDURE ExtendRental
    @RentalID INT,
    @ExtraDays INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        BEGIN TRANSACTION;

        --  Check if rental exists and hasn't been returned yet
        IF NOT EXISTS (
            SELECT 1 FROM Rentals
            WHERE RentalID = @RentalID AND ReturnDate IS NULL
        )
        BEGIN
            RAISERROR('Rental does not exist or has already been returned.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Check if it was already extended (i.e. there's a log entry with 'EXTEND')
        IF EXISTS (
            SELECT 1 FROM RentalLogs
            WHERE RentalID = @RentalID AND Operation LIKE 'EXTEND %'
        )
        BEGIN
            RAISERROR('This rental has already been extended once.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Extend the due date by the given number of days
        UPDATE Rentals
        SET DueDate = DATEADD(DAY, @ExtraDays, DueDate)
        WHERE RentalID = @RentalID;

        --  Insert a log entry
        DECLARE @LogText NVARCHAR(50) = CONCAT('EXTEND +', @ExtraDays);

        INSERT INTO RentalLogs (RentalID, Operation)
        VALUES (@RentalID, @LogText);

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;

        DECLARE @ErrorMessage NVARCHAR(4000) = ERROR_MESSAGE();
        RAISERROR(@ErrorMessage, 16, 1);
    END CATCH
END;

-- USAGE
EXEC ExtendRental @RentalID = 13, @ExtraDays = 5;

SELECT * FROM RentalLogs;

-----------------------------------
GO
CREATE PROCEDURE ReportLostGame
    @RentalID INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        BEGIN TRANSACTION;

        --- Check if rental exists and hasn't been returned yet
        IF NOT EXISTS (
            SELECT 1 FROM Rentals
            WHERE RentalID = @RentalID AND ReturnDate IS NULL
        )
        BEGIN
            RAISERROR('Rental does not exist or has already been returned.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Get GameID from the rental
        DECLARE @GameID INT;

        SELECT @GameID = GameID
        FROM Rentals
        WHERE RentalID = @RentalID;

        -- Mark the rental as lost (set ReturnDate)
        UPDATE Rentals
        SET ReturnDate = GETDATE()
        WHERE RentalID = @RentalID;

        --  Decrease total and available copies
        UPDATE Games
        SET
            TotalCopies = CASE WHEN TotalCopies > 0 THEN TotalCopies - 1 ELSE 0 END,
            AvailableCopies = CASE WHEN AvailableCopies > 0 THEN AvailableCopies - 1 ELSE 0 END
        WHERE GameID = @GameID;

        --  Log the event
        INSERT INTO RentalLogs (RentalID, Operation)
        VALUES (@RentalID, 'LOST');

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;

        DECLARE @ErrorMessage NVARCHAR(4000) = ERROR_MESSAGE();
        RAISERROR(@ErrorMessage, 16, 1);
    END CATCH
END;

EXEC ReportLostGame @RentalID = 14;
