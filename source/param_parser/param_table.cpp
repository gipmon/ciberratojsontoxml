#include <iostream>
#include <map>
#include <cstring>
#include "param_table.h"

using namespace std;

/* iteradores */
map<char*, map<char*, parameter> >::iterator it1;
map<char*, parameter>::iterator it2;

ParamTable::ParamTable(){
    config_standard((char *)"", (char *)"", (char *)"", (char *)"", (char *)"challenge name");
    config_standard((char *)"", (char *)"", (char *)"", (char *)"", (char *)"challenge type");
    config_standard((char *)"", (char *)"uint", (char *)"50", (char *)"CycleTime", (char *)"cycle time");
    config_standard((char *)"", (char *)"uint", (char *)"2400", (char *)"SimTime", (char *)"duration");
}

void ParamTable::config_standard(char* comment, char* value_type, char* default_value, char* xml_name, char* param_name){
    parameter tmp_parameter;

    tmp_parameter.comment = comment;
    tmp_parameter.value_type = value_type;
    tmp_parameter.default_value = default_value;
    tmp_parameter.xml_name = xml_name;

    add_parameter((char*)"parameters_standard", param_name, tmp_parameter);
}

void ParamTable::print_parameter(char* class_name, char* parameter_name, parameter param){
    cout << "\""<< parameter_name << "\" : { \n " << "\t\"comment\" : \""<< param.comment << "\" \n" << "\t\"class\" : \""<< class_name << "\" \n" << "\t\"value type\" : \""<< param.value_type << "\" \n" << "\t\"default value\" : \""<< param.default_value << "\" \n"  << "\t\"XML name\" : \""<< param.xml_name << "\" \n" << "},"<< endl;
}

void ParamTable::print_symboltable(){
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

bool ParamTable::add_parameter(char* class_name, char* param_name, parameter param){
    /* itator->first  = key; itator->second = value map<char*, parameter> */

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

    map<char*, parameter> new_map;
    new_map[param_name] = param;

    param_map.insert(pair<char*, map<char*, parameter> >(class_name, new_map));

    return true;
}

char* ParamTable::get_xml_name(char* class_name, char* parameter_name){
	for(it1 = param_map.begin(); it1 != param_map.end(); it1++) {
        // strcmp() returns a 0 if the two strings are equal,
        if(!strcmp(it1->first, class_name)){
          for(it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
            if(!strcmp(it2->first, parameter_name)){
              return it2->second.xml_name;
            }
          }
        }
    }
    	return (char*)"Erro";
}


bool ParamTable::has_default_value(char* class_name, char* parameter_name){
    return 0;
}

bool ParamTable::parameter_exists(char* class_name, char* parameter_name){
    return 0;
}

bool ParamTable::get_default_value(char* class_name, char* parameter_name){
    return 0;
}


char* ParamTable::get_comment(char* class_name, char* parameter_name){
    return 0;
}

bool ParamTable::valid_value_type(char* class_name, char* parameter_name, char* value){
    /* procura saber qual é o value type do parametro e depois consuante o value type do parametro tem de se validar os tokens recebidos pelo value. feito em REGEX o value vem da segunda gramática invocado em c++ */
    return 0;
}


