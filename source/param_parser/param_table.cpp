#include <iostream>
#include <map>
#include <cstring>
#include "param_table.h"

using namespace std;

/* iteradores */
map<char*, map<char*, parameter> >::iterator it1;
map<char*, parameter>::iterator it2;

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

void ParamTable::add_parameter(char* class_name, char* param_name, parameter param){

    /* validar se o parâmetro tem o que é obrigatório */
    try{
        validate_parameter(class_name, param_name, param);
    }catch(int e){
        ErrorHandlingWithExit(e);
    }

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
          return;
        }
    }

    map<char*, parameter> new_map;
    new_map[param_name] = param;

    param_map.insert(pair<char*, map<char*, parameter> >(class_name, new_map));
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
    for(it1 = param_map.begin(); it1 != param_map.end(); it1++) {
        if(!strcmp(it1->first, class_name)){
          for(it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
            if(!strcmp(it2->first, parameter_name)){
                if(it2->second.default_value != NULL && it2->second.default_value[0] != '\0'){
                    return false;
                }else{
                    return true;
                }
            }
          }
        }
    }
    return false;
}

bool ParamTable::parameter_exists(char* class_name, char* parameter_name){
    for(it1 = param_map.begin(); it1 != param_map.end(); it1++) {
        if(!strcmp(it1->first, class_name)){
          for(it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
            if(!strcmp(it2->first, parameter_name)){
                return true;
            }
          }
        }
    }
    return false;
}

char* ParamTable::get_default_value(char* class_name, char* parameter_name){
    for(it1 = param_map.begin(); it1 != param_map.end(); it1++) {
        if(!strcmp(it1->first, class_name)){
          for(it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
            if(!strcmp(it2->first, parameter_name)){
              return it2->second.default_value;
            }
          }
        }
    }
    return '\0';
}


char* ParamTable::get_comment(char* class_name, char* parameter_name){
    for(it1 = param_map.begin(); it1 != param_map.end(); it1++) {
        if(!strcmp(it1->first, class_name)){
          for(it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
            if(!strcmp(it2->first, parameter_name)){
              return it2->second.comment;
            }
          }
        }
    }
    return '\0';
}

void ParamTable::validate_parameter(char* class_name, char* param_name, parameter param){
    if(strlen(param.value_type)==0){
        throw PARAMETER_VALUE_TYPE_REQUIRED;
    }else if(strlen(class_name)==0){
        throw PARAMETER_CLASS_NAME_REQUIRED;
    }else if(strlen(param_name)==0){
        throw PARAMETER_NAME_REQUIRED;
    }
}

