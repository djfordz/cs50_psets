<form action="cash.php" method="post">
    <fieldset>
        <div class="form-group">
            <h4>Please enter the amount you wish to add.</h4>
            <h5>The maximum amount per transaction is $10,000</h5>
            <input autofocus class="form-control" name="amount" placeholder="$1 - $10000" type="number" min="1" max="10000" required>
            <button type="submit" class="btn btn-primary">Add Cash</button>
        </div>
    </fieldset>
</form>
