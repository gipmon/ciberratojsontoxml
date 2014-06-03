%union{
	char* vid;
	char* vstr;
	char* vidorstr;
}

%{
    #include <stdio.h>
    #include <iostream>
	#include <string>
	#include "main.h"

	int param_error(YYLTYPE* l, const char* fname, const char *s);
    int param_lex(YYSTYPE*, YYLTYPE* l);
    void reset_variables();
    void add_parameter_to_table_map(char*, char*, parameter);

    /* tmp variables */
    parameter param;
    char* param_name;
    char* class_name;
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
/*     */

%type<vidorstr> IDORSTR
%type<vstr> VT

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

PL   : PI { add_parameter_to_table_map(class_name, param_name, param); }
	 | PL ',' PI { add_parameter_to_table_map(class_name, param_name, param); } 
	 ;

PI   : ID {param_name = $1;} ':' '{' PAL '}'
	 ;

PAL  : AT
	 | PAL ',' AT 
	 ;

IDORSTR : STR {$$ = $1;}
		| ID {$$ = $1;}
		;

AT   :  COMMENT  ':'  IDORSTR {param.comment = $3;}
	 |  CLASS ':' IDORSTR {class_name = $3;}
	 |  VALUE_TYPE  ':'  VT {param.value_type = $3;}
	 |  XML_NAME  ':'  IDORSTR {param.xml_name = $3;}
	 |  DEFAULT_VALUE  ':'  IDORSTR {param.default_value = $3;}
	 ;

VT	 : DOUBLE {$$ = $1;}
	 | UINT {$$ = $1;}
	 | SWITCH {$$ = $1;}
	 | BOOLEAN {$$ = $1;}
	 ;

%%

int param_error(YYLTYPE* l, const char* fname, const char *s){
	extern char* param_text;
	printf("%s: %d: %s; conteudo no yytext: '%s'\n", fname, l->first_line, s, param_text);
    exit(1);
}

void add_parameter_to_table_map(char* class_name, char* param_name, parameter param){
	if(param_name != NULL && param_name[0] != '\0'){
		param_table->add_parameter(class_name, param_name, param);
		reset_variables();
 	}
}

void reset_variables(){
	parameter tmp;
	param = tmp;
	char* param_name = '\0';
    char* class_name = '\0';
}
