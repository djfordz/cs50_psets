<?php
/**
 * Created by PhpStorm.
 * User: djfordz
 * Date: 12/20/14
 * Time: 7:59 PM
 */
    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if($_POST["username"] === false || $_POST["password"] === false || $_POST["confirmation"] != $_POST["password"])
        {
            apologize("The information you entered was incorrect. Please try again.");
        }
        else
        {
            query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt
            ($_POST["password"]));
            $rows = query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
           $_SESSION["id"] = $id;
            if(isset($_SESSION['id']))
                header("location:index.php");
            exit();
        }
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>

