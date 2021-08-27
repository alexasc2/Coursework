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
form = cgi.FieldStorage()

print("Content-Type: text/html")
print()

id = form.getvalue("buttonvalue")

cur.execute("SELECT name, description FROM gallery WHERE gallery_id={}".format(int(id)))
gallery = cur.fetchone()

cur.execute("SELECT * FROM image WHERE gallery_id={}".format(int(id)))
images = cur.fetchall()
imagelength=str(len(images))
#image formatting
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
	""")

#back to index
print("""
	<center>
	<form>
		<br><button formaction="index.py" type="submit">Back to Index</button>
		<br><button type="submit" formaction="showgallery.py" name="buttonvalue" value=\""""+id+"""\">Refresh</button>
	</form>
	<H2>"""+gallery[0]+"""</H2>
	"""+gallery[1]+"""
	<br>Number of Images = """+imagelength+"""
	<form>
	<br><button type="submit" formaction="editgallery.py" name="galleryvalue" value=\""""+id+"""\">Edit Gallery</button>
	</form>
	""")

print("""
	<form method="get">
		<br><input type="text" name="searchtype" placeholder="Enter Type">
		<br><button type="submit" formaction="findimagetype.py">Find Image By Type</button>
		<br><input type="text" name="searchyear" placeholder="Enter Year">
		<br><button type="submit" formaction="findimageyear.py">Find Image By Year</button>
		<br><input type="text" name="searchartist" placeholder="Enter Artist">
		<br><button type="submit" formaction="findimageartist.py">Find Image By Artist Name</button>
		<br><input type="text" name="searchlocation" placeholder="Enter Location">
		<br><button type="submit" formaction="findimagelocation.py">Find Image By Location</button>
		<input type="hidden" name="buttonvalue" value=\""""+id+"""\">
	</form>
	""")

#add image to gallery
print("""
	<form method="get" action="addimage.py">
			<input type="hidden" name="buttonvalue" value=\""""+id+"""\">
		<br><input type="submit" value="Upload Image">
	</form>
	""")

for row in images:
	send=str(row[0])
	print("""
		<div class = "gallery">
			<a target="_blank" href=\""""+row[2]+"""\">
				<img src=\""""+row[2]+"""\" width="600" height="400">
			</a>
		</div>

		<form>
			<button type="submit" name="imagevalue" value=\""""+send+"""\" formaction="editimage.py">Edit Image</button>
			<button type="submit" name="deleteimage" value=\""""+send+"""\" formaction="showgallery.py">Delete Image</button>
			<br><button type="submit" formaction="showdetails.py">Image Details</button>
			<input type="hidden" name="buttonvalue" value=\""""+id+"""\">
			<input type="hidden" name="imagevalue" value=\""""+send+"""\">
		</form>
		""")

if form.getvalue("deleteimage") is not None:
	cur.execute("DELETE FROM detail WHERE detail_id=%s",form.getvalue("deleteimage"))
	cur.execute("DELETE FROM image WHERE image_id=%s",form.getvalue("deleteimage"))
	print("<script>document.GetElementsByName('deleteimage') = '';</script>")