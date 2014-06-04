%{
	#include "classes/Point.h"
    #include <stdio.h>
    #include <stdlib.h>
	#include <vector>
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

File 	: '{' OL '}'
		;

OL  	: CLASS ',' OL
		| CLASS
		;

CLASS 	: DEFAULT_VALUES
	 	| LAST_CLASSES
	 	| SD
	 	;

/* nem sempre os default_values vem primeiro, é preciso ter cuidado e verificar se estes parametros e outros estao definidos */

DEFAULT_VALUES  : CHALLENGE_NAME ':' STR {challenge->setChallengeName($3);}
				| CHALLENGE_TYPE ':' STR {challenge->setChallengeType($3);}
				| CYCLE_TIME ':' NUM {challenge->setCycleTime(atoi($3));}
				| DURATION ':' NUM {challenge->setDuration(atoi($3));}
				;

SD 	: SCENARIO_DESCRIPTION ':' '{' SDL '}'
	;

SDL 	: SP ',' SDL
		| SP
		;

SP 		: SD_NAME ':' STR { challenge->maze->setName($3); }
		| SD_DIMENSIONS ':' NUM_PAIR {challenge->maze->setDimensions($3->getX(), $3->getY());}
		| SD_BEACONS ':' BEACONS
		| SD_TARGET_AREAS ':' TARGET_AREAS
		| SD_WALLS ':' WALLS
		| SD_GRID ':' GRID
		;

NUM_PAIR    : '['NUM','NUM']' { Point *pt = new Point(atof($2), atof($4)); $$ = pt;}
			;


BEACONS 	: '[' BEACONS_VALUES ']'
			;

BEACONS_VALUES  : '{' SD_POSITION ':' NUM_PAIR ',' SD_HEIGHT ':' NUM '}' {challenge->maze->addBeacon(*$4, atoi($8));}
				;

TARGET_AREAS    : '[' TARGET_VALUES ']'
			    ;

TARGET_VALUES   : '{' SD_POSITION ':' NUM_PAIR ',' SD_RADIUS ':' NUM '}' {challenge->maze->addTargetArea(*$4, atoi($8));}
				;

WALLS   : '[' WALLS_VALUES ']'
		;

WALLS_VALUES : WALLS_VALUE ',' WALLS_VALUES
			 | WALLS_VALUE
			 ;

/* falta o thickness */
WALLS_VALUE : '{' SD_HEIGHT ':' NUM ',' SD_CORNER_LIST ':' '[' CORNER_LIST ']' '}' {challenge->maze->addWall(atoi($4), 0, vpoint); vpoint = new vector<Point>();}
			|'{' SD_HEIGHT ':' NUM ',' THICKNESS ':' NUM ',' SD_CORNER_LIST ':' '[' CORNER_LIST ']' '}' {challenge->maze->addWall(atoi($4), atof($8), vpoint); vpoint = new vector<Point>();}

CORNER_LIST : NUM_PAIR ',' CORNER_LIST { vpoint->push_back(*$1);}
			| NUM_PAIR { vpoint->push_back(*$1);}
			;

GRID :  '[' POSE_LIST ']'
	 ;

POSE_LIST : POSE
		  | POSE_LIST ',' POSE
		  ;

POSE    :'[' NUM ',' NUM ',' NUM ']' { challenge->maze->addPose(atof($2), atof($4), atof($6)); }
		;

LAST_CLASSES  	: STR {pc->class_name = $1; pc->paramList = new vector<Param>(); challenge->pm->addClass(*pc); } ':' '{' PL '}' {pc = new ParametersClass();}
		        ;

PL  	: PD ',' PL
		| PD
		| /*lameda*/
		;

PD  	: STR ':' NUM { Param tmp; tmp.name = $1; tmp.value = $3; challenge->pm->addParameterToClass(pc->class_name, tmp);}
		;

%%

int maze_error(YYLTYPE* l, const char* fname, const char *s){
	extern char* maze_text;
	printf("%s: %d: %s; conteudo no yytext: '%s'\n", fname, l->first_line, s, maze_text);
    exit(1);
}
