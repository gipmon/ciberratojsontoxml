%union{
	char* vid;
	char* vstr;
	char* vidorstr;
}

%{
    #include <stdio.h>
    #include <string>
	#include "param_table.h"

	extern int yyparse(const char* fname);
	extern FILE* yyin;

	int yyerror(YYLTYPE* l, const char* fname, const char *s);
    int yylex(YYSTYPE*, YYLTYPE* l);
    void print_parameter(char*, char*, parameter);

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
%verbose
%start File

%%
File : '{' PL '}' { print_symboltable(); exit(0); }
	 ;

PL   :  PI {add_parameter(class_name, param_name, param);}
	 |  PI {add_parameter(class_name, param_name, param);} ',' PL
	 ;

PI   : ID {param_name = $1;} ':' '{' PAL '}'
	 ;

PAL  : AT
	 | AT ',' PAL
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

int main(int argc, char* argv[]){
	if((yyin = fopen(argv[1], "r")) == NULL){
		printf("ERRRO!\n");
		return 0;
	}
	yyparse(argv[1]);
	return 1;
}

int yyerror(YYLTYPE* l, const char* fname, const char *s){
	extern char* yytext;
	printf("%s: %d: %s; conteudo no yytext: '%s'\n", fname, l->first_line, s, yytext);
    exit(1);
}
