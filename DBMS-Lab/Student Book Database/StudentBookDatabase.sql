--Copyright (C) 2021 Kritik Agarwal <https://githuB.com/Kritik007>
--------------------------------------------------------------------------------------------------------------------------------
---- The following relations keep track of students, their enrollment for classes along with faculty information.
-------- Student (snum: integer, sname: string, major: string, level: string, age: integer)
-------- Class (name: string, meets at: string, room: string, d: integer)
-------- Enrolled (snum: integer, cname: string)
-------- Faculty (fid: integer, fname: string, DEPTid: integer)
-------- NOTE: The meaning of these relations is straight forward.
-------- For example, Enrolled has one record per student-class pair such that the student is enrolled in the class. 
-------- Level is a two character code with 4 different values (example: Junior: JR etc)
-------- Queries:
---------- 1. Create the above tables by properly specifying the primary keys and the foreign keys.
---------- 2. Enter at least five tuples for each relation.
---------- 3. Demonstrate how you add a new text book to the database and make this book be adopted by some department.
--------------------------------------------------------------------------------------------------------------------------------

------------------ START ----------------

-- CREATE DATABASE
CREATE DATABASE [SBooksDB];
GO

--USING THE CREATED/EXISTING DATABASE
USE [SBooksDB];
GO

--CREATING TABLES
--T1
CREATE TABLE [STUDENT](
     [REGNO] VARCHAR(15),
     [NAME] VARCHAR(20),
     [MAJOR] VARCHAR(20),
     [BDATE] DATE,
     PRIMARY KEY ([REGNO]) 
);
GO

--T2
CREATE TABLE [COURSE](
     [COURSENO] INT,
     [CNAME] VARCHAR(20),
     [DEPT] VARCHAR(20),
     PRIMARY KEY ([COURSENO])
);
GO

--T3
CREATE TABLE [ENROLL](
     [REGNO] VARCHAR(15),
     [COURSENO] INT,
     [SEM] INT,
     [MARKS] INT,
     PRIMARY KEY ([REGNO],[COURSENO]),
     FOREIGN KEY ([REGNO]) REFERENCES [STUDENT]([REGNO]),
     FOREIGN KEY ([COURSENO]) REFERENCES [COURSE]([COURSENO]) 
);
GO

--T4
CREATE TABLE [TEXT](
     [BOOK_ISBN] INT,
     [BOOK_TITLE] VARCHAR(20),
     [PUBLISHER] VARCHAR(20),
     [AUTHOR] VARCHAR(20),
     PRIMARY KEY ([BOOK_ISBN]) 
);
GO

--T5
CREATE TABLE [BOOK_ADOPTION](
     [COURSENO] INT,
     [SEM] INT,
     [BOOK_ISBN] INT,
     PRIMARY KEY ([COURSENO],[BOOK_ISBN]),
     FOREIGN KEY ([COURSENO]) REFERENCES [COURSE](COURSENO),
     FOREIGN KEY ([BOOK_ISBN]) REFERENCES [TEXT]([BOOK_ISBN]) 
);
GO

--INSERTING SOME VALUES INTO THE DATABASE
--1
INSERT INTO [STUDENT]([REGNO],[NAME],[MAJOR],[BDATE]) VALUES 
('19BBTCS020','Arushi','Sr','20021230'),
('19BBTCS026','Ayush','Sr','20010924'),
('19BBTCS050','Himanshu','Sr','20011127'),
('19BBTCS066','Karan','Sr','20010413'),
('19BBTCS067','Kritik','Jr','20000507');
GO

SELECT * FROM STUDENT;
GO

--2
INSERT INTO COURSE VALUES 
(111,'OS','CSE'),
(112,'EC','CSE'),
(113,'SS','ISE'),
(114,'DBMS','CSE'),
(115,'SIGNALS','ECE');
GO

SELECT * FROM COURSE;
GO

--3
INSERT INTO [TEXT]([BOOK_ISBN],[BOOK_TITLE],[PUBLISHER],[AUTHOR]) VALUES
(10,'DATABASE SYSTEMS','PEARSON','SCHIELD'),
(900,'OPERATING SYS','PEARSON','LELAND'),
(901,'CIRCUITS','HALL INDIA','BOB'),
(902,'SYSTEM SOFTWARE','PETERSON','JACOB'),
(903,'SCHEDULING','PEARSON','PATIL'),
(904,'DATABASE SYSTEMS','PEARSON','JACOB'),
(905,'DATABASE MANAGER','PEARSON','BOB'),
(906,'SIGNALS','HALL INDIA','SUMIT');
GO

SELECT * FROM [TEXT];
GO

--4
INSERT INTO [ENROLL]([REGNO],[COURSENO],[SEM],[MARKS]) VALUES 
('19BBTCS020',115,3,100),
('19BBTCS067',114,5,100),
('19BBTCS066',113,5,100),
('19BBTCS026',111,5,100),
('19BBTCS050',112,3,100);
GO

SELECT * FROM ENROLL;
GO

--5
INSERT INTO [BOOK_ADOPTION]([COURSENO],[SEM],[BOOK_ISBN]) VALUES
(111,5,900),
(111,5,903),
(111,5,904),
(112,3,901),
(113,3,10),
(114,5,905),
(113,5,902),
(115,3,906);
GO

SELECT * FROM BOOK_ADOPTION;
GO

-- QUERIES

-- Q1 Produce a list of text books (include Course #, Book-ISBN, Book-title) in the alphabetical order 
----- for COURSEs offered by the 'CS' department that use more than two books.
SELECT C.COURSENO,T.BOOK_ISBN,T.BOOK_TITLE FROM COURSE C,BOOK_ADOPTION BA,[TEXT] T 
WHERE C.COURSENO=BA.COURSENO AND BA.BOOK_ISBN=T.BOOK_ISBN AND C.DEPT='CSE'
AND 2<(SELECT COUNT(BOOK_ISBN) FROM BOOK_ADOPTION B WHERE C.COURSENO=B.COURSENO)
ORDER BY T.BOOK_TITLE;
GO

-- Q2 List any department that has all its adopted books published by a specific publisher. 
SELECT DISTINCT C.DEPT FROM COURSE C WHERE C.DEPT IN (SELECT C.DEPT FROM COURSE C,
BOOK_ADOPTION B,[TEXT] T WHERE C.COURSENO=B.COURSENO AND T.BOOK_ISBN=B.BOOK_ISBN
AND T.PUBLISHER='PEARSON') AND C.DEPT NOT IN (SELECT C.DEPT FROM COURSE C,BOOK_ADOPTION B,
[TEXT] T WHERE C.COURSENO=B.COURSENO AND T.BOOK_ISBN=B.BOOK_ISBN AND T.PUBLISHER != 'PEARSON');
GO

--------------END----------------
