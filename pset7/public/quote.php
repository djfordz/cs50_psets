<?php

    // configuration
    require("../includes/config.php");

    // if form is not empty
    if(!empty($_POST["symbol"])) {

    	// lookup stock symbol.
        $stock = lookup($_POST["symbol"]);
					
    	if($stock["name"] == "N/A") {

    		apologize("invalid stock symbol. Please enter valid stock symbol");
    	}
    	else {
            if($stock["price"] == "N/A") {
                apologize("Stock is in bancruptcy and not tradable at this time.");
            } else {
                render("quote.php", ["stock" => $stock, "title" => "Quote"]);
            }
    		
    	}
    
    } else {
    	render("quote_form.php", ["title" => "Lookup Stock"]);
    }
 ?>