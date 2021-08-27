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
		<br><button formaction="showgallery.py" type="submit">Back to Gallery</button>
		<br><button type="submit" formaction="showdetails.py">Refresh</button>
		<input type="hidden" name="buttonvalue" value=\""""+id+"""\">
	</form>
	""")

cur.execute("SELECT * FROM image WHERE image_id=%s",form.getvalue("imagevalue"))
imagedata = cur.fetchone()
cur.execute("SELECT * FROM detail WHERE image_id=%s",form.getvalue("imagevalue"))
detaildata = cur.fetchone()
cur.execute("SELECT * FROM artist WHERE artist_id=%s",imagedata[4])
artistdata = cur.fetchone()

print("""
	<br>Title: {0}
	<br>Artist: {1}
	<br>Year: {2}
	<br>Type: {3}
	<br>Width: {4}
	<br>Height: {5}
	<br>Location: {6}
	<br>Description: {7}

	""".format(imagedata[1],artistdata[1],detaildata[2],detaildata[3],detaildata[4],detaildata[5],detaildata[6],detaildata[7]))
print("""
	<form>
		<br><button formaction="showartist.py">Artist Details</button>
		<input type="hidden" name="buttonvalue" value=\""""+id+"""\">
		<input type="hidden" name="imagevalue" value=\""""+form.getvalue("imagevalue")+"""\">
	</form>
	""")