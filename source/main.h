#ifndef MAIN_H
#define MAIN_H

#include "classes/Challenge.h"
#include "error.h"

#include <iostream>
#include <fstream>

using namespace std;

extern Challenge *challenge;
extern ParamTable *param_table;

extern int maze_parse(const char* fname);
extern int param_parse(const char* fname);
extern FILE* param_in;
extern FILE* maze_in;

/************************ Prótotipos das funções ************************/
struct Error{
	char* fname;
	int line;
	char* s;
	char* yytext;
};

void gridOutputXML(ofstream& file);
void labOutputXML(ofstream& file);
void paramOutputXML(ofstream& file, ParamTable *param_table);
void URDFOutput(ofstream& file);
void ErrorHandlingWithExit(int);
void ErrorHandling(int);
int  menu(int argc, char* argv[]);
int  commandLineTools(int argc, char* argv[]);

#endif
