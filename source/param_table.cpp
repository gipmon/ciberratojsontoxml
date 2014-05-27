#include <iostream>
#include <map>
#include <string>
#include "param_table.h"

using namespace std;


/* map<string => class, map<string => parameter_name, parameter>> map; */
map<string, map<string, parameter> > param_map;
map<string, parameter> class_standard;

void config_standard(string comment, string value_type, string default_value, string xml_name, string param_name){
  parameter tmp_parameter;

  tmp_parameter.comment = comment;
  tmp_parameter.value_type = value_type;
  tmp_parameter.default_value = default_value;
  tmp_parameter.xml_name = xml_name;

  class_standard[param_name] = tmp_parameter;
}

void init(){
  /* o map de cima vai ser uma class instanciada pelo init() inicial depois temos de fazer uma lista de parametros iniciais para colocar na class de standard e fazemos uma forma de iniciar a class para depois colocar no param_map */

  config_standard("","","","","challenge name");
  config_standard("","","","","challenge type");
  config_standard("","uint","50","SimCycle","cycle time");  // !! verificar xml names
  config_standard("","uint","2400","SimTime","cycle time"); // !! verificar xml names

  param_map["class_standard"] = class_standard;
}

bool add_parameter(string class_name, pair<string, parameter> param){
  if(exists(class_name)){
    if(exists(class_name, param.first)){
      throw PARAMETER_ALREADY_EXISTS;
    }

    map<string, parameter> Class = find(class_name);
    Class.insert(param);
  }else{
    map<string, parameter> new_map;
    param_map.insert(pair<string, map<string, parameter> >(class_name, new_map));
  }
  return true;
}

/*
  NOTA: Quando soubermos que o parâmetro existe, temos armazenado numa variavel e queremos saber se existe default value é mais eficiente fazer: param.default_value.length==0
*/
bool has_default_value(string class_name, string parameter_name){
  if(!exists(class_name, parameter_name)){
    throw PARAMETER_DOESNT_EXISTS;
  }

  parameter param = find(class_name, parameter_name);

  if(param.default_value.size()==0){
    return false;
  }else{
    return true;
  }
}

map<string, parameter> find(string class_name){
  if(!exists(class_name)){
    throw MAP_CLASS_DOESNT_EXISTS;
  }
  return param_map[class_name];
}

void print_parameter(string class_name, string parameter_name, parameter param){
  cout << "\""<< parameter_name << "\" : { \n " << "\t\"comment\" : \""<< param.comment << "\" \n" << "\t\"class\" : \""<< class_name << "\" \n" << "\t\"value type\" : \""<< param.value_type << "\" \n" << "\t\"default value\" : \""<< param.default_value << "\" \n"  << "\t\"XML name\" : \""<< param.xml_name << "\" \n" << "},"<< endl;
}

parameter find(string class_name, string parameter_name){
  if(!exists(class_name, parameter_name)){
  	throw PARAMETER_DOESNT_EXISTS;
  }
  return find(class_name)[parameter_name];
}

bool exists(string class_name){
  return param_map.count(class_name)!=0;
}

bool exists(string class_name, string parameter_name){
  return exists(class_name) && find(class_name).count(parameter_name)!=0;
}

int main(){

  return 0;
}