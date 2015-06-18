<?php

    // configuration
    require(__DIR__ . "/includes/config.php"); 

    // log out current user, if any
    logout();

    // redirect user
    redirect("/");

?>
