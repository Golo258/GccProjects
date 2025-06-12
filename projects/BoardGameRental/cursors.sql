


USE BoardGameRental;
GO

--- CURSOR WITH JSON
CREATE TABLE RentalsJson (
    ID INT IDENTITY(1,1) PRIMARY KEY,
    UserID INT,
    JsonData NVARCHAR(MAX)
);

GO
CREATE PROCEDURE GenerateUserRentalsJson
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        BEGIN TRANSACTION;

        DECLARE @UserID INT;
        DECLARE user_cursor CURSOR FOR
        SELECT DISTINCT UserID FROM Rentals;

        OPEN user_cursor;
        FETCH NEXT FROM user_cursor INTO @UserID;

        WHILE @@FETCH_STATUS = 0
        BEGIN
            DECLARE @Json NVARCHAR(MAX);

            SET @Json = (
                SELECT 
                    g.Title AS GameTitle,
                    r.RentalDate,
                    r.DueDate,
                    r.ReturnDate
                FROM Rentals r
                JOIN Games g ON r.GameID = g.GameID
                WHERE r.UserID = @UserID
                FOR JSON PATH, ROOT('rentals')
            );

            INSERT INTO RentalsJson (UserID, JsonData)
            VALUES (@UserID, @Json);

            FETCH NEXT FROM user_cursor INTO @UserID;
        END

        CLOSE user_cursor;
        DEALLOCATE user_cursor;

        COMMIT TRANSACTION;
    END TRY
    BEGIN CATCH
        ROLLBACK TRANSACTION;

        DECLARE @Error NVARCHAR(4000) = ERROR_MESSAGE();
        RAISERROR(@Error, 16, 1);
    END CATCH
END;


EXEC GenerateUserRentalsJson;
SELECT * FROM RentalsJson;