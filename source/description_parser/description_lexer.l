%{
    #include <stdlib.h>
    #include "example_parser.tab.h"

    #define YY_DECL int yylex(YYSTYPE* p, YYLTYPE* l)

%}

%option noyywrap
%option nounput
%option noinput
%option yylineno

str    				["][^"\n]*["]

num 				[0-9]+

challenge_name 		["]challenge name["]

challenge_type 		["]challenge type["]

cycle_time 			["]cycle time["]

duration 			["]duration["]

scenario_description ["]scenario description["]

class name ...........LOADING 12%............

sd_name 			["]name["]

sd_dimensions       ["]dimensions["]

sd_becons   		["]beacons["]

sd_target_areas     ["]target areas["]

sd_walls 			["]walls["]

sd_grid				["]grid["]

%%

{challenge_name}			{return CHALLENGE_NAME;}

{challenge_type} 			{return CHALLENGE_TYPE;}

{cycle_time} 				{return CYCLE_TIME;}

{duration}					{return DURATION;}

{scenario_description}		{return SCENARIO_DESCRIPTION;}

{sd_name}					{return SD_NAME;}

{sd_dimensions}				{return SD_DIMENSIONS;}

{sd_becons}					{return SD_BEACONS;}

{sd_target_areas}			{return SD_TARGET_AREAS;}

{sd_walls}					{return SD_WALLS;}

{sd_grid}					{return SD_GRID;}

%%
	