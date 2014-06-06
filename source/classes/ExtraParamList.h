#include <iostream>
#include <vector>
#include <fstream>
#include "../param_parser/param_table.h"

using namespace std;

struct Param{
    char* name;
    char* value;
};

struct ParametersClass{
    char* class_name;
    vector<Param>  *paramList;
};

class ExtraParamList{
    private:
    vector<ParametersClass>  *parametersClassList;

	public:
    ExtraParamList(){ parametersClassList = new vector<ParametersClass>();}
    void addClass(ParametersClass add);
    void addParameterToClass(char* class_name, Param param);
    vector<ParametersClass> getExtraParamList();

    void printTest();
    void paramOutputXML(ofstream& paramFile, ParamTable *param_table);
};
