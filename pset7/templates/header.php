<!DOCTYPE html>

<html>

    <head>

        <link href="css/bootstrap.min.css" rel="stylesheet"/>
        <link href="css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <script src="/js/jquery-1.10.2.min.js"></script>
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

    </head>

    <body>

        <div class="container">
        <h4>This is a student site. If you would like to view the Staff's site, please visit <a href="https://finance.cs50.net">https://finance.cs50.net</a></h4>
            <div id="top">
                <div id="masthead" class="container">
                    <a href="/"><h1>C</h1><h1>$</h1><h1>50 Finance</h1></a>
                </div>
                <nav id="primary-nav" class="nav container">
                    <ul>
                        <li><a href="index.php">Portfolio</a></li>
                        <li><a href="quote.php">Quote</a></li>
                        <li><a href="buy.php">Buy</a></li>
                        <li><a href="sell.php">Sell</a></li>
                        <li><a href="history.php">History</a></li>
                        <li><a href="logout.php">Log Out</a></li>
                        <li><a href="cash.php">Add Cash</a></li>
                    </ul>
                </nav>
            </div>

            <div id="middle">
