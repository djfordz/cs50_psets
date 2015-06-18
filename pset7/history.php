<?php
/**
 * Created by PhpStorm.
 * User: djfordz
 * Date: 5/24/15
 * Time: 7:11 AM
 */

require(__DIR__ . "/includes/config.php");

$rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);

$history = [];

foreach($rows as $row) {
    $stock = lookup($row["symbol"]);
    $history[] = [
        "time" => $row["date"],
        "symbol" => $row["symbol"],
        "name" => $stock["name"],
        "price" => $row["price"],
        "shares" => $row["shares"],
        "action" => $row["action"],
    ];
}

render("history.php",["title" => "History", "history" => $history]);