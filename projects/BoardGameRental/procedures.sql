

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
            -- ROLLBACK TRANSACTION;
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
            RETURN;
        END

        IF @AvailableCopies <= 0
        BEGIN
            RAISERROR('No available copies of this game.', 16, 1);
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

        -- DECLARE @ErrorMessage NVARCHAR(4000) = ERROR_MESSAGE();
        RAISERROR(ERROR_MESSAGE(), 16, 1);
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
        END

        -- Check if the rental has already been returned
        IF EXISTS (
            SELECT 1 FROM Rentals
            WHERE RentalID = @RentalID AND ReturnDate IS NOT NULL
        )
        BEGIN
            RAISERROR('Game has already been returned.', 16, 1);
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

        -- DECLARE @ErrorMessage NVARCHAR(4000) = /();
        RAISERROR(ERROR_MESSAGE(), 16, 1);
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

SELECT *
FROM RentalLogs
WHERE RentalID = 14


GO
CREATE PROCEDURE AddGame
    @Title VARCHAR(100),
    @CategoryName NVARCHAR(100)
AS
BEGIN
    SET NOCOUNT ON;
    
    BEGIN TRY
        BEGIN TRANSACTION;
        -- Check whether GAME exists
        IF EXISTS(
            SELECT 1 FROM Games
            WHERE Title=@Title
        )
        BEGIN
            PRINT('Game already exists, not created one, update existing copies.');
            UPDATE Games
            SET TotalCopies = TotalCopies + 1, AvailableCopies = AvailableCopies + 1
            WHERE Title=@Title
            COMMIT TRANSACTION;
            RETURN;
        END

        DECLARE @NewGameCategoryId INT

        SELECT @NewGameCategoryId = Categories.CategoryID
        FROM Games
        LEFT JOIN Categories ON Categories.CategoryID = Games.CategoryID
        WHERE Categories.CategoryName=@CategoryName;


        INSERT Games(Title, CategoryID, TotalCopies, AvailableCopies)
        VALUES(@Title, @NewGameCategoryId, 1, 1);

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;
        DECLARE @ErrorMessage NVARCHAR(4000) = ERROR_MESSAGE();
        
        RAISERROR(@ErrorMessage, 16, 1);
    END CATCH
END

SELECT *FROM Categories;

EXEC AddGame @Title="majong123", @CategoryName="Logiczne"

GO
CREATE PROCEDURE AddGame
    @Title VARCHAR(100),
    @CategoryName NVARCHAR(100)
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        BEGIN TRANSACTION;

        -- Jeœli gra ju¿ istnieje ? tylko inkrementuj kopie
        IF EXISTS (
            SELECT 1 FROM Games
            WHERE Title = @Title
        )
        BEGIN
            PRINT('Game already exists. Incrementing number of copies.');
            
            UPDATE Games
            SET TotalCopies = TotalCopies + 1,
                AvailableCopies = AvailableCopies + 1
            WHERE Title = @Title;

            COMMIT TRANSACTION;
            RETURN;
        END

        DECLARE @CategoryID INT;

        -- Szukamy ID kategorii
        SELECT @CategoryID = CategoryID
        FROM Categories
        WHERE CategoryName = @CategoryName;

        -- if not exists- creating one 
        IF @CategoryID IS NULL
        BEGIN
            PRINT('Category does not exist. Creating one.');
            INSERT INTO Categories(CategoryName)
            VALUES (@CategoryName);

            SET @CategoryID = SCOPE_IDENTITY();
        END

        -- Dodajemy now¹ grê z 1 kopi¹
        INSERT INTO Games (Title, CategoryID, TotalCopies, AvailableCopies)
        VALUES (@Title, @CategoryID, 1, 1);

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;

        RAISERROR(@@ERROR_MESSAGE() ,16, 1);
    END CATCH
END;


EXEC AddGame @Title="maslo123", @CategoryName="superfajna"

SELECT * FROM Games;

