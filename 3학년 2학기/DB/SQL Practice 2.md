0. create clinet table
```sql
CREATE TABLE Client
(
    cid CHAR(20) NOT NULL,
    cname CHAR(10) NOT NULL,
    age REAL,
    grade CHAR(10) NOT NULL,
    job CHAR(20),
    mileage INTEGER,
    primary key (cid)
);
```
1. create Kim's VIEW and get ages of Kim's
```sql
CREATE VIEW KIM_VIEW(cid, cname, age, grade, job, mileage)
AS SELECT *
FROM Client C
WHERE C.name LIKE '김%';
SELECT K.age FROM KIM_VIEW K;
```

2. get number of people by grade
```sql
SELECT * FROM Client;
SELECT C.grade, COUNT (*) AS gcnt
FROM Client C
GROUP BY C.grade;
```

3. get grade that has minimumm average ages
<br>

~~SELECT C.grade <br>
FROM Client C <br>
GROUP BY C.grade <br>
HAVING AVG (C.age) <br>
= (SELECT MIN (AVG (C2.age)) AS mgavg FROM Client C2 GROUP BY C2.grade); <br>
<br>
마지막 그룹바이 안 해도 되는지 체크 필요. <br>
급해서 위와 같이 작성 이후 제출함 ~~

<br>

틀렸다.

![get minimum average age's rating](https://user-images.githubusercontent.com/71186266/196641671-ddaaecc2-9878-4bd4-93e4-1740376be9aa.jpg)

이게 올바른 답이다.
