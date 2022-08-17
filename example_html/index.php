<?php
session_start();

if (!isset($_SESSION['pseudo'])) {
	header('location: login.php');
}

if (isset($_GET['not_find'])) {
	$_SESSION['success'] = 'Pas de resultat';
}
?>

<!DOCTYPE html>
<html>

<head>
	<title>Accueil</title>
</head>

<body>

	<?php include('menu.php') ?>


	<?php if (isset($_SESSION['success'])) { ?>
		<div class="success">
			<h3>
				<?php
				echo "<div class=\"contenu\"><p>" . $_SESSION['success'] . "<p></div>";
				unset($_SESSION['success']);
				?>
			</h3>
		</div>
	<?php } ?>
	<div class="header">
		<p>Bonjour <strong><?php echo $_SESSION['pseudo']; ?></strong></p>
	</div>
	<?php
	$location = "";
	include('file.php');
	?>
	<?php include('darkmode.php'); ?>
</body>

</html>