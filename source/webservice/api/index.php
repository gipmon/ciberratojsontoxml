<?php
	if(isset($_POST['param']) && isset($_POST['challenge'])){
		$param_list = $_POST['param'];
		$challenge = $_POST['challenge'];
	}else{
		echo json_encode(array("response_type" => "error", "val" => "You should pass the parameter param and challenge!"));
		exit();
	}

	// test if is json
	$ob_pl = json_decode($param_list);
	if($ob_pl === null){
		echo json_encode(array("response_type" => "error", "val" => "param.json isn't a JSON file!"));
		exit();
	}
	$ob_cl = json_decode($challenge);
	if($ob_cl === null){
		echo json_encode(array("response_type" => "error", "val" => "challenge.json isn't a JSON file!"));
		exit();
	}

	// create json files
	$dir = "../tmp/";
	$dir_json = $dir."json/";
	$dir_xml = $dir."xml/";

	$id = uniqid();

	$default_files = array($id."param.json", $id."challenge.json");

	// create default files
	foreach ($default_files as $value){
		$file_handling = fopen($dir_json.$value, 'w') or die("UPS! Something went wrong!");
		fwrite($file_handling, $param_list);
		fclose($file_handling);
	}

	// make output
	$files = array("grid_xml_output" => array("filename" => $dir_xml.$id."GRID.xml"),
				   "lab_xml_output" => array("filename" => $dir_xml.$id."LAB.xml"),
				   "param_xml_output" => array("filename" => $dir_xml.$id."PARAM.xml"),
				   "urdf_xml_output_rotate" => array("filename" => $dir_xml.$id."URDFR.xml"),
				   "urdf_xml_output_fixed" => array("filename" => $dir_xml.$id."URDFF.xml")
			 );

	$files_name = "";
	foreach ($files as $key => $value) {
		$filename .= " ".$value["filename"];
	}

	$command = "../../main.output -o -s ".$dir_json.$param_file_json." ".$dir_json.$challange_file_json." ".$filename;
    $output = shell_exec($command);

    if($output){
		echo json_encode(array("response_type" => "error", "val" => str_replace("tmp/json/".$id, "", $output)));
    }else{
    	foreach ($files as $key => $value) {
    		$file_handling = fopen($value["filename"], 'r') or die("UPS! Something went wrong!");
			$array[$key] = fread($file_handling, filesize($value["filename"]));
			fclose($file_handling);
    	}
		echo json_encode(array("response_type" => "ok", "val" => $array));
    }

    // delete files
    foreach ($files as $key => $value) {
    	unlink($value["filename"]);
	}
	foreach ($default_files as $value){
		unlink($value);
	}
?>