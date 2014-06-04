#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <tr1/regex>
#include "main.h"

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

	return 1;
}
/**********PRINTS**********/
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

/**********ERROS**********/
void ErrorHandling(int NUM){
	extern char* param_name;
    extern char* class_name;

	printf("[ERROR!] Error description below:\n");
	switch (NUM){
	    case PARAMETER_ALREADY_EXISTS    	 	: printf("The parameter \"%s\" already exists in \"%s\" class.\n", param_name, class_name); break;
	    case PARAMETER_CLASS_NAME_REQUIRED	 	: printf("The class name is required for the parameter \"%s\".\n", param_name); break;
		case PARAMETER_VALUE_TYPE_REQUIRED    	: printf("The value type is required for the parameter \"%s\" in \"%s\" class.\n", param_name, class_name);   break;
		case PARAMETER_NAME_REQUIRED 			: printf("The class name is required!\n"); break;
		case DEFAULT_VALUE_WRONG_BY_TYPE		: printf("The default value is worng by value type in the parameter \"%s\" in \"%s\" class.\n", param_name, class_name);   break;
		case VALUE_TYPE_IS_NOT_CONSIDERED		: printf("The value type isn't considered");   break;
	    default            				 		: printf("unknown error");
	}
	exit(0);
}

bool validateValuebyType(char* type, char* value){
	if(!strcmp(type, "uint")){
		/*
		regex integer("(\\+|-)?[[:digit:]]+");
   		if(std::tr1::regex_match(value, integer)){
   			return true;
   		}else{
            return false;
        }
        */
        return true;
	}else if(!strcmp(type, "double")){
		/*
		double tmp = atof(value);
		char* tmp_int;
		sprintf(tmp_int , "%lf" , tmp);

		if(strcmp(value, tmp_int)){
			return false;
		}else{
			return true;
		}
		*/
		return true;
	}else if(!strcmp(type, "boolean")){
		if(strcmp(value, "0") && strcmp(value, "1") && strcmp(value, "true") && strcmp(value, "false")){
			return false;
		}else{
			return true;
		}
	}else if(!strcmp(type, "switch")){
		if(strcmp(value,"on") && strcmp(value, "off") && strcmp(value, "0") && strcmp(value,"1")){
			return false;
		}else{
			return true;
		}	
	}else if(!strcmp(type, "string")){
		return true;
	}else{
		throw VALUE_TYPE_IS_NOT_CONSIDERED;
	}
}
