%{
    #include <stdlib.h>
	#include <vector>
    #include "../classes/Point.h"
    #include "../maze_parser.tab.h"

    #define YY_DECL int maze_lex(YYSTYPE* p, YYLTYPE* l)

%}

%option noyywrap
%option nounput
%option noinput
%option yylineno
%option prefix="maze_"

nint    			[0-9]+

num     			{nint}|{nint}\.{nint}|\-{nint}

str    				["][^"\n]*["]

challenge_name 		["]challenge[ ]name["]

challenge_type 		["]challenge[ ]type["]

cycle_time 			["]cycle[ ]time["]

duration 			["]duration["]

scenario_description ["]scenario[ ]description["]

sd_name 			["]name["]

sd_dimensions       ["]dimensions["]

sd_becons   		["]beacons["]

sd_target_areas     ["]target[ ]areas["]

sd_walls 			["]walls["]

sd_grid				["]grid["]

sd_position			["]position["]

sd_radius			["]radius["]

sd_height			["]height["]

sd_corner_list		["]corner[ ]list["]

thickness			["]thickness["]	


%%

{challenge_name}			{ l->first_line=yylineno; return CHALLENGE_NAME; }

{challenge_type} 			{ l->first_line=yylineno; return CHALLENGE_TYPE; }

{cycle_time} 				{ l->first_line=yylineno; return CYCLE_TIME; }

{duration}					{ l->first_line=yylineno; return DURATION; }

{scenario_description}		{ l->first_line=yylineno; return SCENARIO_DESCRIPTION; }

{sd_name}					{ l->first_line=yylineno; return SD_NAME; }

{sd_dimensions}				{ l->first_line=yylineno; return SD_DIMENSIONS; }

{sd_becons}					{ l->first_line=yylineno; return SD_BEACONS; }

{sd_target_areas}			{ l->first_line=yylineno; return SD_TARGET_AREAS; }

{sd_walls}					{ l->first_line=yylineno; return SD_WALLS; }

{sd_grid}					{ l->first_line=yylineno; return SD_GRID; }

{sd_position}				{ l->first_line=yylineno; return SD_POSITION; }

{sd_radius}					{ l->first_line=yylineno; return SD_RADIUS; }

{sd_height}					{ l->first_line=yylineno; return SD_HEIGHT; }

{thickness}					{ l->first_line=yylineno; return THICKNESS; }

{sd_corner_list}			{ l->first_line=yylineno; return SD_CORNER_LIST; }

{num}						{ l->first_line=yylineno; p->vnum = strdup(yytext); return NUM; }

{str}						{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); l->first_line=yylineno; return STR; }

[[:blank:]]		{ }
\n 				{ }

. { return yytext[0]; }

%%