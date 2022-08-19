<?php

if (!session_id())
{
	session_start();
	session_regenerate_id(true);
	$_SESSION["session"] = "new";
}

?>

<!DOCTYPE html>
<html lang="fr">
<head>
	<div class="text">
            <h1><a href="/">Back to Index</a></h1>
		<div class="text">
		>>Session has been created<<</p>
	<div class="img">
		<img src="https://media.giphy.com/media/cT5gKT412jHqw/giphy.gif"  width="255"
		<br><br>
	<div class="text">
		<h1><a href="session_deconnexion.php">Log out</a></h1>
</head>

</body>
</html>