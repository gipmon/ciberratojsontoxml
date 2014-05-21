#include <iostream>
#include <string>
#include <map>

using namespace std;

/************* Estrutura de dados para o parameter **************/
struct parameter{
  string comment;
  string value_type;
  string default_value;
  string xml_name;
};

/************************ Definição de Códigos de Erro ************************/
#define  PARAMETER_ALREADY_EXISTS		0
#define  MAP_CLASS_DOESNT_EXISTS		1
#define  PARAMETER_DOESNT_EXISTS		2

/***************** Definição dos mapas e iteradores *****************/
/* map<string => class, map<string => parameter_name, parameter>> map; */
extern map<string, map<string, parameter*>*> param_map;

/*
extern map<string, map<string, parameter> >:: iterator it1;
extern map<string, parameter>:: iterator it2;;
/*************************** Protótipos das Funções ***************************/

void init();

/*******************************************************************************
	Tem valor de defeito (default_value) este valor permite tornar um parametro obrigatório ou não. Se não for obrigatório o default_value é usado no value.
*******************************************************************************/
bool has_default_value(string parameter_name);

/*******************************************************************************
	Adicionar parâmetro na class
*******************************************************************************/
bool add_parameter(string class_name, parameter param);

/*******************************************************************************
	Verificar se exite o parâmetro na class
*******************************************************************************/
bool exists_parameter(string parameter_name);

/*******************************************************************************
	Procurar no param_map se existe a class_name, se sim, retorna o map
*******************************************************************************/
map<string, parameter> find(string class_name);

/*******************************************************************************
	Procurar na class se existe o parametro, se sim, retorna o parametro
*******************************************************************************/
parameter find(string class_name, string parameter_name);

/*******************************************************************************
	Verificar se exite a class_name
*******************************************************************************/
bool exists(string class_name);

/*******************************************************************************
	Verificar se exite o parametro
*******************************************************************************/
bool exists(string class_name, string parameter_name);
