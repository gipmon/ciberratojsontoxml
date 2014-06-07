%{
    #include <stdlib.h>
    #include <string.h>
    #include <stdint.h>
	#include <vector>
    #include "../classes/Point.h"
    #include "../maze_parser.tab.h"

    #define YY_DECL int maze_lex(YYSTYPE* p, YYLTYPE* loc)

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
%option prefix="maze_"

nint    			[0-9]+

num     			{nint}|{nint}\.{nint}|\-{nint}|\-{nint}\.{nint}

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

sd_models 			["]models["]

model_fp			["]first[ ]point["]

model_sp 			["]second[ ]point["]

%%

							static int col = 1;

{challenge_name}			{ UPDATE_LOC; return CHALLENGE_NAME; }

{challenge_type} 			{ UPDATE_LOC; return CHALLENGE_TYPE; }

{cycle_time} 				{ UPDATE_LOC; return CYCLE_TIME; }

{duration}					{ UPDATE_LOC; return DURATION; }

{scenario_description}		{ UPDATE_LOC; return SCENARIO_DESCRIPTION; }

{sd_name}					{ UPDATE_LOC; return SD_NAME; }

{sd_dimensions}				{ UPDATE_LOC; return SD_DIMENSIONS; }

{sd_becons}					{ UPDATE_LOC; return SD_BEACONS; }

{sd_target_areas}			{ UPDATE_LOC; return SD_TARGET_AREAS; }

{sd_walls}					{ UPDATE_LOC; return SD_WALLS; }

{sd_grid}					{ UPDATE_LOC; return SD_GRID; }

{sd_position}				{ UPDATE_LOC; return SD_POSITION; }

{sd_radius}					{ UPDATE_LOC; return SD_RADIUS; }

{sd_height}					{ UPDATE_LOC; return SD_HEIGHT; }

{thickness}					{ UPDATE_LOC; return THICKNESS; }

{sd_models} 				{ UPDATE_LOC; return SD_MODELS; }

{model_fp}					{ UPDATE_LOC; return MODEL_FP; }

{model_sp} 					{ UPDATE_LOC; return MODEL_SP; }

{sd_corner_list}			{ UPDATE_LOC; return SD_CORNER_LIST; }

{num}						{ UPDATE_LOC; p->vnum = strdup(yytext); return NUM; }

{str}						{ yytext[strlen(yytext)-1] = '\0'; p->vstr = strdup(yytext+1); UPDATE_LOC; return STR; }

[[:blank:]]		{ col++; }
\n 				{ col = 1; }

. { return yytext[0]; }

%%
