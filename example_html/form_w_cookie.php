
<?php
$name = null;
//permet si logout est activé de supprimer le cookie
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
	setcookie('User', $_POST['name']);
	$name = htmlspecialchars($_POST['name']);
}
?>

<?php if ($nom): ?>
	<p>Hello <?php htmlentities($nom); ?> !</p>
	<a href="form_w_cookie.php?action=logout">Log out</a>
<?php else: ?>
	<form action="" method="post">
	<div class "form-group">
		<input class="form-control" name="name" placeholder="Enter your name please.">
	</div>
	<button class="btn btn-primary"> Log in </button>
</form>
<?php endif; ?>