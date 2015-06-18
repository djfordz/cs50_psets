<?php
/**
 * Created by PhpStorm.
 * User: djfordz
 * Date: 5/24/15
 * Time: 10:09 AM
 */

require(__DIR__ . "/includes/config.php");

if($_SERVER["REQUEST_METHOD"] == "POST") {

    $cash = $_POST["amount"];

    query("UPDATE users SET cash = cash + ? WHERE id = ?", $cash, $_SESSION["id"]);

    render("cash.php", ["title" => "Account Updated!", "cash" => $cash]);
} else {
    render("cash_form.php", ["title" => "Add Cash"]);
}

