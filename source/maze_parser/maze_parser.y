%{
	#include "classes/Point.h"
    #include <stdio.h>
    #include <stdlib.h>
	#include <vector>
	#include <string.h>
%}

%union{
	char* vstr;
	char* vnum;
	Point* vpair;
}

%{
    #include "main.h"

	int maze_error(YYLTYPE* l, const char* fname, const char *s);
    int maze_lex(YYSTYPE*, YYLTYPE* l);

	vector<Point> *vpoint = new vector<Point>();
	ParametersClass *pc = new ParametersClass();

	extern Error error;

%}

%token CHALLENGE_NAME
%token CHALLENGE_TYPE
%token CYCLE_TIME
%token DURATION
%token SCENARIO_DESCRIPTION

%token CLASS_NAME
%token <vstr> STR
%token <vnum> NUM

%token SD_NAME
%token SD_DIMENSIONS
%token SD_BEACONS
%token SD_TARGET_AREAS
%token SD_WALLS
%token SD_GRID
%token SD_POSITION
%token SD_RADIUS
%token SD_HEIGHT
%token SD_CORNER_LIST
%token THICKNESS
%token SD_MODELS
%token MODEL_FP
%token MODEL_SP

%type<vpair> NUM_PAIR

%parse-param {const char* fname}
%pure-parser
%defines
%error-verbose
%locations
/*%verbose*/
%name-prefix="maze_"

%start File

%%

File 	: '{' OL '}' { tmp_challenge->validateDefaultValues(); tmp_challenge->validateScenarioDescription(); }
		;

OL  	: CLASS ',' OL
		| CLASS
		;

CLASS 	: DEFAULT_VALUES
	 	| LAST_CLASSES
	 	| SD
	 	;

/* nem sempre os default_values vem primeiro, é preciso ter cuidado e verificar se estes parametros e outros estao definidos */

DEFAULT_VALUES  : CHALLENGE_NAME ':' STR {tmp_challenge->setChallengeName($3);}
				| CHALLENGE_TYPE ':' STR {tmp_challenge->setChallengeType($3);}
				| CYCLE_TIME ':' NUM {error.num = $3; error.line = @3.first_line; error.column = @3.first_column; error.fname = fname; tmp_challenge->validateIntType($3); if(atoi($3) == 0){ throw CYCLE_TIME_ZERO; } tmp_challenge->setCycleTime(atoi($3));}
				| DURATION ':' NUM {error.num = $3; error.line = @3.first_line; error.column = @3.first_column; error.fname = fname; tmp_challenge->validateIntType($3); if(atoi($3) == 0){ throw DURATION_ZERO; }tmp_challenge->setDuration(atoi($3));}
				;

SD 	: SCENARIO_DESCRIPTION ':' '{' SDL '}'
	;

SDL 	: SP ',' SDL
		| SP
		;

SP 		: SD_NAME ':' STR { tmp_challenge->maze->setName($3); }
		| SD_DIMENSIONS ':' NUM_PAIR {error.line = @3.first_line; error.column = @3.first_column; error.fname = fname; if($3->getX() <= 0){ error.d = $3->getX(); throw WRONG_DIMENSIONS; } if($3->getY() <= 0){ error.d = $3->getY(); throw WRONG_DIMENSIONS; } tmp_challenge->maze->setDimensions($3->getX(), $3->getY());}
		| SD_BEACONS ':' BEACONS
		| SD_TARGET_AREAS ':' TARGET_AREAS
		| SD_WALLS ':' WALLS
		| SD_GRID ':' GRID
		| SD_MODELS ':' '[' MODELS ']'
		;

MODELS 	: MODEL ',' MODELS
		| MODEL
		;

MODEL 	: '{' SD_NAME ':' STR ',' SD_HEIGHT ':' NUM ',' THICKNESS ':' NUM ',' MODEL_FP ':'  NUM_PAIR ',' MODEL_SP ':' NUM_PAIR '}' {error.fname = fname; if(atof($8) <= 0){ error.num = $8; error.line = @8.first_line; error.column = @8.first_column; throw INVALID_MODEL_HEIGHT; } if(atof($12) < 0){ error.num = $12; error.line = @12.first_line; error.column = @12.first_column; throw THICKNESS_MODEL_ERROR; } tmp_challenge->maze->addModel($4, atof($8), *$16, *$20, atof($12));}
		;

NUM_PAIR    : '['NUM','NUM']' { Point *pt = new Point(atof($2), atof($4)); $$ = pt;}
			;


BEACONS 	: '[' BEACONS_VALUES ']'
			;

BEACONS_VALUES : BEACONS_VALUE ',' BEACONS_VALUES
			   | BEACONS_VALUE
			   ;

BEACONS_VALUE  : '{' SD_POSITION ':' NUM_PAIR ',' SD_HEIGHT ':' NUM '}' {if(atof($8) <= 0){ error.num = $8; error.line = @8.first_line; error.column = @8.first_column; error.fname = fname; throw INVALID_BEACON_HEIGHT; } tmp_challenge->maze->addBeacon(*$4, atoi($8));}
				;

TARGET_AREAS    : '[' TARGET_VALUES ']'
			    ;

TARGET_VALUES : TARGET_VALUE ',' TARGET_VALUES
			  | TARGET_VALUE
			  ;

TARGET_VALUE   : '{' SD_POSITION ':' NUM_PAIR ',' SD_RADIUS ':' NUM '}' {if(atof($8) <= 0){ error.num = $8; error.line = @8.first_line; error.column = @8.first_column; error.fname = fname; throw NULL_TARGET_RADIUS; } tmp_challenge->maze->addTargetArea(*$4, atoi($8));}
				;

WALLS   : '[' WALLS_VALUES ']'
		;

WALLS_VALUES : WALLS_VALUE ',' WALLS_VALUES
			 | WALLS_VALUE
			 ;

WALLS_VALUE : '{' SD_HEIGHT ':' NUM ',' SD_CORNER_LIST ':' '[' CORNER_LIST ']' '}' {error.fname = fname; if(atof($4) <= 0){ error.num = $4; error.line = @4.first_line; error.column = @4.first_column; throw INVALID_WALL_HEIGHT; }tmp_challenge->maze->addWall(atoi($4), 0, vpoint); vpoint = new vector<Point>();}
			|'{' SD_HEIGHT ':' NUM ',' THICKNESS ':' NUM ',' SD_CORNER_LIST ':' '[' CORNER_LIST ']' '}' {error.fname = fname; if(atof($4) <= 0){ error.num = $4; error.line = @4.first_line; error.column = @4.first_column; throw INVALID_WALL_HEIGHT; } if(atof($8) < 0){ error.num = $8; error.line = @8.first_line; error.column = @8.first_column; throw INVALID_WALL_THICKNESS; } tmp_challenge->maze->addWall(atoi($4), atof($8), vpoint); vpoint = new vector<Point>();}
			;

CORNER_LIST : NUM_PAIR ',' CORNER_LIST { vpoint->push_back(*$1);}
			| NUM_PAIR { vpoint->push_back(*$1);}
			;

GRID :  '[' POSE_LIST ']'
	 ;

POSE_LIST : POSE
		  | POSE_LIST ',' POSE
		  ;

POSE    :'[' NUM ',' NUM ',' NUM ']' { tmp_challenge->maze->addPose(atof($2), atof($4), atof($6)); }
		;

LAST_CLASSES  	: STR {pc->class_name = $1; if(!param_table->class_exists($1)){ throw CLASS_DOESNT_EXIST_IN_PT; } pc->paramList = new vector<Param>(); tmp_challenge->pm->addClass(*pc); } ':' '{' PL '}' {pc = new ParametersClass();}
		        ;

PL  	: PD ',' PL
		| PD
		| /*lameda*/
		;

PD  	: STR ':' STR { error.num = $3; error.line = @3.first_line; error.column = @3.first_column; error.fname = fname; error.s = $1; if(!param_table->parameter_exists(pc->class_name, $1)){ throw PARAMETER_DOESNT_EXISTS; } tmp_challenge->validateTypes(param_table->get_value_type(pc->class_name, $1), $3); Param tmp; tmp.name = $1; tmp.value = $3; tmp_challenge->pm->addParameterToClass(pc->class_name, tmp); }
		| STR ':' NUM { error.num = $3; error.line = @3.first_line; error.column = @3.first_column; error.fname = fname; error.s = $1; if(!param_table->parameter_exists(pc->class_name, $1)){ throw PARAMETER_DOESNT_EXISTS; } tmp_challenge->validateTypes(param_table->get_value_type(pc->class_name, $1), $3); Param tmp; tmp.name = $1; tmp.value = $3; tmp_challenge->pm->addParameterToClass(pc->class_name, tmp);}
		;

%%

int maze_error(YYLTYPE* l, const char* fname, const char *s){
	extern char* maze_text;
	extern Error error;
	error.fname = fname;
	error.line = l->first_line;
	error.column = l->first_column;
	error.s = strdup(s);
	error.yytext = maze_text;
	
	throw PARSING_ERROR;
}
