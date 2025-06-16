CREATE DATABASE BoardGameRental;
GO


USE BoardGameRental;
GO

-- TABLES CREATION
CREATE TABLE Users (
    UserID INT IDENTITY(1,1) PRIMARY KEY,
    Username NVARCHAR(50) NOT NULL,
    Email NVARCHAR(100) NOT NULL UNIQUE,
    RegistrationDate DATE NOT NULL
);
--
CREATE TABLE Categories (
    CategoryID INT IDENTITY(1,1) PRIMARY KEY,
    CategoryName NVARCHAR(50) NOT NULL
);
--
CREATE TABLE Games (
    GameID INT IDENTITY(1,1) PRIMARY KEY,
    Title NVARCHAR(100) NOT NULL,
    CategoryID INT FOREIGN KEY REFERENCES Categories(CategoryID),
    TotalCopies INT NOT NULL,
    AvailableCopies INT NOT NULL
);      
--
CREATE TABLE Rentals (
    RentalID INT IDENTITY(1,1) PRIMARY KEY,
    UserID INT FOREIGN KEY REFERENCES Users(UserID),
    GameID INT FOREIGN KEY REFERENCES Games(GameID),
    RentalDate DATE NOT NULL,
    DueDate DATE NOT NULL,
    ReturnDate DATE NULL
);
--
CREATE TABLE RentalLogs (
    LogID INT IDENTITY(1,1) PRIMARY KEY,
    RentalID INT FOREIGN KEY REFERENCES Rentals(RentalID),
    Operation NVARCHAR(20),
    OperationDate DATETIME DEFAULT GETDATE()
);


-- FILLING TABLES WITH DATA
INSERT INTO Users (Username, Email, RegistrationDate)
VALUES
('janek', 'janek.nowak@gmail.com', '2023-12-12'),
('k_wiola', 'wiola.kowalska@gmail.com', '2024-01-03'),
('misiek88', 'michal88@gmail.com', '2024-01-14'),
('ania_w', 'ania.w@gmail.com', '2024-02-01'),
('piotrek_g', 'piotr.grabowski@gmail.com', '2024-02-18'),
('kamilos', 'kamil.olek@gmail.com', '2024-03-02'),
('z_basia', 'zosia.b@gmail.com', '2024-03-14'),
('tomek96', 'tomek.96@gmail.com', '2024-03-28'),
('lenaaa', 'lena.jankowska@gmail.com', '2024-04-04'),
('darek_g', 'darek.g@gmail.com', '2024-04-12'),
('aga_zn', 'agata.z@gmail.com', '2024-04-27'),
('filipster', 'filip.k@gmail.com', '2024-05-08'),
('grzesiek97', 'grzesiek97@gmail.com', '2024-01-21'),
('sylwia_p', 'sylwia.piekarska@outlook.com', '2024-02-03'),
('mateo', 'mateusz.l@outlook.com', '2024-02-16'),
('joanna_k', 'joanna.kowal@outlook.com', '2024-02-20'),
('szymon_x', 'szymon.x@outlook.com', '2024-03-01'),
('julia_m', 'julia.m@outlook.com', '2024-03-08'),
('pawel_n', 'pawel.n@outlook.com', '2024-03-17'),
('klaudiaa', 'klaudia.r@outlook.com', '2024-03-22'),
('hubert12', 'hubert.nowak@mail.com', '2024-03-29'),
('ewelina_k', 'ewelina.k@mail.com', '2024-04-05'),
('krystianx', 'krystian@mail.com', '2024-04-10'),
('natalia_w', 'natalia.w@mail.com', '2024-04-14'),
('wojtek_92', 'wojtek92@mail.com', '2024-04-18'),
('olga_b', 'olga.b@mail.com', '2024-04-22'),
('arek_m', 'arkadiusz.m@mail.com', '2024-04-25'),
('jadzia_xd', 'jadzia@mail.com', '2024-04-29'),
('bartek_m', 'bartek.m@mail.com', '2024-05-02'),
('patrykss', 'patryk.s@mail.com', '2024-05-06');


INSERT INTO Categories (CategoryName)
VALUES
('Strategiczne'),
('Imprezowe'),
('Kooperacyjne'),
('Karcianki'),
('Logiczne'),
('RPG'),
('Dzieci�ce'),
('Przygodowe'),
('Ekonomiczne'),
('Dwuosobowe'),
('Rodzinne'),
('Quizowe'),
('Deckbuilding'),
('Uk�adanki'),
('Dedukcyjne'),
('Zr�czno�ciowe'),
('Survival');



INSERT INTO Games (Title, CategoryID, TotalCopies, AvailableCopies)
VALUES
('Catan', 1, 5, 3),
('Dixit', 2, 4, 2),
('Pandemic', 3, 3, 0),
('UNO', 4, 8, 6),
('Azul', 5, 5, 5),
('Dungeons & Dragons', 6, 2, 2),
('Piodz�ce ��wie', 7, 6, 4),
('Robinson Crusoe', 8, 3, 1),
('Terraformacja Marsa', 9, 4, 3),
('Jaipur', 10, 2, 2),
('Dobble', 11, 10, 9),
('5 Sekund', 12, 6, 4),
('Dominion', 13, 3, 1),
('Ubongo', 14, 5, 3),
('Cluedo', 15, 4, 2),
('Jenga', 16, 7, 6),
('This War of Mine', 17, 2, 0),
('Tajniacy', 15, 6, 5),
('Splendor', 1, 4, 2),
('Star Realms', 13, 3, 2),
('7 Cud�w �wiata', 1, 5, 3),
('Wsi��� do Poci�gu: Europa', 1, 6, 5),
('Codenames: Pictures', 15, 4, 2),
('BANG!', 4, 5, 3),
('Ghost Stories', 3, 3, 1),
('Exit: Tajemnicze Laboratorium', 15, 2, 1),
('Karuba', 5, 4, 4),
('Palce w Pralce', 2, 5, 5),
('Ryzyk Fizyk', 12, 6, 5),
('Munchkin', 6, 4, 2),
('Reef', 5, 4, 3),
('Patchwork', 14, 5, 4),
('Escape Room: Skok w Wenecji', 8, 3, 2),
('Timeline: Polska', 12, 4, 4),
('Jungle Speed', 16, 6, 5),
('Zgadnij Kto To?', 11, 8, 7),
('Takenoko', 11, 5, 3),
('Splendor Duel', 10, 3, 2),
('Star Wars: Rebellion', 17, 2, 1),
('Sabota�ysta', 4, 5, 5),
('Dominion: Intryga', 13, 3, 2),
('The Mind', 3, 5, 5),
('Magic Maze', 3, 4, 2),
('Mystery House', 15, 2, 1),
('Domek', 9, 4, 3),
('Small World', 1, 4, 3),
('Alias', 2, 6, 4),
('Spirit Island', 3, 2, 1),
('Exploding Kittens', 4, 7, 6),
('Sherlock Holmes: Detektyw Doradczy', 15, 2, 1),
('IQ Fit', 5, 3, 3),
('Zamek', 7, 5, 5),
('Mali Detektywi', 11, 4, 4),
('Ekosystem', 14, 3, 3),
('Aeon�s End', 13, 2, 1),
('Dobble Kids', 7, 4, 4),
('Jungle Boogie', 16, 3, 3),
('Dead of Winter', 17, 2, 0),
('Valeria: Card Kingdoms', 13, 3, 2),
('Super Farmer', 11, 6, 5);


INSERT INTO Rentals (UserID, GameID, RentalDate, DueDate, ReturnDate)
VALUES
(1, 3, '2024-05-01', '2024-05-08', '2024-05-07'),
(2, 7, '2024-05-02', '2024-05-09', NULL),
(3, 10, '2024-04-25', '2024-05-02', '2024-05-01'),
(4, 15, '2024-05-03', '2024-05-10', NULL),
(5, 20, '2024-04-29', '2024-05-06', '2024-05-07'),
(6, 8, '2024-05-04', '2024-05-11', NULL),
(7, 11, '2024-05-05', '2024-05-12', NULL),
(8, 13, '2024-05-06', '2024-05-13', NULL),
(9, 6, '2024-05-07', '2024-05-14', NULL),
(10, 1, '2024-05-01', '2024-05-08', '2024-05-06'),
(11, 4, '2024-05-02', '2024-05-09', NULL),
(12, 9, '2024-05-03', '2024-05-10', NULL),
(13, 5, '2024-05-04', '2024-05-11', NULL),
(14, 2, '2024-05-05', '2024-05-12', NULL),
(15, 12, '2024-05-06', '2024-05-13', NULL),
(16, 17, '2024-05-07', '2024-05-14', NULL),
(17, 18, '2024-05-08', '2024-05-15', NULL),
(18, 19, '2024-05-09', '2024-05-16', NULL),
(19, 14, '2024-05-10', '2024-05-17', NULL),
(20, 16, '2024-05-11', '2024-05-18', NULL),
(21, 22, '2024-05-12', '2024-05-19', NULL),
(22, 5, '2024-05-10', '2024-05-17', '2024-05-15'),
(23, 30, '2024-05-08', '2024-05-15', NULL),
(24, 9, '2024-05-05', '2024-05-12', '2024-05-10'),
(25, 14, '2024-05-04', '2024-05-11', NULL),
(26, 3, '2024-05-03', '2024-05-10', NULL),
(27, 7, '2024-05-02', '2024-05-09', NULL),
(28, 33, '2024-05-01', '2024-05-08', NULL),
(29, 40, '2024-04-30', '2024-05-07', NULL),
(30, 17, '2024-04-29', '2024-05-06', '2024-05-06'),
(1, 45, '2024-05-10', '2024-05-17', NULL),
(2, 12, '2024-05-09', '2024-05-16', NULL),
(3, 27, '2024-05-08', '2024-05-15', NULL),
(4, 16, '2024-05-07', '2024-05-14', NULL),
(5, 38, '2024-05-06', '2024-05-13', NULL),
(6, 26, '2024-05-05', '2024-05-12', NULL),
(7, 44, '2024-05-04', '2024-05-11', '2024-05-08'),
(8, 19, '2024-05-03', '2024-05-10', NULL),
(9, 8, '2024-05-02', '2024-05-09', NULL),
(10, 2, '2024-05-01', '2024-05-08', NULL);

