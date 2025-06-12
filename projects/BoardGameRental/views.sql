
USE BoardGameRental;

GO
CREATE VIEW ActiveRentalsView AS
SELECT
    r.RentalID,
    u.Username,
    u.Email,
    g.Title AS GameTitle,
    r.RentalDate,
    r.DueDate
FROM Rentals r
JOIN Users u ON r.UserID = u.UserID
JOIN Games g ON r.GameID = g.GameID
WHERE r.ReturnDate IS NULL;

--- USAGE
SELECT * FROM ActiveRentalsView;


--------------------
GO
CREATE VIEW OverdueRentalsView AS
SELECT
    r.RentalID,
    u.Username,
    u.Email,
    g.Title AS GameTitle,
    r.RentalDate,
    r.DueDate,
    DATEDIFF(DAY, r.DueDate, GETDATE()) AS DaysOverdue
FROM Rentals r
JOIN Users u ON r.UserID = u.UserID
JOIN Games g ON r.GameID = g.GameID
WHERE r.ReturnDate IS NULL
  AND r.DueDate < GETDATE();


-- USAGE
SELECT * FROM OverdueRentalsView;

GO
CREATE VIEW MostPopularGamesView AS
SELECT
    g.GameID,
    g.Title AS GameTitle,
    c.CategoryName,
    COUNT(r.RentalID) AS TotalRentals
FROM Games g
LEFT JOIN Rentals r ON g.GameID = r.GameID
LEFT JOIN Categories c ON g.CategoryID = c.CategoryID
GROUP BY g.GameID, g.Title, c.CategoryName;


SELECT * FROM MostPopularGamesView
ORDER BY TotalRentals DESC;