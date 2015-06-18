<?php

    // configuration
    require(__DIR__ . "/includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if($_POST["username"] === false || $_POST["password"] === false || $_POST['password'] !== $_POST["confirmation"])
        {
            apologize("Incorrect information, please try again.");
        }
        else
        {
            session_start();
            query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
            $rows = query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            //$_SESSION = $id;
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