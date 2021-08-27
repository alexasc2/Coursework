import cgi
import pymysql
import cgitb
cgitb.enable()
db = pymysql.connect(host = 'localhost',
					user = 'gallery',
				 	passwd = 'eecs118',
					db = 'gallery',
					autocommit = True)
form = cgi.FieldStorage()
cur = db.cursor()
print("Content-Type: text/html")
print()
print("<center>")
print("<title>MP3</title>")
print("""
	<form action="index.py">
		<br><button type="submit">Back to Index</button>
	</form>
	""")

print("""
	<form method="post">
		<br><input type="text" name="name" placeholder="name" required>
		<br><input type="text" name="desc" placeholder="description">
		<br><input type="submit" value="Upload">
	</form>
	""")

if form.getvalue("name") is not None:
	cur.execute("INSERT INTO gallery(name,description) VALUES (%s,%s) ",(form.getvalue("name"),form.getvalue("desc")))
	db.commit()
print("</center>")