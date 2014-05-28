#include <iostream>
#include <map>
#include <cstring>
#include "param_table.h"

using namespace std;


/* std::map<char* => class, std::map<char* => parameter_name, parameter>> map; */
std::map<char*, std::map<char*, parameter> > param_map;
std::map<char*, parameter> class_standard;

std::map<char*, std::map<char*, parameter> >::iterator it1;
std::map<char*, parameter>::iterator it2;

void config_standard(char* comment, char* value_type, char* default_value, char* xml_name, char* param_name){
  parameter tmp_parameter;

  tmp_parameter.comment = comment;
  tmp_parameter.value_type = value_type;
  tmp_parameter.default_value = default_value;
  tmp_parameter.xml_name = xml_name;

  class_standard[param_name] = tmp_parameter;
}

void init(){
  /* o map de cima vai ser uma class instanciada pelo init() inicial depois temos de fazer uma lista de parametros iniciais para colocar na class de standard e fazemos uma forma de iniciar a class para depois colocar no param_map */

  config_standard((char *)"", (char *)"", (char *)"", (char *)"", (char *)"challenge name");
  config_standard((char *)"", (char *)"", (char *)"", (char *)"", (char *)"challenge type");
  config_standard((char *)"", (char *)"uint", (char *)"50", (char *)"CycleTime", (char *)"cycle time");
  config_standard((char *)"", (char *)"uint", (char *)"2400", (char *)"SimTime", (char *)"duration");

  param_map[(char *)"class_standard"] = class_standard;
}

bool add_parameter(char* class_name, char* param_name, parameter param){
    /* itator->first  = key; itator->second = value std::map<char*, parameter> */

    for(it1 = param_map.begin(); it1 != param_map.end(); it1++) {
        // strcmp() returns a 0 if the two strings are equal,
        if(!strcmp(it1->first, class_name)){
          for(it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
            if(!strcmp(it2->first, param_name)){
              throw PARAMETER_ALREADY_EXISTS;
            }
          }
          it1->second[param_name] = param;
          return true;
        }
    }

    std::map<char*, parameter> new_map;
    new_map[param_name] = param;

    param_map.insert(std::pair<char*, std::map<char*, parameter> >(class_name, new_map));

  return true;
}

/*
  NOTA: Quando soubermos que o parâmetro existe, temos armazenado numa variavel e queremos saber se existe default value é mais eficiente fazer: param.default_value.length==0
*/
bool has_default_value(char* class_name, char* parameter_name){
  if(!exists(class_name, parameter_name)){
    throw PARAMETER_DOESNT_EXISTS;
  }

  parameter param = find(class_name, parameter_name);
  return true;
  /*
  if(param.default_value()==0){
    return false;
  }else{
    return true;
  }
  */
}

std::map<char*, parameter> find(char* class_name){
  if(!exists(class_name)){
    throw MAP_CLASS_DOESNT_EXISTS;
  }
  return param_map[class_name];
}

void print_parameter(char* class_name, char* parameter_name, parameter param){
  cout << "\""<< parameter_name << "\" : { \n " << "\t\"comment\" : \""<< param.comment << "\" \n" << "\t\"class\" : \""<< class_name << "\" \n" << "\t\"value type\" : \""<< param.value_type << "\" \n" << "\t\"default value\" : \""<< param.default_value << "\" \n"  << "\t\"XML name\" : \""<< param.xml_name << "\" \n" << "},"<< endl;
}

parameter find(char* class_name, char* parameter_name){
  if(!exists(class_name, parameter_name)){
  	throw PARAMETER_DOESNT_EXISTS;
  }
  return find(class_name)[parameter_name];
}

bool exists(char* class_name){
  it1 = param_map.find(class_name);
  return it1!=param_map.end();
}

bool exists(char* class_name, char* parameter_name){
  return exists(class_name) && find(class_name).count(parameter_name)!=0;
}

void print_symboltable(){
    // itator->first = key
    // itator->second = value

    for(it1 = param_map.begin(); it1 != param_map.end(); it1++) {
        cout << it1->first << "\n" << endl;
        for(it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
            char* key2 = it2->first;
            char* comment =it2->second.comment;
            char* value_type  = it2->second.value_type;
            char* default_value = it2->second.default_value;
            char* xml_name = it2->second.xml_name;
            cout << "\n \t" << key2 <<endl;
            cout << "\n \t \t \"comment\": " << comment <<endl;
            cout << "\n \t \t \"value type\": " << value_type <<endl;
            if(it2->second.default_value != NULL){
              cout << "\n \t \t \"default value\": " << default_value <<endl;
            }
            cout << "\n \t \t \"xml name\": " << xml_name <<endl;
        }
    }
}
