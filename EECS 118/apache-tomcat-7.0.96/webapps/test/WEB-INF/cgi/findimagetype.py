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
	</form>
	""")
cur.execute("SELECT * FROM detail WHERE type=\"{0}\"".format(form.getvalue("searchtype")))
details = cur.fetchall()

for row in details:
	