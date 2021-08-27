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
	</form>
	<form method="post">
		<br><input type="text" name="name" placeholder="Name">
		<br><input type="text" name="birthyear" placeholder="Birth Year">
		<br><input type="text" name="country" placeholder="Country">
		<br><input type="text" name="desc" placeholder="Description">
		<br><input type="submit" value="Upload">
		<input type="hidden" name="inputartist" value=\""""+form.getvalue("inputartist")+"""\">
	</form>
	""")

if form.getvalue("name") is not None:
	cur.execute("UPDATE artist SET name=\"{0}\" WHERE artist_id=\"{1}\"".format(form.getvalue("name"),form.getvalue("inputartist")))
if form.getvalue("birth_year") is not None:
	cur.execute("UPDATE artist SET birth_year=\"{0}\" WHERE artist_id=\"{1}\"".format(form.getvalue("birthyear"),form.getvalue("inputartist")))
if form.getvalue("country") is not None:
	cur.execute("UPDATE artist SET country=\"{0}\" WHERE artist_id=\"{1}\"".format(form.getvalue("country"),form.getvalue("inputartist")))
if form.getvalue("desc") is not None:
	cur.execute("UPDATE artist SET description=\"{0}\" WHERE artist_id=\"{1}\"".format(form.getvalue("desc"),form.getvalue("inputartist")))