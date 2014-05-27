%token CHALLENGE_NAME
%token CHALLENGE_TYPE
%token CYCLE_TIME
%token DURATION

%token 	CLASS_O3  {// vai os id dO O3}
%token STR

%token SD_NAME  {// SD => scenario_description}
%token SD_DIMENSIONS
%token SD_BEACONS
%token SD_TARGET_AREAS
%token SD_WALLS
%token SD_GRID

%token SCENARIO_DESCRIPTION
%token VP_NUM

%%

File 	: '{' OL '}' {// OL => Object List }
	
OL  	: CLASS ',' OL
		| CLASS

CLASS 	: O1 ',' OL  {// 4 primeiros atributos}
	 	| O3 ',' OL  {// 3 ultimos classes}   
	 	| O2 ',' OL  {// senario description}
	 	;



O1  	: CHALLENGE_NAME ':' STR
		| CHALLENGE_TYPE ':' STR
		| CYCLE_TIME ':' STR
		| DURATION ':' STR
		;

O2  	: SCENARIO_DESCRIPTION ':' '{' SDL '}'
		;

SDL 	: SP ',' SDL
		: SP
		;

SP 		: SD_NAME ':' STR
		| SD_DIMENSIONS ':' VP
		| SD_BEACONS ':' 
		| SD_TARGET_AREAS ':'
		| SD_WALLS ':'
		| SD_GRID ':'

VP      : '['VP_NUM','VP_NUM']'
		;

O3  	: CLASS_O3 ':' '{' PL '}' 
		;

PL  	: PD ',' PL 
		| PD
		;

PD  	: PO3 ':' STR  {// PO3 => Parameter name O3     STR => value O3}

%%
