%{
    #include <stdio.h>
	#include "param_table.h"

    int yylex(void);
    int yyerror(char *s);
    parameter param;
%}

%token  COMMENT
%token  CLASS
%token  VALUE_TYPE
%token  XML_NAME
%token 	DEFAULT_VALUE
%token 	<vid> ID
%token 	<vstr> STR
%token  <vclassvalue> CLASS_VALUE
/* relativos ao value type*/
%token 	DOUBLE
%token 	UINT
%token 	SWITCH
%token 	BOOLEAN
/*     */
%token <vdvv> DEFAULT_VALUE_VALUE
%token <vxml> XML_NAME_VALUE

%%
// File = param-list.json
File : '{' PL '}'
	 ;

// PL = parameter list
PL   :	/* lambda */
	 |  PI ',' PL
	 ;

// PI = parameter item
PI   : PK ':' '{' PAL '}'
	 ;

// Pk = parameter key
// reconhecido e fornecido pelo lexer2 (flex)
PK   : ID {string parameter_name = $1}
	 ;

// PAL = parameter atribute list
PAL  : AT
	 | PAL ',' AT
	 ;

// AT = atribute
// String fornecida pelo lexer2 (flex)
AT   : /* lambda */
	 | '\"' COMMENT '\"' ':' '\"' STR '\"' {/*param->comment = $6;*/}
	 | '\"' CLASS '\"' ':' '\"' CLASS_VALUE '\"' {/*string class_name = $6;*/}
	 | '\"' VALUE_TYPE '\"' ':' '\"' VT '\"' {/*param->value_type = $6;*/}
	 | '\"' XML_NAME '\"' ':' '\"' XML_NAME_VALUE '\"'	{/*param->xml_name = $6;*/}
	 | '\"' DEFAULT_VALUE '\"' ':' '\"' DEFAULT_VALUE_VALUE '\"' {/*param->default_value = $6;*/}
	 ;
//VT = value type
VT	:
	| '\"'DOUBLE'\"'
	| '\"'UINT'\"'
	| '\"'SWITCH'\"'
	| '\"'BOOLEAN'\"'
	;

%%


int main(int argc, char* argv[]){
	extern FILE* yyin;
	if((yyin = fopen(argv[i], "r")) == NULL){
		printf("ERRRO!\n");
		return 0;
	}
	yyparser();
	printf("FUNCIONOU!\n");
	return 1;
}

int yyerror(const char *s)
{
    return 0;
}