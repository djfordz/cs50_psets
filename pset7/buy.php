<?php
/**
 * Created by PhpStorm.
 * User: djfordz
 * Date: 5/19/15
 * Time: 8:42 PM
 */

require(__DIR__ . "/includes/config.php");

if($_SERVER["REQUEST_METHOD"] == "POST") {

    if (!empty($_POST["symbol"]) || !empty($_POST["quantity"])) {

        $buy_symbol = strtoupper($_POST["symbol"]);
        $buy_shares = $_POST["quantity"];
        $user_stock = query("SELECT * FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $buy_symbol);
        $user_cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);

        if(empty($user_stock) ) {
            $user_shares = 0;
        } else {
            $user_shares = $user_stock[0]["shares"];
        }

        $stock = lookup($buy_symbol);

        if ($stock["name"] === "N/A") {
            apologize("Not a valid stock symbol.  Please input a valid stock symbol to buy.");
        } else {
            if($stock["price"] == "N/A") {
                apologize("Stock is not tradable on market.");
            } else {
                if ( preg_match("/^\d+$/", $_POST["quantity"]) === 1) {

                    if ($stock["price"] * $buy_shares > $user_cash[0]["cash"] || $user_cash[0]["cash"] < 1) {
                        apologize("you do not have enough money in your account to buy this stock!");
                    } else {
                        $user_shares += $buy_shares;
                        $user_cash[0]["cash"] -= $buy_shares * $stock["price"];

                        query("INSERT INTO stocks (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $buy_symbol, $user_shares);
                        query("UPDATE users SET cash = ? WHERE id = ?", $user_cash[0]["cash"], $_SESSION["id"]);

                        query("INSERT INTO history (id, symbol, shares, price, action) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], $buy_symbol, $buy_shares, $stock["price"], "BUY");

                        render("buy.php", ["title" => "Stocks Bought", "quantity" => $buy_shares, "stock" => $stock]);
                    }
                } else {
                    apologize("You must enter a whole number of shares greater than zero.");
                }
            }
        }
    }
} else {
    render("buy_form.php", ["title" => "Buy"]);
}
