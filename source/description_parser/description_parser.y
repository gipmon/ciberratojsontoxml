%union{
	char* vstr;
	char* vnum;
	Pose* pose;
	PoseList* pl
}

%token CHALLENGE_NAME
%token CHALLENGE_TYPE
%token CYCLE_TIME
%token DURATION
%token SCENARIO_DESCRIPTION

%token CLASS_NAME  {// nome das ultimas tres classes}
%token <vstr> STR
%token <vnum> NUM


%token SD_NAME  {// SD => scenario_description}
%token SD_DIMENSIONS
%token SD_BEACONS
%token SD_TARGET_AREAS
%token SD_WALLS
%token SD_GRID
%token SD_POSITION
%token SD_RADIUS
%token SD_HEIGHT
%token SD_CORNER_LIST

%tpye <pose> POSE
%type <pl> POSE_LIST

%%

File 	: '{' OL '}' {// OL => Object List }
	
OL  	: CLASS ',' OL
		| CLASS

CLASS 	: DEFAULT_VALUES ',' OL  {// 4 primeiros atributos}
	 	| LAST_CLASSES ',' OL  {// 3 ultimos classes}   
	 	| SD ',' OL  {// senario description}
	 	;



DEFAULT_VALUES  : CHALLENGE_NAME ':' STR
				| CHALLENGE_TYPE ':' STR
				| CYCLE_TIME ':' STR
				| DURATION ':' STR
				;

SD 	: SCENARIO_DESCRIPTION ':' '{' SDL '}'
	;

SDL 	: SP ',' SDL
		: SP
		;

SP 		: SD_NAME ':' STR
		| SD_DIMENSIONS ':' DIMENSIONS
		| SD_BEACONS ':' BEACONS
		| SD_TARGET_AREAS ':' TARGET_AREAS 
		| SD_WALLS ':' WALLS
		| SD_GRID ':' GRID

NUM_PAIR    : '['NUM','NUM']'
			;

BEACONS 	: '[' BEACONS_VALUES ']'
			;

BEACONS_VALUES  : '{' SD_POSITION ':' NUM_PAIR ',' SD_RADIUS ':' NUM ',' SD_HEIGHT ':' NUM '}'
				;

TARGET_AREAS    : '[' TARGET_VALUES ']'
			    ;

TARGET_VALUES   : '{' SD_POSITION ':' NUM_PAIR ',' SD_RADIUS ':' NUM ',' SD_HEIGHT ':' NUM '}'
				;

WALLS   : '[' WALLS_VALUES ']'
		;

WALLS_VALUES : '{' SD_HEIGHT ':' NUM ',' SD_CORNER_LIST ':' '[' CORNER_LIST ']' '}' ',' WALLS_VALUE
			 | '{' SD_HEIGHT ':' NUM ',' SD_CORNER_LIST ':' '[' CORNER_LIST ']' '}'
			 ;

CORNER_LIST : NUM_PAIR , CORNER_LIST
			| NUM_PAIR
			;

GRID :  '[' POSE_LIST ']'
	 ;

POSE_LIST : POSE
		  | POSE_LIST ',' POSE
		  ;

POSE    :'[' NUM ',' NUM ',' NUM ']'
		;	

LAST_CLASSES  	: CLASS_NAME ':' '{' PL '}' 
		        ;

PL  	: PD ',' PL 
		| PD
		| /*lameda*/
		;

PD  	: PSD ':' NUM  {// PSD => Parameter name O3     STR => value O3}

%%
