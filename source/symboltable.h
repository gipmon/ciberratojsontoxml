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