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
	<br><button formaction="addartist.py" type="submit">Back to Artists</button>
	</form>
	""")
cur.execute("SELECT * FROM artist WHERE country=\"{0}\"".format(form.getvalue("searchcountry")))
artists = cur.fetchall()

for row in artists:
	print("""Artist(ID,Name): {0}, {1}
		<br>Birth Year: {2}
		<br>Country: {3}
		<br>Description {4}
		<br>
		<br>
		""".format(row[0],row[1],row[2],row[3],row[4]))