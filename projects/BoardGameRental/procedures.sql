

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

        -- Sprawd�, czy u�ytkownik istnieje
        IF NOT EXISTS (SELECT 1 FROM Users WHERE UserID = @UserID)
        BEGIN
            RAISERROR('User does not exist.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Sprawd�, czy gra istnieje i jest dost�pna
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

        -- Dodaj wypo�yczenie na 7 dni
        DECLARE @Today DATE = GETDATE();
        DECLARE @Due DATE = DATEADD(DAY, 7, @Today);

        INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate)
        VALUES (@UserID, @GameID, @Today, @Due);

        -- Pobierz ID nowo dodanego wypo�yczenia
        DECLARE @RentalID INT = SCOPE_IDENTITY();

        -- Dodaj wpis do loga
        INSERT INTO RentalLogs (RentalID, Operation)
        VALUES (@RentalID, 'RENT');

        -- Zmniejsz dost�pne egzemplarze
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


--------------
CREATE PROCEDURE ReturnGame
    @RentalID INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        BEGIN TRANSACTION;

        -- Sprawd�, czy wypo�yczenie istnieje
        IF NOT EXISTS (SELECT 1 FROM Rentals WHERE RentalID = @RentalID)
        BEGIN
            RAISERROR('Rental does not exist.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Sprawd�, czy ju� zosta�o zwr�cone
        IF EXISTS (
            SELECT 1 FROM Rentals
            WHERE RentalID = @RentalID AND ReturnDate IS NOT NULL
        )
        BEGIN
            RAISERROR('Game has already been returned.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Pobierz GameID z wypo�yczenia
        DECLARE @GameID INT;

        SELECT @GameID = GameID
        FROM Rentals
        WHERE RentalID = @RentalID;

        -- Ustaw dzisiejszy dzie� jako ReturnDate
        UPDATE Rentals
        SET ReturnDate = GETDATE()
        WHERE RentalID = @RentalID;

        -- Zwi�ksz dost�pne egzemplarze
        UPDATE Games
        SET AvailableCopies = AvailableCopies + 1
        WHERE GameID = @GameID;

        -- Dodaj wpis do RentalLogs
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

EXEC ReturnGame @RentalID = 25;

-----------------------------
CREATE PROCEDURE ExtendRental
    @RentalID INT,
    @ExtraDays INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        BEGIN TRANSACTION;

        -- Sprawd�, czy wypo�yczenie istnieje i nie zosta�o ju� zwr�cone
        IF NOT EXISTS (
            SELECT 1 FROM Rentals
            WHERE RentalID = @RentalID AND ReturnDate IS NULL
        )
        BEGIN
            RAISERROR('Rental does not exist or has already been returned.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Sprawd�, czy ju� by�o przed�u�ane (czyli czy istnieje wpis w logach z 'EXTEND')
        IF EXISTS (
            SELECT 1 FROM RentalLogs
            WHERE RentalID = @RentalID AND Operation LIKE 'EXTEND %'
        )
        BEGIN
            RAISERROR('This rental has already been extended once.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Przed�u� termin o podan� liczb� dni
        UPDATE Rentals
        SET DueDate = DATEADD(DAY, @ExtraDays, DueDate)
        WHERE RentalID = @RentalID;

        -- Dodaj wpis do loga
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
EXEC ExtendRental @RentalID = 12, @ExtraDays = 5;

-----------------------------------
CREATE PROCEDURE ReportLostGame
    @RentalID INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        BEGIN TRANSACTION;

        -- Sprawd�, czy wypo�yczenie istnieje i nie zosta�o ju� zwr�cone
        IF NOT EXISTS (
            SELECT 1 FROM Rentals
            WHERE RentalID = @RentalID AND ReturnDate IS NULL
        )
        BEGIN
            RAISERROR('Rental does not exist or has already been returned.', 16, 1);
            ROLLBACK TRANSACTION;
            RETURN;
        END

        -- Pobierz GameID z wypo�yczenia
        DECLARE @GameID INT;

        SELECT @GameID = GameID
        FROM Rentals
        WHERE RentalID = @RentalID;

        -- Zako�cz wypo�yczenie jako zagubione
        UPDATE Rentals
        SET ReturnDate = GETDATE()
        WHERE RentalID = @RentalID;

        -- Zmniejsz ca�kowit� i dost�pn� liczb� kopii
        UPDATE Games
        SET
            TotalCopies = CASE WHEN TotalCopies > 0 THEN TotalCopies - 1 ELSE 0 END,
            AvailableCopies = CASE WHEN AvailableCopies > 0 THEN AvailableCopies - 1 ELSE 0 END
        WHERE GameID = @GameID;

        -- Loguj zdarzenie
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
