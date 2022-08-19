<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Form</title>
</head>
    <body>
        <?php if (empty($_POST['name']) || empty($_POST['email'])) { ?>
        <form action="form.php" method="post">
            <input type="text" name="name" placeholder="Name">
            <input type="text" name="email" placeholder="Email">
            <input type="submit" value="Submit">
        </form>
        <?php } else {?>
            <p>Hello <?php echo $_POST['name']; ?></p>
            <p>Your email is <?php echo $_POST['email']; ?></p>
        <?php } ?>
    </body>
</html>