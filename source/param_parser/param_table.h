#include <iostream>
#include <map>

using namespace std;

/************* Estrutura de dados para o parameter **************/
struct parameter{
  char* comment;
  char* value_type;
  char* default_value;
  char* xml_name;
};

/************************ Definição de Códigos de Erro ************************/
#define  PARAMETER_ALREADY_EXISTS		0
#define  MAP_CLASS_DOESNT_EXISTS		1
#define  PARAMETER_DOESNT_EXISTS		2

class ParamTable{
	private:
		/* map<char* => class, map<char* => parameter_name, parameter>> map; */
		map<char*, map<char*, parameter> > param_map;

		void config_standard(char* comment, char* value_type, char* default_value, char* xml_name, char* param_name);
	public:
		ParamTable();
		bool add_parameter(char* class_name, char* param_name, parameter param);
		bool has_default_value(char* class_name, char* parameter_name);
		bool get_default_value(char* class_name, char* parameter_name);
		bool parameter_exists(char* class_name, char* parameter_name);
		char* get_xml_name(char* class_name, char* parameter_name);
		char* get_comment(char* class_name, char* parameter_name);
		bool valid_value_type(char* class_name, char* parameter_name, char* value);
		void print_parameter(char* class_name, char* parameter_name, parameter param);
		void print_symboltable();
};
