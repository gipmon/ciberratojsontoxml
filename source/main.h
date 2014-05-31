#ifndef MAIN_H
#define MAIN_H

#include "classes/Challenge.h"
#include "param_parser/param_table.h"

extern Challenge *challenge;
extern ParamTable *param_table;

extern int maze_parse(const char* fname);
extern int param_parse(const char* fname);
extern FILE* param_in;
extern FILE* maze_in;

#endif