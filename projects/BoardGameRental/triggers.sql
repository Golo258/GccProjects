

USE BoardGameRental;
GO

--- TRIGGERS
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


INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate)
VALUES (5, 10, GETDATE(), DATEADD(DAY, 7, GETDATE()));

SELECT TOP 1 *
FROM RentalLogs
ORDER BY OperationDate DESC;

---
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

---------------------
INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate)
VALUES (5, 12, GETDATE(), DATEADD(DAY, 7, GETDATE()));

SELECT TOP 1 RentalID
FROM Rentals
WHERE UserID = 5 AND GameID = 12
ORDER BY RentalID DESC;

DELETE FROM Rentals
WHERE RentalID = 46;

DELETE FROM Rentals WHERE RentalID = 46;

SELECT *
FROM RentalLogs
WHERE RentalID = 46;

---------------------

CREATE TRIGGER TR_BlockUnavailableRentals
ON Rentals
INSTEAD OF INSERT
AS
BEGIN
    SET NOCOUNT ON;

    -- Sprawd� wstawiane dane i odfiltruj gry niedost�pne
    IF EXISTS (
        SELECT 1
        FROM inserted i
        JOIN Games g ON i.GameID = g.GameID
        WHERE g.AvailableCopies <= 0
    )
    BEGIN
        RAISERROR('Cannot rent: the selected game is not available.', 16, 1);
        RETURN;
    END

    -- Je�li wszystko OK � wykonaj prawdziwy insert
    INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate, ReturnDate)
    SELECT UserID, GameID, RentalDate, DueDate, ReturnDate
    FROM inserted;
END;

--- POSITIVE SCENARIO
INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate)
VALUES (6, 4, GETDATE(), DATEADD(DAY, 7, GETDATE()));

-- NEGATIVE SCENARIO
INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate)
VALUES (7, 3, GETDATE(), DATEADD(DAY, 7, GETDATE()));
