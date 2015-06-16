<section id="history" class="container">
    <table id="history">
        <thead class="head">
        <tr>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Action</th>
            <th>Price</th>
            <th>Total</th>
        </tr>
        </thead>
        <tbody class="body">
            <?php foreach($history as $h): ?>
                <tr>
                    <td><?= $h["time"]; ?></td>
                    <td><?= $h["symbol"]; ?></td>
                    <td><?= $h["name"]; ?></td>
                    <td><?= $h["shares"]; ?></td>
                    <td><?= $h["action"]; ?></td>
                    <td><?= number_format($h["price"], 2); ?></td>
                    <td><?= number_format(($h["price"] * $h["shares"]), 2); ?></td>
                </tr>
            <?php endforeach ?>
        </tbody>
    </table>


