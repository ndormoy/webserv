<!DOCTYPE html>
<html>
	<head>
		<title>Upload</title>
		<meta charset="utf-8">
		<meta name="description" content="">
	</head>
<body>

	<!-- PHP -->
		<?php
			if(isset($_POST) && !empty($_POST)){
				?><pre><?php print_r($_POST); ?></pre><?php
				?><pre><?php print_r($_FILES); ?></pre><?php
				
				if($_FILES['file']['size'] > 1000000)
					echo 'File is too big';
				
				$extension = strrchr($_FILES['file']['name'], '.');
				if ($extension != '.jpg' && $extension != '.jpeg' && $extension != '.png' && $extension != '.gif')
					echo 'File is not an image';
				if($_FILES['file']['error'] == 0){
					$file_name = $_FILES['file']['name'];
					$file_tmp_name = $_FILES['file']['tmp_name'];
					$file_size = $_FILES['file']['size'];
					$file_type = $_FILES['file']['type'];
					$file_path = 'uploads/' . $file_name;
					
					if(move_uploaded_file($file_tmp_name, $file_path)){
						echo 'Uploaded successfully';
					} else {
						echo 'Error uploading file';
					}
				} else {
					echo 'Error uploading file';
				}
			}
		?>
	<!-- HTML -->
<p>Click on the "Choose File" button to upload a file:</p>
	<form method="POST" action="#" enctype="multipart/form-data">
	  <input type="file" name="filename" value="">
	  <input type="submit" name="chargement" value="charger le fichier">
	</form>

</body>
</html>