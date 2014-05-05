#include <iostream>
#include <string>
#include <map>

using namespace std;

struct parameter{
  string comment;
  string class_name;
  string value_type;
  string default_value;
  string xml_name;
};

bool has_default_value(string key);
bool add_parameter(string key, parameter param);
bool exists_parameter(string key);
parameter find_parameter(string key);

map<string, parameter> symbol_table;
map <string, parameter> :: iterator it;


bool exists_parameter(string key){
    return symbol_table.count(key)!=0;
}

bool add_parameter(string key, parameter param){
    if(exists_parameter(key)){
        return false;
    }
    symbol_table.insert(pair<string, parameter>(key, param));
    return true;
}

bool has_default_value(string key){
    if(!symbol_table.count(key)){
        return false;
    }
    return true;
}

parameter find_parameter(string key){
    if(!exists_parameter(key)){
    	throw 10;
    }
    return symbol_table[key];
}