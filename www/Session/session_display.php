<?php
    session_start();
    // echo "<h3> PHP List All Session Variables</h3>";
    // foreach ($_SESSION as $key=>$val)
    // echo $key." ".$val."<br/>";

	echo '<pre>' . print_r($_SESSION, TRUE) . '</pre>';

?>
<body>
	<div class="text">
            <h1><a href="/">Back to Index</a></h1>
        
    </section>
</body>


</html>