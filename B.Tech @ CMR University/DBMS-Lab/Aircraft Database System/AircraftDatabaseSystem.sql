--Copyright (C) 2021 Kritik Agarwal <https://github.com/Kritik007>
--------------------------------------------------------------------------------------------------------------------------------
---- The following relations keep track of airline flight information:
-------- FLIGHTS (no:integer,from:string,to:string,distance:integer,departs:time,arrives:time,price:real)
-------- AIRCRAFT (aid:integer,aname:string,cruisingrange:integer)
-------- CERTIFIED (eid:integer,aid:integer)
-------- EMPLOYEES (eid:integer,ename:string,salary:integer)
-------- NOTE that the EMPLOYEES relation describes pilots and other kinds of employees as well;
---------------- Every pilot is certified for some aircraft,and only pilots are certified to fly.
--------------------------------------------------------------------------------------------------------------------------------

------------------ START ----------------

-- CREATE DATABASE (RUN ONLY ONCE)
CREATE DATABASE [FlightsDB];
GO

--USING THE EXISTING DATABASE
USE [FlightsDB];
GO

--CREATING TABLES
--T1
CREATE TABLE [FLIGHT](
	[NO] INT PRIMARY KEY,
	[FROM] VARCHAR(20),
	[TOO] VARCHAR(20),
	[DIST] INT,
	[DEPARTS] VARCHAR(20),
	[ARRIVES] VARCHAR(20),
	[PRICE] REAL
);
GO

--T2
CREATE TABLE [AIRCRAFT](
	[AID] INT PRIMARY KEY,
    [AName] VARCHAR(20),
    [CruisingRange] INT
);
GO

--T3
CREATE TABLE [EMPLOYEES](
    [EID] INT PRIMARY KEY,
    [EName] VARCHAR(20),
    [Salary] INT
);
GO

--T4
CREATE TABLE [CERTIFIED](
    [EID] INT,
    [AID] INT,
    PRIMARY KEY (EID,AID),
    FOREIGN KEY (EID) REFERENCES [EMPLOYEES]([EID]),
    FOREIGN KEY (AID) REFERENCES [AIRCRAFT]([AID]) 
);
GO

--INSERTING SOME VALUES INTO THE DATABASE
--1
INSERT INTO [FLIGHT]([NO],[FROM],[TOO],[DIST],[DEPARTS],[ARRIVES],[PRICE]) VALUES 
(1,'Bengaluru','Mangalore', 360,'10:45:00','12:00:00', 10000),
(2,'Bengaluru','Delhi', 5000,'12:15:00','04:30:00', 25000),
(3,'Bengaluru','Mumbai', 3500,'02:15:00','05:25:00', 30000),
(4,'Dibrugarh','Bengaluru', 2416,'13:30:00','17:05:00', 9500),
(5,'Delhi','Frankfurt', 18000,'07:15:00','05:30:00', 90000),
(6,'Bengaluru','Frankfurt', 19500,'10:00:00','07:45:00', 95000),
(7,'Bengaluru','Frankfurt', 17000,'12:00:00','06:30:00', 99000);
GO

--2
INSERT INTO [AIRCRAFT]([AID],[AName],[CruisingRange]) VALUES 
(123,'Airbus',1000),
(302,'Boeing777',5000),
(306,'Jet001',5000),
(378,'Airbus390',8000),
(456,'Aircraft',500),
(789,'Aircraft002',800),
(951,'Aircraft003',1000);
GO

--3
INSERT INTO [EMPLOYEES]([EID],[EName],[Salary]) VALUES
(1,'Jatin',30000),
(2,'Vikash',85000),
(3,'Krishna',50000),
(4,'Himanta',45000),
(5,'Rony',90000),
(6,'Siddharth',75000),
(7,'Kritik',100000);
GO

--4
INSERT INTO [CERTIFIED]([EID],[AID]) VALUES
(7,123), (2,123), (1,302), (5,302), (7,302), 
(7,306), (2,306), (1,378), (7,378), (4,378), 
(6,456), (7,456), (5,789), (6,789), (3,951), 
(7,951), (7,789);
GO


-- QUERIES

-- Q1 Find the names of aircraft such that all pilots certified to operate them have salaries more than Rs 80,000.
SELECT DISTINCT A.AName FROM AIRCRAFT A,CERTIFIED C,EMPLOYEES E
WHERE A.AID = C.AID AND C.EID=E.EID AND NOT EXISTS (SELECT * FROM EMPLOYEES E1 WHERE E1.EID=E.EID AND E1.Salary<80000);
GO

-- Q2 For each pilot who is certified for more than three aircrafts,
----  find the eid and the maximum cruisingrange of the aircraft for which he/she is certified.
SELECT C.[EID],MAX(CruisingRange) FROM CERTIFIED C,AIRCRAFT A WHERE C.AID=A.AID GROUP BY C.EID HAVING COUNT(*)>3;
GO

-- Q3 Find the names of all pilots whose salary is less than the price of the cheapest route from Bengaluru to Frankfurt.
SELECT DISTINCT E.EName FROM EMPLOYEES E 
WHERE E.Salary<(SELECT MIN(F.PRICE) FROM FLIGHT F WHERE F.[FROM]='Bengaluru' AND F.TOO='Frankfurt');
GO

-- Q4 For all aircrafts with cruisingrange over 1000 kms,
----  find the name of the aircraft and the average salary of all pilots certified for this aircraft.
SELECT A.AID, A.AName,AVG(E.Salary) FROM AIRCRAFT A,CERTIFIED C,EMPLOYEES E WHERE A.AID=C.AID
AND C.EID=E.EID AND A.CruisingRange>1000 GROUP BY A.AID,A.AName;
GO

-- Q5 Find the names of pilots certified for some Boeing aircraft.
SELECT DISTINCT E.EName FROM EMPLOYEES E, AIRCRAFT A, CERTIFIED C
WHERE E.EID=C.EID AND C.AID=A.AID AND A.AName='Boeing777';
GO

-- Q6 Find the aid's of all aircraft that can be used on routes from Bengaluru to Delhi.
SELECT A.AID FROM AIRCRAFT A 
WHERE A.CruisingRange>(SELECT MIN(F.DIST) FROM FLIGHT F 
WHERE F.[FROM]='Bengaluru' AND F.TOO='Delhi');
GO

--------------END----------------