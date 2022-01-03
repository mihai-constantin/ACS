<?php
  $operation = $_POST["operation"];
  $operator1 = $_POST["operator1"];
  $operator2 = $_POST["operator2"];
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