<?php

if (!session_id())
{
	session_start();
	session_regenerate_id(true);
	$_SESSION["session"] = "new";
}

?>

<br><br>
<br><br>

<!DOCTYPE html>
<html lang="fr">
<head>
	<center>
		<div class="text">
    	        <h1><a href="/">
					<button class="btn btn-primary w3-black w3-padding-large w3-large w3-margin-top"> Back to Index </button>
				</a></h1>
				<div class="text">
				>>Session has been created<<</p>
				<h1><a href="session_display.php">
					<button class="btn btn-primary w3-red w3-padding-large w3-large w3-margin-top"> Session Display </button>
				</a></h1>
				<h1><a href="set_session.php">
					<button class="btn btn-primary w3-red w3-padding-large w3-large w3-margin-top"> Set Session </button>
				</a></h1>
			
		<div class="img">
			<img src="https://media.giphy.com/media/cT5gKT412jHqw/giphy.gif"  width="255"></img>
			<br><br>
		<div class="text">
			<h1><a href="session_deconnexion.php">
			<button class="btn btn-primary w3-black w3-padding-large w3-large w3-margin-top"> Log out </button>
			</a></h1>
	</center>

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
				<a href="../Upload/upload.html" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-white">Upload</a>
				<a href="../Coockie/form_w_cookie.php" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-hover-white">Cookie</a>
				<a href="../Session/session_start.php" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-white">Session</a>
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
	</body>
</html>