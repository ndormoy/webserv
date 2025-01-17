<?php

// A list of permitted file extensions
$allowed = array('png', 'jpg', 'gif','zip');

if(isset($_FILES['upl']) && $_FILES['upl']['error'] == 0){

	$extension = pathinfo($_FILES['upl']['name'], PATHINFO_EXTENSION);

	if(!in_array(strtolower($extension), $allowed)){
		echo '{"status":"error"}';
		exit;
	}

	if(move_uploaded_file($_FILES['upl']['tmp_name'], 'uploads/'.$_FILES['upl']['name'])){
		echo '{"status":"success"}';
		exit;
	}
}

echo '{"status":"error"}';
exit;

?>
<!DOCTYPE html>
<html>

	<head>
		<meta charset="utf-8"/>
		<title>Mini Ajax File Upload Form</title>

		<!-- Google web fonts -->
		<link href="http://fonts.googleapis.com/css?family=PT+Sans+Narrow:400,900" rel='stylesheet' />

		<!-- The main CSS file -->
		<link href="assets/css/style.css" rel="stylesheet" />

		<title>Webserv ndormoy mamaurai gmary</title>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
		<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Lato">
		<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Montserrat">
		<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
		<style>
		body,h1,h2,h3,h4,h5,h6 {font-family: "Lato", sans-serif}
		.w3-bar,h1,button {font-family: "Montserrat", sans-serif}
		.fa-anchor,.fa-coffee {font-size:200px}
		</style>
	
	</head>

	<body>
			<!-- Navbar -->
			<div class="w3-top">
			  <div class="w3-bar w3-red w3-card w3-left-align w3-large">
				<a class="w3-bar-item w3-button w3-hide-medium w3-hide-large w3-right w3-padding-large w3-hover-white w3-large w3-red" href="javascript:void(0);" onclick="myFunction()" title="Toggle Navigation Menu"><i class="fa fa-bars"></i></a>
				<a href="../index.html" class="w3-bar-item w3-button w3-padding-large w3-hover-white">Home</a>
				<a href="../Download/download.html" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-white">Download</a>
				<a href="../Upload/upload.html" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-white">Upload</a>
				<a href="../Coockie/form_w_cookie.php" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-white">Cookie</a>
				<a href="../Session/session_start.php" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-white">Session</a>
			  </div>
		
			  <!-- Navbar on small screens -->
			  <div id="navDemo" class="w3-bar-block w3-white w3-hide w3-hide-large w3-hide-medium w3-large">
				<a href="../index.html" class="w3-bar-item w3-button w3-padding-large">Home</a>
				<a href="../Download/download.html" class="w3-bar-item w3-button w3-padding-large">Download</a>
				<a href="../Upload/upload.html" class="w3-bar-item w3-button w3-padding-large">Upload</a>
				<a href="../Coockie/form_w_cookie.php" class="w3-bar-item w3-button w3-padding-large">Cookie</a>
				<a href="../Session/session_start.php" class="w3-bar-item w3-button w3-padding-large">Session</a>
			  </div>
			</div>
	<center>

		
		<form id="upload" method="post" action="#" enctype="multipart/form-data">
			<div id="drop">
				Drop Files Here

				<a>Browse</a>
				<!-- <input type="file" name="upl" multiple /> -->
				<input type="file" name="filename" value="">
	 			<input type="submit" name="chargement" value="charger le fichier">
			</div>

			<ul>
				<!-- The file uploads will be shown here -->
			</ul>

		</form>

		<!-- <p>Click on the "Choose File" button to upload a file:</p>
	<form method="POST" action="#" enctype="multipart/form-data">
	  <input type="file" name="filename" value="">
	  <input type="submit" name="chargement" value="charger le fichier">
	</form> -->

		<!-- JavaScript Includes -->
		<!-- <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
		<script src="assets/js/jquery.knob.js"></script> -->

		<!-- jQuery File Upload Dependencies -->
		<!-- <script src="assets/js/jquery.ui.widget.js"></script>
		<script src="assets/js/jquery.iframe-transport.js"></script>
		<script src="assets/js/jquery.fileupload.js"></script> -->
		
		<!-- Our main JS file -->
		<!-- <script src="assets/js/script.js"></script> -->
	</center>
	</body>
</html>
