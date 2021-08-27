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

id = form.getvalue("buttonvalue")
print("<center>")
print("<title>MP3</title>")
print("""
	<head>
	<style>
	div.gallery{
		border: 1px solid;
		float: center;
		width: 180px;
	}

	div.gallery img{
		width: 100%;
		height: auto;
	}

	</style>
	</head>
	<form>
	<br><button formaction="showgallery.py" type="submit">Back to Gallery</button>
	<input type="hidden" name="buttonvalue" value=\""""+id+"""\">
	</form>
	""")
cur.execute("SELECT image_id FROM detail WHERE year=\"{0}\"".format(form.getvalue("searchyear")))
imageid = cur.fetchone()
cur.execute("SELECT * FROM image WHERE image_id=\"{0}\"".format(imageid))
images = cur.fetchall()

for row in images:
	print("""
			<div class = "gallery">
			<a target="_blank" href=\""""+row[2]+"""\">
				<img src=\""""+row[2]+"""\" width="600" height="400">
			</a>
		</div>
		""")