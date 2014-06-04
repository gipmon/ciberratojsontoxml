#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include "main.h"

using namespace std;

ParamTable *param_table = new ParamTable();
Challenge *challenge = new Challenge();

void warning_message(){
	printf("OPTIONS:\n-p : print tables\n-o : output to xml\nIt should be passed the two files .json!\n\nExample:\n./main.output -o ../exemplos/json/param-list.json ../exemplos/json/example.json\n./main.output -p ../exemplos/json/param-list.json ../exemplos/json/example.json\n./main.output -p -o ../exemplos/json/param-list.json ../exemplos/json/example.json");
}

int main(int argc, char* argv[]){
	int option;

	if(argc<4){
		option  = menu(argc, argv);
	}else{
		return commandLineTools(argc, argv);
	}
	
	switch(option){
		case 1:
			printf("\nIntroduza o nome do ficheiro parameters list: ");

	}
}

int menu(int argc, char* argv[]){
	int b, isDigit;
	printf("MENU:\n1 - Read parameters list file (.json)\n2 - Read challenge parameters file (.json)\n3 - Print to XML\n4 - Print URDF\n5 - Walls options (Models)\n0 - End Program\nOpção: ");
	do{
		cin >> b;
		cin.clear();
		cin.ignore(80,'\n');
		
		//isDigit = isdigit(b);

		if(/*!isDigit ||*/ b < 1 || b > 5){
			printf("Introduza uma opção válida: ");
		}
	}while(/*!isDigit ||*/ b < 1 || b > 5);

	return b;
}

int commandLineTools(int argc, char* argv[]){
	/* options via terminal */
	int print = 0;
	int output = 0;
	int output_set = 0;


	if(!strcmp("-p", argv[1]) || !strcmp("-p", argv[2])){
		print = 1;
	}
	if(!strcmp("-o", argv[1]) || !strcmp("-o", argv[2])){
		output = 1;
	}
	if(output && (!strcmp("-s", argv[2]) || !strcmp("-s", argv[3]))){
		output_set = 1;
	}

	if(!print && !output){
		warning_message();
		return 0;
	}

	/* name files */
	int arg = 1;
	if(print){
		arg++;
	}
	if(output){
		arg++;
	}
	if(output_set){
		arg++;
	}

	if((param_in = fopen(argv[arg], "r")) == NULL){
		printf("[ERROR!] %d must be a .json file!\n", arg-1);
		return 0;
	}

	try{
		param_parse(argv[arg++]);
	}catch(int e){
		ErrorHandlingWithExit(e);
	}

	if(print){
		param_table->print_symboltable();
	}

	if((maze_in = fopen(argv[arg], "r")) == NULL){
		printf("[ERROR!] %d must be a .json file!\n", arg);
		return 0;
	}

	try{
		maze_parse(argv[arg++]);
	}catch(int e){
		ErrorHandlingWithExit(e);
	}

	if(print){
		challenge->printTest();
	}

	if(output){
		if(output_set){
			ofstream labFile(argv[arg++]);
			ofstream gridFile(argv[arg++]);
			ofstream paramFile(argv[arg++]);
	    	ofstream URDFFile(argv[arg++]);

			gridOutputXML(gridFile);
			labOutputXML(labFile);
			paramOutputXML(paramFile, param_table);
	    	URDFOutput(URDFFile);
		}else{
			system("rm -rf ./xml");
			system("mkdir ./xml");
	      
		    system("rm -rf ./urdf");
		    system("mkdir ./urdf");
		      
			ofstream labFile("./xml/Lab.xml");
			ofstream gridFile("./xml/Grid.xml");
			ofstream paramFile("./xml/Param.xml");
	    	ofstream URDFFile("./urdf/URDF.xml");

			gridOutputXML(gridFile);
			labOutputXML(labFile);
			paramOutputXML(paramFile, param_table);
	    	URDFOutput(URDFFile);
		}
	}

	return 1;
}

/********** PRINTS **********/
void gridOutputXML(ofstream& file){
	challenge->gridOutputXML(file);
}

void labOutputXML(ofstream& file){
	challenge->labOutputXML(file);
}

void paramOutputXML(ofstream& file, ParamTable *param_table){
	challenge->paramOutputXML(file, param_table);
}

void URDFOutput(ofstream& file){
    challenge->URDFOutput(file);
}

/********** ERROR **********/
void ErrorHandlingWithExit(int NUM){
	extern char* param_name;
    extern char* class_name;
    extern parameter param;
    extern char* default_value_type;

	printf("[SEMANTIC ERROR!] Error description below:\n");
	switch (NUM){
	    case PARAMETER_ALREADY_EXISTS    	 	: printf("The parameter \"%s\" already exists in \"%s\" class.\n", param_name, class_name); break;
	    case PARAMETER_CLASS_NAME_REQUIRED	 	: printf("The class name is required for the parameter \"%s\".\n", param_name); break;
		case PARAMETER_VALUE_TYPE_REQUIRED    	: printf("The value type is required for the parameter \"%s\" in \"%s\" class.\n", param_name, class_name);   break;
		case PARAMETER_NAME_REQUIRED 			: printf("The class name is required!\n"); break;
		case DEFAULT_VALUE_WRONG_BY_TYPE		: printf("The default value is wrong by value type in the parameter \"%s\" in \"%s\" class, expecting %s but as given %s.\n", param_name, class_name, param.value_type, default_value_type);   break;
	    default            				 		: printf("unknown error");
	}
	exit(0);
	/* SKYP OR EXIT? */
}
