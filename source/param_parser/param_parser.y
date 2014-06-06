%union{
	char* vid;
	char* vstr;
	char* vidorstr;
	struct{
		char* type;
		char* value;
	} vdv;
}

%{
    #include <stdio.h>
    #include <iostream>
	#include <string>
	#include <cstring>
	#include "main.h"

	int param_error(YYLTYPE* l, const char* fname, const char *s);
    int param_lex(YYSTYPE*, YYLTYPE* l);
    void reset_variables();
    void add_parameter_to_table_map(char*, char*, parameter);
    void validate_dv();

    /* tmp variables */
    parameter param;
    char* param_name;
    char* class_name;
    char* default_value_type;
%}

%token  COMMENT
%token  CLASS
%token  VALUE_TYPE
%token  XML_NAME
%token 	DEFAULT_VALUE
%token 	<vstr> STR
%token 	<vid> ID

/* relativos ao value type*/
%token 	<vstr> DOUBLE
%token 	<vstr> UINT
%token 	<vstr> SWITCH
%token 	<vstr> BOOLEAN

/* default value types */
%token 	<vstr> DV_INT
%token 	<vstr> DV_DOUBLE
%token  <vstr> DV_BOOL
%token  <vstr> DV_SWITCH

/* type grammar */
%type<vidorstr> IDORSTR
%type<vstr> VT
%type<vdv> DV_VALUE

%parse-param {const char* fname}
%pure-parser
%defines
%error-verbose
%locations
/*%verbose*/
%start File
%name-prefix="param_"

%%
File : '{' PL '}' { return 1; }
	 ;

PL   : PI { validate_dv(); add_parameter_to_table_map(class_name, param_name, param); }
	 | PL ',' PI { validate_dv(); add_parameter_to_table_map(class_name, param_name, param); } 
	 ;

PI   : ID {param_name = $1;} ':' '{' PAL '}'
	 ;

PAL  : AT
	 | PAL ',' AT 
	 ;

IDORSTR : STR {$$ = $1;}
		| ID {$$ = $1;}
		;

AT   :  COMMENT  	':'  IDORSTR {param.comment = $3;}
	 |  CLASS 	 	':'  IDORSTR {class_name = $3;}
	 |  VALUE_TYPE  ':'  VT {param.value_type = $3;}
	 |  XML_NAME  	':'  IDORSTR {param.xml_name = $3;}
	 |  DEFAULT_VALUE  ':'  DV_VALUE {param.default_value = $3.value; default_value_type = $3.type;}
	 ;

DV_VALUE : 		DV_INT {$$.value = $1; $$.type = (char*)"uint";}
			  | DV_DOUBLE {$$.value = $1; $$.type = (char*)"double";}
			  | STR {$$.value = $1; $$.type = (char*)"string";}
			  | ID {$$.value = $1; $$.type = (char*)"string";}
			  | DV_BOOL {$$.value = $1; $$.type = (char*)"boolean";}
			  | DV_SWITCH {$$.value = $1; $$.type = (char*)"switch";}
			  ;

VT	 : DOUBLE {$$ = $1;}
	 | UINT {$$ = $1;}
	 | SWITCH {$$ = $1;}
	 | BOOLEAN {$$ = $1;}
	 ;

%%

int param_error(YYLTYPE* l, const char* fname, const char *s){
	extern char* param_text;
	extern Error error;
	error.fname = fname;
	error.line = l->first_line;
	error.column = l->first_column;
	error.s = strdup(s);
	error.yytext = param_text;

	throw PARSING_ERROR;
}

void add_parameter_to_table_map(char* class_name, char* param_name, parameter param){
	if(param_name != NULL && param_name[0] != '\0' && class_name != NULL && class_name[0] != '\0'){
		tmp_param_table->add_parameter(class_name, param_name, param);
 	}
	reset_variables();
}
void validate_dv(){
	if(default_value_type != NULL && default_value_type[0] != '\0' && param.value_type != NULL && param.value_type[0] != '\0' && param.default_value != NULL && param.default_value[0] != '\0'){
		if(!(!strcmp(param.value_type, "double") && (!strcmp(default_value_type, "double") || !strcmp(default_value_type, "uint")))){
			if(strcmp(param.value_type, default_value_type)){
				//printf("%s!=%s, %s\n", param.value_type, default_value_type, param.default_value);
				throw DEFAULT_VALUE_WRONG_BY_TYPE;
			}
		}
	}
}

void reset_variables(){
	parameter tmp;
	param = tmp;
	param.default_value = '\0';
	char* param_name = '\0';
    char* class_name = '\0';
    char* default_value_type = '\0';
}
