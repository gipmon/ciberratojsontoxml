%{
    #include <stdlib.h>
    #include "../param_parser.tab.h"

    #define YY_DECL int param_lex(YYSTYPE* p, YYLTYPE* loc)

    #define UPDATE_LOC { \
        loc->first_line = loc->last_line = yylineno; \
        loc->first_column = col; \
        col += strlen(yytext); \
        loc->last_column = col-1; }

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

				static int col = 1;

{comment}		{ UPDATE_LOC; return COMMENT; }

{class}			{ UPDATE_LOC; return CLASS; }

{value_type} 	{ UPDATE_LOC; return VALUE_TYPE; }

{xml_name}  	{ UPDATE_LOC; return XML_NAME; }

{default_value} { UPDATE_LOC; return DEFAULT_VALUE; }

{double} 		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); UPDATE_LOC; return DOUBLE; }

{uint} 			{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); UPDATE_LOC; return UINT; }

{switch} 		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); UPDATE_LOC; return SWITCH; }

{boolean} 		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); UPDATE_LOC; return BOOLEAN; }

{dv_bool}		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); UPDATE_LOC; return DV_BOOL; }

{dv_switch}		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); UPDATE_LOC; return DV_SWITCH; }

{dv_int}		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); UPDATE_LOC; return DV_INT; }

{dv_double}		{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); UPDATE_LOC; return DV_DOUBLE; }

{id}        	{ yytext[strlen(yytext)-1] = '\0'; p->vid = strdup(yytext+1); UPDATE_LOC; return ID; }

{str}			{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); UPDATE_LOC; return STR; }


[[:blank:]]		{ col++; }

\n 				{ col = 1; }

. { return yytext[0]; }
%%

