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
	<form>
	<br><button formaction="index.py" type="submit">Back to Index</button>
	<br><button type="submit" formaction="addartist.py">Refresh</button>
	</form>
	""")

print("""
	<form method="post">
		<br><input type="text" name="id" placeholder="Artist ID" required>
		<br><input type="text" name="name" placeholder="Name" required>
		<br><input type="text" name="birthyear" placeholder="Birth Year">
		<br><input type="text" name="country" placeholder="Country">
		<br><input type="text" name="desc" placeholder="Description">
		<br><input type="submit" value="Upload">
	</form>
	""")

if form.getvalue("name") is not None:
	cur.execute("INSERT INTO artist(artist_id,name,birth_year,country,description) VALUES (%s,%s,%s,%s,%s)", (form.getvalue("id"),form.getvalue("name"),form.getvalue("birthyear"),form.getvalue("country"),form.getvalue("desc")))
	db.commit()

cur.execute("SELECT * FROM artist")
artists = cur.fetchall()

print("""
	<form method="get">
		<br><input type="text" name="searchcountry" placeholder="Enter Country">
		<br><button type="submit" formaction="findartistcountry.py">Find Artist By Country</button>
		<br><input type="text" name="searchyear" placeholder="Enter Birth Year">
		<br><button type="submit" formaction="findartistyear.py">Find Artist By Birth Year</button>
	</form>

	<H3>List of Artists</H3>
	""")

for row in artists:
	print("""Artist(ID,Name): {0}, {1}
		<br>Birth Year: {2}
		<br>Country: {3}
		<br>Description {4}
		<br>
		<br>
		""".format(row[0],row[1],row[2],row[3],row[4]))

print("</center>")