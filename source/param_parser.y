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
%token 	<vstr> STR
%token 	<vid> ID

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
%verbose

%%
File : '{' PL '}'
	 ;

PL   :  PI
	 |  PI ',' PL
	 ;

PI   : ID ':' '{' PAL '}'
	 ;

PAL  : AT
	 | AT ',' PAL
	 ;

AT   :  COMMENT  ':'  STR
	 |  CLASS  ':'  STR
	 |  VALUE_TYPE  ':'  VT
	 |  XML_NAME  ':'  STR
	 |  DEFAULT_VALUE  ':'  STR
	 ;

VT	 : DOUBLE
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

int yyerror(YYLTYPE* l, const char* fname, const char *s){
	extern char* yytext;
	printf("%s: %d: %s; conteudo no yytext: '%s'\n", fname, l->first_line, s, yytext);
    exit(0);
}
