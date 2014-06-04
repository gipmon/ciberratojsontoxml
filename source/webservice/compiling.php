<?php
	$param_list = $_POST['param'];
	$challange = $_POST['challange'];

	// test if is json
	$ob_pl = json_decode($param_list);
	if($ob_pl === null){
		echo "param.json isn't a JSON file!";
		exit();
	}
	$ob_cl = json_decode($challange);
	if($ob_cl === null){
		echo "challange.json isn't a JSON file!";
		exit();
	}

	// create json files
	$dir = "tmp/";
	$dir_json = $dir."json/";
	$id = uniqid();
	$param_id = $id."param.json";
	$challange_id = $id."challange.json";

	// create param list.json
	$param_file = $param_id;
	$param_file_handling = fopen($dir_json.$param_file, 'w') or die("UPS! Something went wrong!");
	fwrite($param_file_handling, $param_list);
	fclose($param_file_handling);

	// create challange .json
	$challange_file = $challange_id;
	$challange_file_handling = fopen($dir_json.$challange_file, 'w') or die("UPS! Something went wrong!");
	fwrite($challange_file_handling, $challange);
	fclose($challange_file_handling);

	// make output
    $output = shell_exec("../main.output -o ".$dir_json.$param_file." ".$dir_json.$challange_file);

    if($output){
    	// open files

    }else{
    	echo $output;
    }

    // delete files
    unlink($dir_json.$param_file);
    unlink($dir_json.$challange_file);
?>