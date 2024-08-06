--Copyright (C) 2021 Kritik Agarwal <https://github.com/Kritik007>
--------------------------------------------------------------------------------------------------------------------------------
---- The following relations keep track of students, their enrollment for classes along with faculty information.
-------- Student (snum: integer, sname: string, major: string, level: string, age: integer)
-------- Class (name: string, meets at: string, room: string, d: integer)
-------- Enrolled (snum: integer, cname: string)
-------- Faculty (fid: integer, fname: string, deptid: integer)
-------- NOTE: The meaning of these relations is straight forward.
-------- For example, Enrolled has one record per student-class pair such that the student is enrolled in the class. 
-------- Level is a two character code with 4 different values (example: Junior: JR etc)
--------------------------------------------------------------------------------------------------------------------------------

------------------ START ----------------

-- CREATE DATABASE
CREATE DATABASE [StudentDB];
GO

--USING THE CREATED/EXISTING DATABASE
USE [StudentDB];
GO

--CREATING TABLES
--T1
CREATE TABLE [STUDENT](
	[SNUM] INT,
	[SNAME] VARCHAR(10),
	[MAJOR] VARCHAR(2),
	[LEVEL] VARCHAR(2),
	[AGE] INT,
	PRIMARY KEY([SNUM])
);
GO

--T2
CREATE TABLE [FACULTY](
	[FID] INT,
	[FNAME] VARCHAR(20),
	[DEPTID] INT,
	PRIMARY KEY(FID)
);
GO

--T3
CREATE TABLE [CLASS](
	[CNAME] VARCHAR(20),
	[MEETS_AT] VARCHAR(10),
	[ROOM] VARCHAR(10),
	[FID] INT,
	PRIMARY KEY([CNAME]),
	FOREIGN KEY([FID]) REFERENCES FACULTY([FID])
);
GO

--T4
CREATE TABLE [ENROLLED](
	[SNUM] INT,
	[CNAME] VARCHAR(20),
	PRIMARY KEY([SNUM],[CNAME]),
	FOREIGN KEY([SNUM]) REFERENCES STUDENT([SNUM]),
	FOREIGN KEY([CNAME]) REFERENCES CLASS([CNAME])
);
GO

--INSERTING SOME VALUES INTO THE DATABASE
--1
INSERT INTO [STUDENT] (SNUM,SNAME,MAJOR,[LEVEL],AGE) VALUES
(1,'SRUSHTI','CS','Sr',20),
(2,'VYSHNAVI','CS','Jr',19),
(3,'MITHILA','CV','Sr',20),
(4,'RUTVI','CS','Jr',20),
(5,'SID','CS','Jr',20),
(6,'KRITIK','CS','Sr',21);
GO

SELECT * FROM STUDENT;
GO

--2
INSERT INTO [FACULTY] (FID,FNAME,[DEPTID]) VALUES
(11,'PARAMESWARAN',1001),
(12,'SATHIYARAJ',1001),
(13,'BABU RAO',1002),
(14,'VANITHA',1002),
(15,'RAM',1001);
GO

SELECT * FROM FACULTY;
GO

--3
INSERT INTO [CLASS] (CNAME,MEETS_AT,ROOM,FID) VALUES
('LEC1','NOON','ROOM301',14),
('LEC4','MORNING','ROOM314',14),
('LEC2','MORNING','ROOM215',12),
('LEC3','MORNING','ROOM310',11),
('LEC8','EVENING','ROOM402',14),
('LEC5','EVENING','ROOM305',15),
('LEC6','MORNING','ROOM212',14),
('LEC7','MORNING','ROOM311',14);

SELECT * FROM CLASS;
GO

--4
INSERT INTO [ENROLLED] (SNUM,CNAME) VALUES
(1,'LEC1'),
(2,'LEC1'),
(3,'LEC3'),
(4,'LEC3'),
(3,'LEC4'),
(5,'LEC8'),
(1,'LEC5'),
(2,'LEC5'),
(3,'LEC5'),
(4,'LEC5'),
(5,'LEC5'),
(6,'LEC5');
GO

SELECT * FROM ENROLLED;
GO

-- QUERIES

-- Q1 Find the names of all juniors (level=Jr) who are enrolled for class taught by professor PARAMESWARAN.
SELECT DISTINCT S.SNAME FROM STUDENT S,CLASS C,FACULTY F,ENROLLED E
WHERE S.SNUM=E.SNUM AND E.CNAME=C.CNAME AND S.LEVEL='Jr' AND
F.FNAME='PARAMESWARAN' AND F.FID=C.FID;
GO

-- Q2 Find the names of all classes that either meet in ROOM314 or have 5 or more students enrolled.
SELECT DISTINCT CNAME FROM CLASS WHERE ROOM='ROOM314' OR
CNAME IN (SELECT E.CNAME FROM ENROLLED E GROUP BY E.CNAME HAVING COUNT(*)>=5);
GO

-- Q3 Find the names of all students who are enrolled in two classes that meet at same time.
SELECT DISTINCT S.SNAME FROM STUDENT S WHERE S.SNUM IN (SELECT E1.SNUM FROM ENROLLED E1,
ENROLLED E2,CLASS C1,CLASS C2 WHERE E1.SNUM=E2.SNUM AND E1.CNAME<>E2.CNAME AND
E1.CNAME=C1.CNAME AND C2.CNAME=C2.CNAME AND C1.MEETS_AT=C2.MEETS_AT);
GO

-- Q4 Find the names of faculty members who teach in every room in which some class is taught.
SELECT F.FNAME,F.FID FROM FACULTY F WHERE F.FID IN (SELECT C.FID FROM CLASS C 
GROUP BY C.FID HAVING COUNT(*)=(SELECT COUNT(DISTINCT ROOM) FROM CLASS));
GO

-- Q5 Find the names of the faculty members for whom the combined enrollment of the classes that they teach is less then five.
SELECT DISTINCT F.FNAME FROM FACULTY F WHERE F.FID IN (SELECT C.FID FROM CLASS C, 
ENROLLED E WHERE C.CNAME=E.CNAME GROUP BY C.CNAME HAVING COUNT(C.CNAME)<5);
GO

--------------END----------------
