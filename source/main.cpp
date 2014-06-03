#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include "main.h"
#include <cstdlib>

using namespace std;

ParamTable *param_table = new ParamTable();
Challenge *challenge = new Challenge();

void warning_message(){
	printf("OPTIONS:\n-p : print tables\n-o : output to xml\nIt should be passed the two files .json!\n\nExample:\n./main.output -o ../exemplos/json/param-list.json ../exemplos/json/example.json\n./main.output -p ../exemplos/json/param-list.json ../exemplos/json/example.json\n./main.output -p -o ../exemplos/json/param-list.json ../exemplos/json/example.json");
}

int main(int argc, char* argv[]){
    
	/* validação dos argumentos */
	if(argc<4){
		warning_message();
		return 0;
	}

	/* options via terminal */
	int print = 0;
	int output = 0;


	if(!strcmp("-p", argv[1]) || !strcmp("-p", argv[2])){
		print = 1;
	}
	if(!strcmp("-o", argv[1]) || !strcmp("-o", argv[2])){
		output = 1;
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

	if((param_in = fopen(argv[arg++], "r")) == NULL){
		printf("[ERROR!] %d must be a .json file!\n", arg-1);
		return 0;
	}

	try{
		param_parse(argv[1]);
	}catch(int e){
		ErrorHandling(e);
	}

	if(print){
		param_table->print_symboltable();
	}

	if((maze_in = fopen(argv[arg], "r")) == NULL){
		printf("[ERROR!] %d must be a .json file!\n", arg);
		return 0;
	}

	try{
		maze_parse(argv[2]);
	}catch(int e){
		ErrorHandling(e);
	}

	if(print){
		challenge->printTest();
	}

	if(output){
		system("rm -rf ./xml");
		system("mkdir ./xml");
		ofstream labFile("./xml/Lab.xml");
		ofstream gridFile("./xml/Grid.xml");
		ofstream paramFile("./xml/Param.xml");

		gridOutputXML(gridFile);
		labOutputXML(labFile);
		paramOutputXML(paramFile, param_table);
	}

	return 1;
}

void gridOutputXML(ofstream& file){
	challenge->gridOutputXML(file);
}

void labOutputXML(ofstream& file){
	challenge->labOutputXML(file);
}

void paramOutputXML(ofstream& file, ParamTable *param_table){
	challenge->paramOutputXML(file, param_table);
}

void ErrorHandling(int NUM){
	extern char* param_name;
    extern char* class_name;

	printf("[ERROR!] Error description below:\n");
	switch (NUM){
	    case PARAMETER_ALREADY_EXISTS    	 	: printf("The parameter \"%s\" already exists in \"%s\" class.\n", param_name, class_name); break;
	    case PARAMETER_CLASS_NAME_REQUIRED	 	: printf("The class name is required for the parameter \"%s\".\n", param_name); break;
		case PARAMETER_VALUE_TYPE_REQUIRED    	: printf("The value type is required for the parameter \"%s\" in \"%s\" class.\n", param_name, class_name);   break;
		case PARAMETER_NAME_REQUIRED 			: printf("The class name is required!\n"); break;
	    default            				 		: printf("unknown error");
	}
	exit(0);
}

