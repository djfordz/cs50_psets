<?php
/**
 * Created by PhpStorm.
 * User: djfordz
 * Date: 5/19/15
 * Time: 8:42 PM
 */

require("../includes/config.php");

if($_SERVER["REQUEST_METHOD"] == "POST") {
    if(!empty($_POST["symbol"]) || !empty($_POST["quantity"])) {
        $sell_symbol = strtoupper($_POST["symbol"]);
        $sell_shares = $_POST["quantity"];
        $user_shares = query("SELECT shares FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        $user_cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $stock = lookup($sell_symbol);

        if(!empty($user_shares[0]["shares"])) {
            if($user_shares[0]["shares"] >= $sell_shares) {
                $user_shares[0]["shares"] -= $sell_shares;
                $user_cash[0]["cash"] += $sell_shares * $stock["price"];

                query("UPDATE stocks SET shares = ? WHERE id = ? AND symbol = ?", $user_shares[0]["shares"], $_SESSION["id"], $sell_symbol);
                query("UPDATE users SET cash = ? WHERE id = ?", $user_cash[0]["cash"], $_SESSION["id"]);

                query("INSERT INTO history (id, symbol, shares, price, action) VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], $sell_symbol, $sell_shares, $stock["price"], "SELL");

                $shares = query("SELECT shares FROM stocks WHERE id = ?", $_SESSION["id"]);
                if($shares[0]["shares"] === 0) {
                    query("DELETE FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
                }
            } else {
                apologize("You do not own that many shares!");
            }
            render("sell.php",["title" => "Stocks Sold", "quantity" => $sell_shares, "stock" => $stock]);
        } else {
            apologize("the symbol entered is either not valid or not owned by you.  Please enter a valid stock symbol which you own.");
        }
    } else {
        apologize("You must enter a symbol and number of shares to continue");
    }
} else {
    render("sell_form.php", ["title" => "Sell"]);
}