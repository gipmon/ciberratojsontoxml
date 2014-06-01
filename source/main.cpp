#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include "main.h"


using namespace std;

ParamTable *param_table = new ParamTable();
Challenge *challenge = new Challenge();

void warning_message(){
	printf("OPTIONS:\n-p : print tables\n-o : output to xml\nIt should be passed the two files .json!\n\nExample:\n./main.output -o ../exemplos/json/param-list.json ../exemplos/json/example.json\n./main.output -p ../exemplos/json/param-list.json ../exemplos/json/example.json\n./main.output -p -o ../exemplos/json/param-list.json ../exemplos/json/example.json");
}

int main(int argc, char* argv[]){
	/* validação dos argumentos */
	if(argc==1){
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
		printf("ERRRO %d must be a .json file!\n", arg-1);
		return 0;
	}
	param_parse(argv[1]);

	if(print){
		param_table->print_symboltable();
	}

	if((maze_in = fopen(argv[arg], "r")) == NULL){
		printf("ERRRO %d must be a .json file!\n", arg);
		return 0;
	}
	maze_parse(argv[2]);

	if(print){
		challenge->printTest();
	}

	if(output){
		ofstream labFile("Lab.xml");
		ofstream gridFile("Grid.xml");
		ofstream paramFile("Param.xml");

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
