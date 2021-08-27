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
		<br><button formaction="showgallery.py" name="buttonvalue" value=\""""+id+"""\" type="submit">Back to Gallery</button>
		<br><button type="submit" formaction="addimage.py" name="buttonvalue" value=\""""+id+"""\">Refresh</button>
	</form>
	""")

print("""
	<form method="get">
		<input type="url" name="imageurl" placeholder="URL" required>
		<br><input type="text" name="imagetitle" placeholder="Image Title">
		<br><input type="text" name="imageartist" placeholder="Image Artist ID" required>
		<br><input type="text" name="imageyear" placeholder="Image Year">
		<br><input type="text" name="imagetype" placeholder="Image Type">
		<br><input type="text" name="imagewidth" placeholder="Image Width">
		<br><input type="text" name="imageheight" placeholder="Image Height">
		<br><input type="text" name="imagelocation" placeholder="Image Location">
		<br><input type="text" name="imagedescription" placeholder="Image Description">
		<br><input type="submit" value="Upload">
	</form>
	""")

cur.execute("SELECT * FROM artist")
artists = cur.fetchall()

for row in artists:
	print("""
		Artist(ID,Name): {0}, {1}
		<br>Birth Year: {2}
		<br>Country: {3}
		<br>Description {4}
		<br>
		<br>
		""".format(row[0],row[1],row[2],row[3],row[4]))


if form.getvalue("imageurl") is not None:
	cur.execute("INSERT IGNORE INTO image(title,link,gallery_id,artist_id) VALUES (%s,%s,%s,%s)", (form.getvalue("imagetitle"),form.getvalue("imageurl"),id,form.getvalue("imageartist")))
	cur.execute("SELECT image_id FROM image WHERE link=\"{0}\"".format(form.getvalue("imageurl")))
	imageid = cur.fetchone()
	cur.execute("UPDATE image SET detail_id=\"{0}\" WHERE image_id=\"{1}\"".format(imageid[0],imageid[0]))
	cur.execute("INSERT IGNORE INTO detail(detail_id,image_id,year,type,width,height,location,description) VALUES (%s,%s,%s,%s,%s,%s,%s,%s)",(imageid[0],imageid[0],form.getvalue("imageyear"),form.getvalue("imagetype"),form.getvalue("imagewidth"),form.getvalue("imageheight"),form.getvalue("imagelocation"),form.getvalue("imagedescription")))
