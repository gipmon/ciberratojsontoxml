#include <iostream>
#include <map>
#include "../error.h"

using namespace std;

extern void ErrorHandling(int);

struct parameter{
  char* comment;
  char* value_type;
  char* default_value;
  char* xml_name;
};

class ParamTable{
	private:
		/* map<char* => class, map<char* => parameter_name, parameter>> map; */
		map<char*, map<char*, parameter> > param_map;

		void config_standard(char* comment, char* value_type, char* default_value, char* xml_name, char* param_name);
	public:
		ParamTable();
		void add_parameter(char* class_name, char* param_name, parameter param);
		bool has_default_value(char* class_name, char* parameter_name);
		bool get_default_value(char* class_name, char* parameter_name);
		bool parameter_exists(char* class_name, char* parameter_name);
		char* get_xml_name(char* class_name, char* parameter_name);
		char* get_comment(char* class_name, char* parameter_name);
		bool valid_value_type(char* class_name, char* parameter_name, char* value);
		void print_parameter(char* class_name, char* parameter_name, parameter param);
		void validate_parameter(parameter param);
		void print_symboltable();
};
