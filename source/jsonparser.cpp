%{
    #include <stdio.h>
	#include "symboltable.h"

    int yylex(void);
    int yyerror(char *s);

%}

%token <vcomment> COMMENT
%token <vclass> CLASS
%token <vvalue> VALUE_TYPE
%token <vxml> XML_NAME
%token <vdefault> DEFAULT_VALUE
%token <vid> ID
%token <vstr> STR

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
	 | '\"' VALUE_TYPE '\"' ':' '\"' str '\"' {param->value_type = $6;}
	 | '\"' XML_NAME '\"' ':' '\"' str '\"'	{param->xml_name = $6;}
	 | '\"' DEFAULT_VALUE '\"' ':' '\"' str '\"' {param->default_value = $6;}
	 ;

%%

int yyerror(const char *s)
{
    return 0;
}