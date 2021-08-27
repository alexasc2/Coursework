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
send = str(form.getvalue("imagevalue"))
print("""
		<form method="post">
		<br><button formaction="showgallery.py" name="buttonvalue" value=\""""+id+"""\" type="submit">Back to Gallery</button>
		<br><button type="submit" formaction="editimage.py" name="buttonvalue" value=\""""+id+"""\">Refresh</button>
			<input type="hidden" name="imagevalue" value=\""""+send+"""\">
	</form>
	""")

print("""
	<form method="post">
		<input type="url" name="imageurl" placeholder="URL">
		<br><input type="text" name="imagetitle" placeholder="Image Title">
		<br><input type="text" name="imageartist" placeholder="Image Artist ID">
		<br><input type="text" name="imageyear" placeholder="Image Year">
		<br><input type="text" name="imagetype" placeholder="Image Type">
		<br><input type="text" name="imagewidth" placeholder="Image Width">
		<br><input type="text" name="imageheight" placeholder="Image Height">
		<br><input type="text" name="imagelocation" placeholder="Image Location">
		<br><input type="text" name="imagedescription" placeholder="Image Description">
		<br><input type="submit" value="Update Image">
		<input type="hidden" name="imagevalue" value=\""""+send+"""\">
		<input type="hidden" name="buttonvalue" value=\""""+id+"""\">
	</form>
	""")

if form.getvalue("imageurl") is not None:
	cur.execute("UPDATE image SET link=\"{0}\" WHERE image_id=\"{1}\"".format(form.getvalue("imageurl"),form.getvalue("imagevalue")))
if form.getvalue("imagetitle") is not None:
	cur.execute("UPDATE image SET title=\"{0}\" WHERE image_id=\"{1}\"".format(form.getvalue("imagetitle"),form.getvalue("imagevalue")))
if form.getvalue("imageartist") is not None:
	cur.execute("UPDATE image SET artist_id=\"{0}\" WHERE image_id=\"{1}\"".format(form.getvalue("imageartist"),form.getvalue("imagevalue")))
if form.getvalue("imageyear") is not None:
	cur.execute("UPDATE detail SET year=\"{0}\" WHERE image_id=\"{1}\"".format(form.getvalue("imageyear"),form.getvalue("imagevalue")))
if form.getvalue("imagetype") is not None:
	cur.execute("UPDATE detail SET type=\"{0}\" WHERE image_id=\"{1}\"".format(form.getvalue("imagetype"),form.getvalue("imagevalue")))
if form.getvalue("imagewidth") is not None:
	cur.execute("UPDATE detail SET width=\"{0}\" WHERE image_id=\"{1}\"".format(form.getvalue("imagewidth"),form.getvalue("imagevalue")))
if form.getvalue("imageheight") is not None:
	cur.execute("UPDATE detail SET height=\"{0}\" WHERE image_id=\"{1}\"".format(form.getvalue("imageheight"),form.getvalue("imagevalue")))
if form.getvalue("imagelocation") is not None:
	cur.execute("UPDATE detail SET location=\"{0}\" WHERE image_id=\"{1}\"".format(form.getvalue("imagelocation"),form.getvalue("imagevalue")))
if form.getvalue("imagedescription") is not None:
	cur.execute("UPDATE detail SET description=\"{0}\" WHERE image_id=\"{1}\"".format(form.getvalue("imagedescription"),form.getvalue("imagevalue")))
