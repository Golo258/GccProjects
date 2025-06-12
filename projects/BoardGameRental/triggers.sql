USE BoardGameRental;
GO

-- TRIGGERS

-- Trigger: Log insertions into Rentals table
CREATE TRIGGER TR_Rentals_Insert_Log
ON Rentals
AFTER INSERT
AS
BEGIN
    SET NOCOUNT ON;

    INSERT INTO RentalLogs (RentalID, Operation)
    SELECT RentalID, 'RENT'
    FROM inserted;
END;

-- Test INSERT triggering RENT log
INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate)
VALUES (5, 10, GETDATE(), DATEADD(DAY, 7, GETDATE()));

-- Check the latest RentalLogs entry
SELECT TOP 1 *
FROM RentalLogs
ORDER BY OperationDate DESC;

GO

-- Trigger: Log deletions from Rentals table
CREATE TRIGGER TR_Rentals_Delete_Log
ON Rentals
AFTER DELETE
AS
BEGIN
    SET NOCOUNT ON;

    INSERT INTO RentalLogs (RentalID, Operation)
    SELECT RentalID, 'DELETE'
    FROM deleted;
END;

-- Insert and then delete rental to test DELETE trigger
INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate)
VALUES (5, 12, GETDATE(), DATEADD(DAY, 7, GETDATE()));

-- Get the latest RentalID for that user and game
SELECT TOP 1 RentalID
FROM Rentals
WHERE UserID = 5 AND GameID = 12
ORDER BY RentalID DESC;

-- Delete rental (example)
DELETE FROM Rentals
WHERE RentalID = 46;

-- Check the RentalLogs for the deleted rental
SELECT *
FROM RentalLogs
WHERE RentalID = 46;

GO

-- Trigger: Prevent renting games that have no available copies
CREATE TRIGGER TR_BlockUnavailableRentals
ON Rentals
INSTEAD OF INSERT
AS
BEGIN
    SET NOCOUNT ON;

    -- Check the incoming rows and block if any game is unavailable
    IF EXISTS (
        SELECT 1
        FROM inserted
        JOIN Games ON inserted.GameID = Games.GameID
        WHERE Games.AvailableCopies <= 0
    )
    BEGIN
        RAISERROR('Cannot rent: the selected game is not available.', 16, 1);
        RETURN;
    END

    -- If all checks pass, proceed with the actual insert
    INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate, ReturnDate)
    SELECT UserID, GameID, RentalDate, DueDate, ReturnDate
    FROM inserted;
END;

-- ✅ Positive scenario (available game)
INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate)
VALUES (6, 4, GETDATE(), DATEADD(DAY, 7, GETDATE()));

-- ❌ Negative scenario (unavailable game)
INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate)
VALUES (7, 3, GETDATE(), DATEADD(DAY, 7, GETDATE()));
