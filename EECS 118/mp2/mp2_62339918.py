#Alexander Choi's mp2 submission
#UCI ID: 62339918
#Fully functional, requires both mp2_62339918.py and mp2_62339918_part2.py to run 

import cgi

#title,formatting, and initializations
form = cgi.FieldStorage()
print("Content-Type: text/html")
print()
print("<center><TITLE>MP2 Upload Site</TITLE>")
print("<H2>Alexander Choi's Image Uploader</H2>")
#Instructions subtitle
print("Enter the URL for two images and their names, artist, year, and brief description.")

#Main HTML query form
#Sends data to mp2_62339918_part2.py for processing/display on a new webpage
print ("""
<body> 
<form method="post" action="mp2_62339918_part2.py" id="formID">
	<p><input type ="url"  name="image1_url" 	id="image1_url" 	placeholder="Input Image 1" required> 
	<br><input type="text" name="image1name" 	id="image1name" 	placeholder="Name" required>
	<br><input type="text" name="image1artist" 	id="image1artist"	placeholder="Artist" required>
	<br><input type="text" name="image1year" 	id="image1year"  	placeholder="Year" required>
	<br><input type="text" name="image1desc" 	id="image1desc"		placeholder="Description" size="50" required>
	</p>
</body>
<body>
	<p><input type ="url"  name="image2_url" 	id="image2_url" 	placeholder="Input Image 2" required>
	<br><input type="text" name="image2name" 	id="image2name" 	placeholder="Name" required>
	<br><input type="text" name="image2artist" 	id="image2artist" 	placeholder="Artist" required>
	<br><input type="text" name="image2year"	id="image2year"  	placeholder="Year" required>
	<br><input type="text" name="image2desc"	id="image2desc"	 	placeholder="Description" size="50" required>
	</p><input type ="submit" value="Upload">
</form>
</body>
</center>
""")