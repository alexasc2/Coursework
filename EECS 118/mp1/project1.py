import pymysql
import os

myname = "CHOI, ALEXANDER"
my2id = 18
db = pymysql.connect(host = 'localhost',
					 user = 'root',
					 passwd = 'alexanderchoi',
					 db = 'sample_python',
					 autocommit = True)	
if os.path.exists("output.txt"):
	os.remove("output.txt")
file1 = open("output.txt","w+")

try:
	#Problem 1
	with db.cursor() as cur:
		cur.execute("SELECT * FROM sample_python.question")
		results = cur.fetchall()
		print("question:",file=open("output.txt","a"))
		for row in results:
			print("{0},{1},{2}".format(row[0],row[1],row[2]),file=open("output.txt","a"))

	#Problem 2
	with db.cursor() as cur:
		cur.execute("SELECT * FROM sample_python.question WHERE name=%s",myname)
		myname, myA, myB = cur.fetchone()
		myresult = myA * myB + my2id

	#insert 
	with db.cursor() as cur:
		cur.execute("INSERT IGNORE INTO sample_python.result (name,id2d,result) VALUES (%s,%s,%s) ",(myname,my2id,myresult))
		db.commit()

	#Problem 3
	with db.cursor() as cur:
		cur.execute("SELECT name,result FROM sample_python.result WHERE name=%s",myname)
		thisname,thisresult = cur.fetchone()
		print("\nresult:",file=open("output.txt","a"))
		print("{}, {}".format(thisname,thisresult),file=open("output.txt","a"))
finally:
	db.close()

file1.close()