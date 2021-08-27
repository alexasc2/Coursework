#secondary file from mp2_62339918.py
 
import cgi
#same FieldStorage from previous webpage
form = cgi.FieldStorage()

#Headers
print("Content-Type: text/html")
print()
print("<center><TITLE>MP2 Presentation Site</TITLE>")
print("<H2>Alexander Choi's Image Presenter</H2>")

#Button formatting
#each onclick event activates a Javascript function below to change images
print("""
<button style="height:30px;width:200px" onclick="ChangeButton1()">
First Image
</button>
<button style="height:30px;width:200px" onclick="ChangeButton2()">
Second Image
</button>
""")

#Image information, default to first image
print("<br><br>Title: ")
print("<div id='Title'>"+form.getvalue("image1name")+"</div>")
print("Artist: ")
print("<div id='Artist'>"+form.getvalue("image1artist")+"</div>")
print("Year: ")
print("<div id='Year'>"+form.getvalue("image1year")+"</div>")
print("Description: ")
print("<div id='Desc'>"+form.getvalue("image1desc")+"</div>")
print("<img src=\""+form.getvalue("image1_url")+"\" id='displayImg'>")

#script to change information/images per button press, uses FieldStorage information from previous webpage
print("""
	<script>
	function ChangeButton1()
	{
	document.getElementById('displayImg').src=\""""+form.getvalue("image1_url")+"""\";
	document.getElementById('Title').innerHTML=\""""+form.getvalue("image1name")+"""\";
	document.getElementById('Artist').innerHTML=\""""+form.getvalue("image1artist")+"""\";
	document.getElementById('Year').innerHTML=\""""+form.getvalue("image1year")+"""\";
	document.getElementById('Desc').innerHTML=\""""+form.getvalue("image1desc")+"""\";
	}
	function ChangeButton2()
	{
	document.getElementById('displayImg').src=\""""+form.getvalue("image2_url")+"""\";
	document.getElementById('Title').innerHTML=\""""+form.getvalue("image2name")+"""\";
	document.getElementById('Artist').innerHTML=\""""+form.getvalue("image2artist")+"""\";
	document.getElementById('Year').innerHTML=\""""+form.getvalue("image2year")+"""\";
	document.getElementById('Desc').innerHTML=\""""+form.getvalue("image2desc")+"""\";
	}
	</script></center>
""")