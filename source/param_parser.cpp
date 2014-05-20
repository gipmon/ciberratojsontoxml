%{
    #include <stdio.h>
	#include "param_table.h"

    int yylex(void);
    int yyerror(char *s);

%}

%token  COMMENT
%token  CLASS
%token  VALUE_TYPE
%token  XML_NAME
%token  DEFAULT_VALUE
%token <vid> ID
%token <vstr> STR
%token DOUBLE
%token UINT
%token SWITCH
%token BOOLEAN

/*
	{parameter param;} ONDE INICIALIZO A ESTRUTURA?
*/

%%
// File = param-list.json
File :	'{' PL '}'
	 ;

// PL = parameter list
PL   :	/* lambda */
	 |  PI ',' PL { add_parameter(); }
	 ;

// PI = parameter item
PI   : PK ':' '{' PAL '}'
	 ;

// Pk = parameter key
// reconhecido e fornecido pelo lexer2 (flex)
PK   : ID {string parameter_name = $1}
	 ;

// PAL = parameter atribute list
PAL  : /* lambda */
	 | AT ',' PAL
	 ;

// AT = atribute
// String fornecida pelo lexer2 (flex)
AT   : /* lambda */
	 | '\"' COMMENT '\"' ':' '\"' str '\"' {param->comment = $6;}
	 | '\"' CLASS '\"' ':' '\"' str '\"' {string class_name = $6;}
	 | '\"' VALUE_TYPE '\"' ':' '\"' VT '\"' {param->value_type = $6;}   
	 | '\"' XML_NAME '\"' ':' '\"' str '\"'	{param->xml_name = $6;}
	 | '\"' DEFAULT_VALUE '\"' ':' '\"' str '\"' {param->default_value = $6;}
	 ;
//VT = value type
VT	:
	| '\"'DOUBLE'\"'
	| '\"'UINT'\"'
	| '\"'SWITCH'\"'
	| '\"'BOOLEAN'\"'
	;

%%

int yyerror(const char *s)
{
    return 0;
}