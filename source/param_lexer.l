%{
    #include <stdlib.h>
    #include "param_parser.tab.h"

    #define YY_DECL int yylex(YYSTYPE* p, YYLTYPE* l)
%}

%option noyywrap
%option nounput
%option noinput
%option yylineno

str  			["][a-zA-Z0-9 -][a-zA-Z0-9 -]*["]

id    			["][a-z][a-z -]*["]

comment 		["]comment["]

class 			["]class["]

value_type 		["]value[ ]type["]

xml_name 		["]XML[ ]name["]

default_value 	["]default[ ]value["]

double 			["]double["]

uint 			["]uint["]

switch 			["]switch["]

boolean 		["]boolean["]

%%

{comment}		{ l->first_line=yylineno; return COMMENT; }

{class}			{ l->first_line=yylineno; return CLASS; }

{value_type} 	{ l->first_line=yylineno; return VALUE_TYPE; }

{xml_name}  	{ l->first_line=yylineno; return XML_NAME; }

{default_value} { l->first_line=yylineno; return DEFAULT_VALUE; }

{double} 		{ l->first_line=yylineno; return DOUBLE; }

{uint} 			{ l->first_line=yylineno; return UINT; }

{switch} 		{ l->first_line=yylineno; return SWITCH; }

{boolean} 		{ l->first_line=yylineno; return BOOLEAN; }

{id}        	{ p->vid = strdup(yytext); l->first_line=yylineno; return ID; }

{str}			{ p->vstr = strdup(yytext); l->first_line=yylineno; return STR; }

[[:blank:]]		{ }

. { return yytext[0]; }
%%