#ifndef MAIN_H
#define MAIN_H

#include "classes/Challenge.h"
#include "param_parser/param_table.h"
#include <iostream>
#include <fstream>

using namespace std;

extern Challenge *challenge;
extern ParamTable *param_table;

extern int maze_parse(const char* fname);
extern int param_parse(const char* fname);
extern FILE* param_in;
extern FILE* maze_in;

void gridOutputXML();
void labOutputXML(ofstream& file);

#endif
