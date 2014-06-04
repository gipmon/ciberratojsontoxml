%{
    #include <stdlib.h>
    #include "../param_parser.tab.h"

    #define YY_DECL int param_lex(YYSTYPE* p, YYLTYPE* l)

%}

%option noyywrap
%option nounput
%option noinput
%option yylineno
%option prefix="param_"

str  			["][^"\n]*["]

nint    		[0-9]+

dv_int 			["]{nint}["]

dv_double		["]({nint}|{nint}\.{nint})["]

dv_bool 		["]true["]|["]false["]

dv_switch 		["]on["]|["]off["]

id    			["][a-zA-Z][a-zA-Z -]*["]

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

{double} 		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); l->first_line=yylineno; return DOUBLE; }

{uint} 			{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); l->first_line=yylineno; return UINT; }

{switch} 		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); l->first_line=yylineno; return SWITCH; }

{boolean} 		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); l->first_line=yylineno; return BOOLEAN; }

{dv_bool}		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); l->first_line=yylineno; return DV_BOOL; }

{dv_switch}		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); l->first_line=yylineno; return DV_SWITCH; }

{dv_int}			{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); l->first_line=yylineno; return DV_INT; }

{dv_double}			{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); l->first_line=yylineno; return DV_DOUBLE; }

{id}        	{ yytext[strlen(yytext)-1] = '\0'; p->vid = strdup(yytext+1); l->first_line=yylineno; return ID; }

{str}			{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); l->first_line=yylineno; return STR; }


[[:blank:]]		{ }

\n 				{ }

. { return yytext[0]; }
%%

