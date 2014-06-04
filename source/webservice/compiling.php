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
	$param_id_json = $id."param.json";
	$challange_id_json = $id."challange.json";

	// create param list.json
	$param_file_json = $param_id_json;
	$param_file_handling = fopen($dir_json.$param_file_json, 'w') or die("UPS! Something went wrong!");
	fwrite($param_file_handling, $param_list);
	fclose($param_file_handling);

	// create challange .json
	$challange_file_json = $challange_id_json;
	$challange_file_handling = fopen($dir_json.$challange_file_json, 'w') or die("UPS! Something went wrong!");
	fwrite($challange_file_handling, $challange);
	fclose($challange_file_handling);

	// make output
    $output = shell_exec("../main.output -p -s ".$dir_json.$param_file_json." ".$dir_json.$challange_file_json." /var/www/source/webservice/tmp/xml/".$id."GRID.xml"." /var/www/source/webservice/tmp/xml/".$id."LAB.xml"." /var/www/source/webservice/tmp/xml/".$id."PARAM.xml"." /var/www/source/webservice/tmp/xml/".$id."URDF.xml");

    if($output){
    	echo $output;
    	echo "n";
    }else{
    	// read param list.json
		$param_file_xml = $param_id_xml;
		$dir_xml = $dir."xml/";
		$param_file_handling = fopen($dir_xml.$param_file_xml, 'r') or die("UPS! Something went wrong!");
		$data = fread($param_file_handling, filesize($dir_xml.$param_file_xml));
		fclose($param_file_handling);

		// create challange .json
		$challange_file = $challange_id_xml;
		$challange_file_handling = fopen($dir_xml.$challange_file, 'r') or die("UPS! Something went wrong!");
		$data = fread($challange_file_handling, filesize($dir_xml.$challange_file));
		fclose($challange_file_handling);

    	echo "aqui";
    	echo $output;
    }

    // delete files
    //unlink($dir_json.$param_file_json);
    //unlink($dir_json.$challange_file_json);
?>