<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];
   
    // search database for places matching $_GET["geo"]
    $places = query("SELECT * FROM places WHERE postal_code like ? OR place_name like ? OR admin_code1 like ? OR admin_name1 like ?","%" . $_GET["geo"] . "%", "%" . $_GET["geo"] . "%", "%" . $_GET["geo"] . "%", "%" . $_GET["geo"] . "%");


    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
