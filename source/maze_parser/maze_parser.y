%union{
	char* vstr;
	char* vnum;
}

%{
    #include <stdio.h>
    #include <string>
	//#include "param_parser/param_table.h"

	extern int maze_parse(const char* fname);
	extern FILE* yyin;

	int maze_error(YYLTYPE* l, const char* fname, const char *s);
    int maze_lex(YYSTYPE*, YYLTYPE* l);

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



DEFAULT_VALUES  : CHALLENGE_NAME ':' STR
				| CHALLENGE_TYPE ':' STR
				| CYCLE_TIME ':' NUM
				| DURATION ':' NUM
				;

SD 	: SCENARIO_DESCRIPTION ':' '{' SDL '}'
	;

SDL 	: SP ',' SDL
		| SP
		;

SP 		: SD_NAME ':' STR
		| SD_DIMENSIONS ':' NUM_PAIR
		| SD_BEACONS ':' BEACONS
		| SD_TARGET_AREAS ':' TARGET_AREAS
		| SD_WALLS ':' WALLS
		| SD_GRID ':' GRID
		;

NUM_PAIR    : '['NUM','NUM']'
			;


BEACONS 	: '[' BEACONS_VALUES ']'
			;

BEACONS_VALUES  : '{' SD_POSITION ':' NUM_PAIR ',' SD_RADIUS ':' NUM ',' SD_HEIGHT ':' NUM '}'
				;

TARGET_AREAS    : '[' TARGET_VALUES ']'
			    ;

TARGET_VALUES   : '{' SD_POSITION ':' NUM_PAIR ',' SD_RADIUS ':' NUM '}'
				;

WALLS   : '[' WALLS_VALUES ']'
		;

WALLS_VALUES : '{' SD_HEIGHT ':' NUM ',' SD_CORNER_LIST ':' '[' CORNER_LIST ']' '}' ',' WALLS_VALUES
			 | '{' SD_HEIGHT ':' NUM ',' SD_CORNER_LIST ':' '[' CORNER_LIST ']' '}'
			 ;

CORNER_LIST : NUM_PAIR ',' CORNER_LIST
			| NUM_PAIR
			;

GRID :  '[' POSE_LIST ']'
	 ;

POSE_LIST : POSE
		  | POSE_LIST ',' POSE
		  ;

POSE    :'[' NUM ',' NUM ',' NUM ']'
		;

LAST_CLASSES  	: STR ':' '{' PL '}'
		        ;

PL  	: PD ',' PL
		| PD
		| /*lameda*/
		;

PD  	: STR ':' NUM
		;

%%

int main(int argc, char* argv[]){
	if((yyin = fopen(argv[1], "r")) == NULL){
		printf("ERRRO!\n");
		return 0;
	}
	maze_parse(argv[1]);
	printf("FUNCIONOU\n");
	return 1;
}

int maze_error(YYLTYPE* l, const char* fname, const char *s){
	extern char* yytext;
	printf("%s: %d: %s; conteudo no yytext: '%s'\n", fname, l->first_line, s, yytext);
    exit(1);
}
