#Alexander Choi's mp3 submission
#UCI ID: 62339918
import cgi
import pymysql
import cgitb
cgitb.enable()
db = pymysql.connect(host = 'localhost',
					 user = 'gallery',
					 passwd = 'eecs118',
					 db = 'gallery',
					 autocommit = True)
cur = db.cursor()
cur.execute("SELECT gallery_id, name, description FROM gallery")
gallery = cur.fetchall()

print("Content-Type: text/html")
print()
print("<center>")
print("<title>MP3</title>")
print("<H2>Alexander Choi's Gallery Index</H2>")

print("""
<form action="addgallery.py">
	<button type="submit">Add a Gallery</button>
</form>
<form action="addartist.py">
	<button type="submit">Add and Look Up Artists</button>
</form>
<form action="editartist.py" method="post">
	<input type="text" name="inputartist" placeholder="Enter Valid Artist ID" required>
	<button type="submit">Edit Artist</button>
</form>
	""")

print("<body>")
for row in gallery:
	send = str(row[0])
	print("<br>Gallery Name:", row[1])
	print("<br>Gallery ID: ",row[0])
	print("<br>Gallery Description: ",row[2])
	print("""<form action='showgallery.py'>
				<button type="submit" name="buttonvalue" value=\""""+send+"""\">Show Gallery</button>
			 </form>
		""")

print("</center>")
print ("</body>")