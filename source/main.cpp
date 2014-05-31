#include "main.h"
#include <stdio.h>

ParamTable *param_table = new ParamTable();
Challenge *challenge = new Challenge();

int main(int argc, char* argv[]){
	if((param_in = fopen(argv[1], "r")) == NULL){
		printf("ERRRO 1 argumento!\n");
		return 0;
	}
	param_parse(argv[1]);
	param_table->print_symboltable();

	if((maze_in = fopen(argv[2], "r")) == NULL){
		printf("ERRRO 2 argumento!\n");
		return 0;
	}
	maze_parse(argv[2]);

	printf("FUNCIONOU\n");
	return 1;
}
