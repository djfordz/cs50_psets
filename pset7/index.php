<?php

    // configuration
    require(__DIR__ . "/includes/config.php"); 

    $rows = query("SELECT * FROM stocks WHERE id = ?", $_SESSION["id"]);
    $user = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);

    $portfolio = [];

    foreach($rows as $row) {
    	$stock = lookup($row["symbol"]);
    	if($stock !== false) {
    		$portfolio[] = [
    			"name" => $stock["name"],
    			"price" => $stock["price"],
    			"shares" => $row["shares"],
    			"symbol" => $row["symbol"]
            ];
    	}
    }

    // render portfolio
    render("portfolio.php", ["portfolio" => $portfolio, "user" => $user, "title" => "Portfolio"]);

 //render("portfolio.php", ["title" => "Portfolio"]);
    ?>
