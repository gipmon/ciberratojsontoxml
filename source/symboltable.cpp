#include <iostream>
#include <string>
#include <map>
#include "symboltable.h"

using namespace std;

/* map<string => class, map<string => parameter_name, parameter>> map; */
map<string, map<string, parameter> > standard_map;
map<string, map<string, parameter> > param_map;

map<string, map<string, parameter> >:: iterator it1;
map<string, parameter>:: iterator it2;

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
  NOTA: Quando soubermos que o parâmetro existe, temos armazenado numa variavel e queremos saber se existe default value é mais eficiente fazer: param.default_value.length()==0
*/
bool has_default_value(string class_name, string parameter_name){
  if(!exists(class_name, parameter_name)){
      return false;
  }

  parameter param = find(class_name, parameter_name);

  if(param.default_value.length()==0){
    return false;
  }else{
    return true;
  }
}

map<string, parameter> find(string class_name){
  if(!exists(class_name)){
    throw MAP_PARAMETER_DOESNT_EXISTS;
  }
  if(standard_map.count(class_name)!=0){
    return standard_map[class_name];
  }else{
    return param_map[class_name];
  }
}

parameter find(string class_name, string parameter_name){
  if(!exists(class_name, parameter_name)){
  	throw PARAMETER_DOESNT_EXISTS;
  }
  return find(class_name)[parameter_name];
}

bool exists(string class_name){
  return param_map.count(class_name)!=0 || standard_map.count(class_name)!=0;
}

bool exists(string class_name, string parameter_name){
  return exists(class_name) && (param_map[class_name].count(parameter_name)!=0 || standard_map[class_name].count(parameter_name)!=0);
}
