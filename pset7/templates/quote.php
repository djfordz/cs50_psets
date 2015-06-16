
<div class="quote container">
	<ul>
			<li><?php print("Stock Symbol: <h4>" . $stock["symbol"] . "</h4>"); ?></li>
			<li><?php print("Company Name: <h4>" . $stock["name"] . "</h4>"); ?></li>
			<li><?php print("Price per share: <h4>$" . number_format($stock["price"], 2) . "</h4>"); ?></li>
	</ul>
</div>
