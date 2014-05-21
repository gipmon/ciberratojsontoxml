map<string, parameter*> class_standard;
bool add_parameter(string class_name, pair<string, parameter> param);
map<string => class, map<string => parameter_name, parameter>> map; 
map<string, map<string, parameter*>* > param_map;

void init(){
	
	config_standard("","","","","challenge name");
	config_standard("","","","","challenge type");
	config_standard("","uint","50","SimCycle","cycle time"); //verificar xml names
	config_standard("","uint","2400","SimTime","cycle time"); //verificar xml names


	param_map["class_standard"] = class_standard;



}

void config_standard(string comment, string value_type, string default_type, string xml_name, string param_name){
	parameter tmp_parameter;

	tmp_parameter->comment = comment;
	tmp_parameter->value_type = value_type;
	tmp_parameter->default_type = default_type;
	tmp_parameter->xml_name = xml_name;

	class_standard[param_name] = tmp_parameter;
}


