<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="symbol" placeholder="stock symbol" type="text" min="0" required>
        </div>
        <div class="form-group">
            <input class="form-control" name="quantity" placeholder="# of shares" type="number" required>
            <input type="submit" name="sell" placeholder="sell">
        </div>
    </fieldset>
</form>

