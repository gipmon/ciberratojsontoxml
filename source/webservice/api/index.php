<?php
	if(isset($_POST['param']) && isset($_POST['challange'])){
		$param_list = $_POST['param'];
		$challange = $_POST['challange'];
	}else{
		echo json_encode(array("response_type" => "error", "val" => "You should pass the parameter param and challange!"));
		exit();
	}


	// test if is json
	$ob_pl = json_decode($param_list);
	if($ob_pl === null){
		echo json_encode(array("response_type" => "error", "val" => "param.json isn't a JSON file!"));
		exit();
	}
	$ob_cl = json_decode($challange);
	if($ob_cl === null){
		echo json_encode(array("response_type" => "error", "val" => "challange.json isn't a JSON file!"));
		exit();
	}

	// create json files
	$dir = "../tmp/";
	$dir_json = $dir."json/";
	$dir_xml = $dir."xml/";
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
	$grid_xml_output = $dir_xml.$id."GRID.xml";
	$lab_xml_output = $dir_xml.$id."LAB.xml";
	$param_xml_output = $dir_xml.$id."PARAM.xml";
	$urdf_xml_output = $dir_xml.$id."URDF.xml";

	$command = "../main.output -o -s ".$dir_json.$param_file_json." ".$dir_json.$challange_file_json." ".$grid_xml_output." ".$lab_xml_output." ".$param_xml_output." ".$urdf_xml_output;
    $output = shell_exec($command);

	echo json_encode(array("response_type" => "error", "val" => $command));
	exit();

    if($output){
		echo json_encode(array("response_type" => "error", "val" => str_replace("tmp/json/".$id, "", $output)));
    }else{
		$grid_file_handling = fopen($grid_xml_output, 'r') or die("UPS! Something went wrong!");
		$array['grid_output'] = fread($grid_file_handling, filesize($grid_xml_output));
		fclose($grid_file_handling);

		$lab_file_handling = fopen($lab_xml_output, 'r') or die("UPS! Something went wrong!");
		$array['lab_output'] = fread($lab_file_handling, filesize($lab_xml_output));
		fclose($lab_file_handling);

		$param_file_handling = fopen($param_xml_output, 'r') or die("UPS! Something went wrong!");
		$array['param_output'] = fread($param_file_handling, filesize($param_xml_output));
		fclose($param_file_handling);

		$urdf_file_handling = fopen($urdf_xml_output, 'r') or die("UPS! Something went wrong!");
		$array['urdf_output'] = fread($urdf_file_handling, filesize($urdf_xml_output));
		fclose($urdf_file_handling);

		echo json_encode(array("response_type" => "ok", "val" => $array));
    }

    // delete files
    unlink($grid_xml_output);
    unlink($lab_xml_output);
    unlink($param_xml_output);
    unlink($urdf_xml_output);
    unlink($lab_xml_output);
    unlink($dir_json.$challange_file_json);
    unlink($dir_json.$param_file_json);
?>