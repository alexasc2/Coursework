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

id = form.getvalue("galleryvalue")

print("""
	<center>
	<form action="showgallery.py">
		<br><button type="submit" name="buttonvalue" value=\""""+id+"""\">Back to Gallery</button>
	</form>
	<form method="post">
		<br><input type="text" name="new_g_name" placeholder="name">
		<br><input type="text" name="new_g_desc" placeholder="description">
		<br><input type="submit" value="Update">
	</form>
	""")

if form.getvalue("new_g_name") is not None:
	cur.execute("UPDATE gallery SET name=\"{0}\" WHERE gallery_id={1}".format(form.getvalue("new_g_name"),int(id)))
	db.commit()
if form.getvalue("new_g_desc") is not None:
	cur.execute("UPDATE gallery SET description=\"{0}\" WHERE gallery_id={1}".format(form.getvalue("new_g_desc"),int(id)))
	db.commit()

print("</center>")