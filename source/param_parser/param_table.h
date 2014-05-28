#include <iostream>
#include <map>

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

/***************** Definição dos mapas e iteradores *****************/
/* std::map<char* => class, std::map<char* => parameter_name, parameter>> map; */
extern std::map<char*, std::map<char*, parameter> > param_map;

/*************************** Protótipos das Funções ***************************/
void init();

/*******************************************************************************
	Tem valor de defeito (default_value) este valor permite tornar um parametro obrigatório ou não. Se não for obrigatório o default_value é usado no value.
*******************************************************************************/
bool has_default_value(char* parameter_name);

/*******************************************************************************
	Adicionar parâmetro na class
*******************************************************************************/
bool add_parameter(char* class_name, char* param_name, parameter param);

/*******************************************************************************
	Verificar se exite o parâmetro na class
*******************************************************************************/
bool exists_parameter(char* parameter_name);

/*******************************************************************************
	Procurar no param_map se existe a class_name, se sim, retorna o map
*******************************************************************************/
std::map<char*, parameter> find(char* class_name);

/*******************************************************************************
	Procurar na class se existe o parametro, se sim, retorna o parametro
*******************************************************************************/
parameter find(char* class_name, char* parameter_name);

/*******************************************************************************
	Verificar se exite a class_name
*******************************************************************************/
bool exists(char* class_name);

/*******************************************************************************
	Verificar se exite o parametro
*******************************************************************************/
bool exists(char* class_name, char* parameter_name);

/*******************************************************************************
	Imprimir o parametro no formato json
*******************************************************************************/
void print_parameter(char* class_name, char* parameter_name, parameter param);

/*******************************************************************************
	FUNÇÃO DE INICIALIZAR PARAMETER TABLE
*******************************************************************************/
void init();

/*******************************************************************************
	PRINT SYMBOL TABLE
*******************************************************************************/
void print_symboltable();
