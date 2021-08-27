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

id = form.getvalue("buttonvalue")

print("""
		<form>
		<br><button formaction="showdetails.py" type="submit">Back to Details</button>
		<br><button type="submit" formaction="showartist.py">Refresh</button>
		<input type="hidden" name="buttonvalue" value=\""""+id+"""\">
		<input type="hidden" name="imagevalue" value=\""""+form.getvalue("imagevalue")+"""\">
	</form>
	""")

cur.execute("SELECT * FROM artist")
artists = cur.fetchone()

print("""
	Artist(ID,Name): {0},{1}
	<br>Birth Year: {2}
	<br>Country: {3}
	<br>Description {4}
	""".format(artists[0],artists[1],artists[2],artists[3],artists[4]))