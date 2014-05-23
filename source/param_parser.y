%union{
	char* vid;
	char* vstr;
}

%{
    #include <stdio.h>
	#include "param_table.h"

	extern int yyparse(const char* fname);
	extern FILE* yyin;

	int yyerror(YYLTYPE* l, const char* fname, const char *s);
    int yylex(YYSTYPE*, YYLTYPE* l);

    parameter param;
%}

%token  COMMENT
%token  CLASS
%token  VALUE_TYPE
%token  XML_NAME
%token 	DEFAULT_VALUE
%token 	<vid> ID
%token 	<vstr> STR
/* relativos ao value type*/
%token 	DOUBLE
%token 	UINT
%token 	SWITCH
%token 	BOOLEAN
/*     */

%parse-param {const char* fname}
%pure-parser
%defines
%error-verbose
%locations

%%
// File = param-list.json
File : '{' PL '}'
	 ;

// PL = parameter list
PL   :  PI
	 |  PL ',' PI
	 ;

// PI = parameter item
PI   : ID ':' '{' PAL '}'
	 ;

// PAL = parameter atribute list
PAL  : AT
	 | PAL ',' AT
	 ;

// AT = atribute
// String fornecida pelo lexer2 (flex)
AT   : /* lambda */
	 |  COMMENT  ':'  STR
	 |  CLASS  ':'  STR
	 |  VALUE_TYPE  ':'  VT
	 |  XML_NAME  ':'  STR
	 |  DEFAULT_VALUE  ':'  STR
	 ;

//VT = value type
VT	: DOUBLE
	| UINT
	| SWITCH
	| BOOLEAN
	;
%%

int main(int argc, char* argv[]){
	if((yyin = fopen(argv[1], "r")) == NULL){
		printf("ERRRO!\n");
		return 0;
	}
	yyparse(argv[1]);
	printf("FUNCIONOU!\n");
	return 1;
}

int yyerror(YYLTYPE* l, const char* fname, const char *s)
{
	printf("%s: %d: %s\n", fname, l->first_line, s);
    exit(0);
}
