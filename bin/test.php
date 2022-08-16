<?php
session_start();

$db = mysqli_connect('localhost', 'root', '', 'database');

if (isset($_POST['connection'])) {
	$pseudo = htmlspecialchars($_POST['pseudo']);
	$mot_de_passe = htmlspecialchars($_POST['mot_de_passe']);

	//On verifie si l'utilisateur existe

	$mot_de_passe = md5($mot_de_passe);
	$sql_pseudo = "SELECT * FROM users WHERE pseudo='$pseudo'";
	$sql_mdp = "SELECT * FROM users WHERE mot_de_passe='$mot_de_passe'";

	$res_pseudo = mysqli_query($db, $sql_pseudo);
	$res_mdp = mysqli_query($db, $sql_mdp);

	$row = mysqli_fetch_array($res_pseudo);

	//Si il y a bien un utilisateur et que son mdp corresponds on se connecte

	if (mysqli_num_rows($res_pseudo) == 1 && $row['mot_de_passe'] == $mot_de_passe) {
		$_SESSION['pseudo'] = $pseudo;
		$results = mysqli_query($db, "SELECT * FROM `users` WHERE pseudo='$pseudo'");
		$row = mysqli_fetch_array($results);
		if ($row['admin'] == 1) {
			$_SESSION['admin'] = 1;
		}
		$_SESSION['id'] = $row['id'];
		$_SESSION['success'] = "Vous etes connecter";
		header('location: index.php');
	} else {
		$error = "Mot de passe ou pseudo incorrect";
	}
}

?>
<!DOCTYPE html>
<html>

<head>
	<title>Connection</title>
</head>

<body>

	<?php include('menu.php') ?>


	<div class="header">
		<h2>Connection</h2>
	</div>

	<div class="contenu">
		<form method="post" action="login.php">
			<div class="input">
				<p>Pseudo</p>
				<input class="log" type="text" name="pseudo" placeholder="Mon Pseudo" required>
			</div>
			<div class="input">
				<p>Mot de Passe</p>
				<input type="password" class="log" name="mot_de_passe" placeholder="Mot de Passe" required>
			</div>


			<? if (isset($error)) {
				echo "<span style=\"color:red\"><strong>" . $error . "</strong></span>";
			}
			?>

			<div class="input">
				<button type="submit" class="button" name="connection">Connecter vous</button>
			</div>


	</div>
	</form>
	<? include('darkmode.php'); ?>
</body>

</html>
