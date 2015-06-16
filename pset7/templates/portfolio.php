<section id="portfolio" class="container">
    <table id="main">
        <thead class="head">
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total</th>
        </tr>
        </thead>
        <tbody class="body">
            <tr>
                <td><?php print("CASH"); ?></td>
                <td><?php print("Cash in account"); ?></td>
                <td></td>
                <td></td>
                <td><?= number_format($user[0]["cash"], 2); ?></td>
            </tr>
            <?php foreach($portfolio as $folio): ?>
                <tr>
                    <td><?= $folio["symbol"]; ?></td>
                    <td><?= $folio["name"]; ?></td>
                    <td><?= $folio["shares"]; ?></td>
                    <td><?= number_format($folio["price"], 2); ?></td>
                </tr>
            <?php endforeach ?>
        </tbody>
    </table>

