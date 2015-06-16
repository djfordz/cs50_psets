<?php
/**
 * Created by PhpStorm.
 * User: djfordz
 * Date: 5/23/15
 * Time: 3:01 AM
 */

print("Congratulations! You have sold " . $quantity . " shares of " . strtoupper($stock["symbol"]) . " at $" . number_format($stock["price"], 2) ." per share. For a total of
$" . number_format(($stock["price"] * $quantity), 2) );