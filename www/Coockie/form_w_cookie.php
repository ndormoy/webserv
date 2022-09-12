<?php

session_start();

$name = null;
// permet si logout est activé de supprimer le cookie
// if (!empty($_POST['name']))
//     echo "is set";
// else
//     echo "is not set";

if (!empty($_GET['action']) && $_GET['action'] === 'logout') {
	unset($_COOKIE['User']);
 	setcookie('User', '', time() - 3600); // permet de supprimer le cookie avec une date dans le passe
}
if (!empty($_COOKIE['User']))
{
	$name = htmlspecialchars($_COOKIE['User']);
}
if (!empty($_POST['name']))
{
    $_SESSION['name'] = htmlspecialchars($_POST['name']);
	setcookie("User", $_POST['name'], time()+3600);
	$name = htmlspecialchars($_POST['name']);
}



?>
<br><br>
<br><br>

<?php
	echo "<center>";
	if ($name) { ?>
	
		<p>Hello <?php echo($name); ?> !</p>
		
		<a href="form_w_cookie.php?action=logout" >
			<button class="btn btn-primary w3-black w3-padding-medium w3-medium w3-margin-top"> Log out </button>
		</a>
	
<?php } else { ?>
	<form action="form_w_cookie.php" method="post">
	<div class "form-group">
		<input class="form-control" name="name" placeholder="Enter your name please.">
	</div>
	<button class="btn btn-primary w3-black w3-padding-medium w3-medium w3-margin-top" > Log in </button>
</form>
	</center>
<?php } ?>

<html>

	<head>
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
			<a href="../Coockie/form_w_cookie.php" class="w3-bar-item w3-button w3-hide-small w3-padding-large w3-white">Cookie</a>
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
	</body>
</html>