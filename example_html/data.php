<?php
session_start();

/*session is started if you don't write this line can't use $_Session  global variable*/
if (isset($_POST["value"])) {
    $_SESSION['name']=$_POST["value"];
}

// output the new value
// echo $_POST["tag"] . "=" . $_POST["value"] . " is now set!";

/*it is my new session*/
// $_SESSION[$_POST["session2"]]=$updatedvalue;
/*session updated*/
echo "<br>" . $_SESSION['name'];
echo '<br><br><br /><a href="/">Back to HomePage</a>';
?>

<form action="data.php" method="post">
    <div class "form-group">
        <input class="form-control" name="value" placeholder="Enter your name please.">
    </div>
    <button class="btn btn-primary"> Log in </button>
</form>