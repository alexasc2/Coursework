/*Query 1:
 Equate topicid and id to find # id
 */
SELECT id, description, counter FROM topic NATURAL INNER JOIN
	(SELECT topicid AS id, COUNT(*) AS counter FROM blurt_analysis GROUP BY topicid 
    UNION SELECT id, NULL FROM topic WHERE id NOT IN (SELECT topicid AS id FROM blurt_analysis)) AS union2 
ORDER BY id;

/*Query 2:
 */
SELECT name, followeeCount FROM user NATURAL INNER JOIN
	(SELECT email, followeeCount FROM celebrity NATURAL INNER JOIN
		(SELECT followee AS email, COUNT(followee) AS followeeCount FROM follow GROUP BY followee) AS union1
        UNION (SELECT email, NULL FROM celebrity WHERE email NOT IN (SELECT followee FROM follow))) AS union2 
ORDER BY followeeCount DESC;


/*Query 3:
 */
SELECT name, blurtCount FROM user NATURAL RIGHT JOIN
	(SELECT email, COUNT(*) AS blurtCount FROM blurt GROUP BY email
	UNION SELECT email, NULL FROM celebrity WHERE email NOT IN (SELECT email FROM blurt)) AS union2
    NATURAL RIGHT JOIN celebrity
ORDER BY blurtCount DESC;

/*Query 4:
 NOTE - find follower emails, then the names 
 */
SELECT DISTINCT name FROM user u JOIN celebrity c 
	ON (u.email = c.email) WHERE c.email NOT IN
		(SELECT follower FROM follow);

/*Query 5:
 */
SELECT v.name, va.email, COUNT(*) AS counter FROM vendor v JOIN follow f JOIN vendor_ambassador va 
	ON (f.followee = va.email AND va.vendorid = v.id) 
GROUP BY f.followee ORDER BY counter DESC;

/*Query 6:
 */
SELECT v.name, COUNT(DISTINCT ba.email) AS counter FROM vendor v JOIN blurt_analysis AS ba JOIN vendor_topic AS vt 
ON ( v.id = vt.vendorid AND vt.topicid = ba.topicid) WHERE ba.email NOT IN 
	(SELECT ua.email FROM user_ad AS ua, advertisement AS a WHERE a.id = ua.adid AND v.id = a.vendorid)
GROUP BY v.id
ORDER BY counter DESC;

/*Query 7:
 NOTE - returning 5113 rows for some reason
		have no clue why
 */
SELECT u1.name, u2.name FROM user AS u1 JOIN user AS u2 JOIN
	(SELECT DISTINCT ba1.email AS ba1e, ba2.email AS ba2e FROM blurt_analysis AS ba1 JOIN blurt_analysis AS ba2
	ON ba1.topicid = ba2.topicid AND ba1.email != ba2.email AND ba1.email NOT IN
		(SELECT follower FROM follow WHERE followee = ba2.email)) AS t1
ON u1.email = ba1e AND u2.email = ba2e;

/*Query 8:
 */
SELECT DISTINCT f1.follower, f1.followee, f2.followee FROM follow AS f1 JOIN follow AS f2 
	ON f1.followee = f2.follower AND f1.follower != f2.followee WHERE f2.followee NOT IN
	(SELECT followee FROM follow WHERE follower = f1.follower);
    
/*Query 9
 */
SELECT topicid, name, location, COUNT(*) AS counter, AVG(sentiment) AS avgSent FROM blurt NATURAL INNER JOIN blurt_analysis NATURAL INNER JOIN
	(SELECT id AS topicid, description AS NAME FROM topic) AS join1
GROUP BY location, topicid
HAVING avgSent < 0;