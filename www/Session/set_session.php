<?php
	session_start();
?>

<!DOCTYPE html>
<html>

<head>
	<div class="text">
            <h1><a href="/">Back to Index</a></h1>
	
<body>
<form method="post">
		<label for="fname">First name:</label>
		<input type="text" id="fname" name="fname"><br><br>
		<label for="lname">Last name:</label>
		<input type="text" id="lname" name="lname"><br><br>
		<input type="submit" value="Submit">
</form>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
  // collect value of input field
	$_SESSION[$_POST['fname']] = $_POST["fname"];
	$_SESSION[$_POST['lname']] = $_POST['lname'];
  echo "<br>";
  if (empty($_POST['fname'])) {
    echo "\"First Name\" is empty";
	echo "<br>";
  } else {
	echo $_POST['fname'];
	echo " --> is set";
	echo "<br>";
  }
  if (empty($_POST['lname'])) {
    echo "\"Last Name\" is empty";
  } else {
	echo $_POST['lname'];
	echo " --> is set";
	echo "<br>";
  }
}
?>

</body>
</html>
