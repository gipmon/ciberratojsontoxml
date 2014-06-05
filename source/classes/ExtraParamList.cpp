#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "ExtraParamList.h"

using namespace std;

void ExtraParamList::addClass(ParametersClass add){
	parametersClassList->push_back(add);
}

void ExtraParamList::addParameterToClass(char* class_name, Param param){
	for (vector<ParametersClass>::iterator it = parametersClassList->begin() ; it != parametersClassList->end(); ++it){
		if(!strcmp((*it).class_name, class_name)){
			(*it).paramList->push_back(param);
			break;
		}
	}
}

vector<ParametersClass> ExtraParamList::getExtraParamList(){
	return *parametersClassList;
}

void ExtraParamList::printTest(){
	for (vector<ParametersClass>::iterator it1 = parametersClassList->begin() ; it1 != parametersClassList->end(); ++it1){
		cout << "\t" << (*it1).class_name <<"\" : [ " << endl;
			for(vector<Param>::iterator it2 = (*it1).paramList->begin() ; it2 != (*it1).paramList->end(); ++it2){
				cout << "\t\t\t\"" << (*it2).name << "\" : " << (*it2).value  << "," << endl;
			}
		cout << "\t]," << endl;
	}
}

void ExtraParamList::paramOutputXML(ofstream& file, ParamTable *param_table){

	for (vector<ParametersClass>::iterator it1 = parametersClassList->begin() ; it1 != parametersClassList->end(); ++it1){

			for(vector<Param>::iterator it2 = (*it1).paramList->begin() ; it2 != (*it1).paramList->end(); ++it2){
				if(strcmp("Erro", param_table->get_xml_name((*it1).class_name, (*it2).name))){
					file << param_table->get_xml_name((*it1).class_name, (*it2).name) << "=\""<< (*it2).value  << "\" " ;
				}
			}
	}
}
