<?php

require "vendor/autoload.php";
$client = new MongoDB\Client();
$database = $client -> data;
$collection = $database -> quotes;


$result = $collection->find([]);
#foreach($result as $doc){
#	foreach($doc as $key=>$value){
#		if($key != "_id"){
#			echo "{$key}:{$value} <br>";
#		}
#	}
#}



#$customer = ["name"=>"john", "location"=>"Newark"];
#echo "<h1>".$customer["name"]."</h1>";
#$keys = array_keys($customer);
#$values = array_values($customer);
#foreach ($customer as $key=>$value){
#	echo "<h1>"."{$key}:{$value} <br>"."<h1>";
#}

?>
<!Doctype HTML>
<html>
<head>
<title>
	My Sample Page
</title>
</head>
<body>
<center><h1>Welcome, Hello</h1></center>
<table border=1>
<tr>
<th>
Quote
</th>
<th>
Author
</th>
</tr>
<?php
foreach($result as $doc){
	echo "<tr>";
        foreach($doc as $key=>$value){
                if($key != "_id"){
                        echo "<td>{$key}:{$value} </td>";
                }
	}
	echo "</tr>";
}
?>

</table>
</body>
</html>

