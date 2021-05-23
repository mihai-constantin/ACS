<?php
  $operation = $_GET["operation"];
  $operator1 = $_GET["operator1"];
  $operator2 = $_GET["operator2"];
  switch($operation) {
	  case "addition":
	    echo $operator1+$operator2;
		break;
	  case "subtraction":
	  	echo $operator1-$operator2;
		break;
	  case "multiplication":
	  	echo $operator1*$operator2;
		break;
	  case "division":
	  	echo $operator1/$operator2;
		break;
	  default:
	    echo "No valid operation was specified";	
  }
?>