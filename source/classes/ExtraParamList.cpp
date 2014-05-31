#include <iostream>
#include <vector>
#include <cstring>
#include "ExtraParamList.h"

/* http://www.cplusplus.com/reference/std::vector/std::vector/ */

void ExtraParamList::addClass(ParametersClass add){
	parametersClassList->push_back(add);
}

void ExtraParamList::addParameterToClass(char* class_name, Param param){
	for (std::vector<ParametersClass>::iterator it = parametersClassList->begin() ; it != parametersClassList->end(); ++it){
		if(!strcmp((*it).class_name, class_name)){
			(*it).paramList->push_back(param);
			break;
		}
	}
}

std::vector<ParametersClass> ExtraParamList::getExtraParamList(){
	return *parametersClassList;
}

void ExtraParamList::printTest(){
	for (std::vector<ParametersClass>::iterator it1 = parametersClassList->begin() ; it1 != parametersClassList->end(); ++it1){
		std::cout << "\t" << (*it1).class_name <<"\" : [ " << std::endl;
			for(std::vector<Param>::iterator it2 = (*it1).paramList->begin() ; it2 != (*it1).paramList->end(); ++it2){
				std::cout << "\t\t\t\"" << (*it2).name << "\" : " << (*it2).value  << "," << std::endl;
			}
		std::cout << "\t]," << std::endl;
	}
}
