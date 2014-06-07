#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "ExtraParamList.h"

using namespace std;

void ExtraParamList::addClass(ParametersClass add){
	parametersClassList->push_back(add);
}

bool ExtraParamList::existsClass(char* class_name){
	for (vector<ParametersClass>::iterator it = parametersClassList->begin() ; it != parametersClassList->end(); ++it){
		if(!strcmp((*it).class_name, class_name)){
			return true;
		}
	}
	return false;
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

bool ExtraParamList::isDefined(char* class_name, char* param_name){
	for (vector<ParametersClass>::iterator it1 = parametersClassList->begin() ; it1 != parametersClassList->end(); ++it1){
		if(!strcmp((*it1).class_name, class_name)){
			for(vector<Param>::iterator it2 = (*it1).paramList->begin() ; it2 != (*it1).paramList->end(); ++it2){
				if(!strcmp((*it2).name, param_name)){
					return true;
				}
			}
		}
	}
	return false;
}

void ExtraParamList::setParametersWithDefaultValues(){
	extern ParamTable *param_table;

	/* quando um parâmetro tem um default value associado e não foi definido no challange.json deve ser inserido na table final! */
	map<char*, map<char*, parameter> > param_map = param_table->getParamMap();	
	
	for(map<char*, map<char*, parameter> >::iterator it1 = param_map.begin(); it1 != param_map.end(); it1++) {
        for(map<char*, parameter>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++){
        	if(it2->second.default_value != NULL && it2->second.default_value[0] != '\0'){
        		if(!isDefined(it1->first, it2->first)){
        			if(!existsClass(it1->first)){
        				ParametersClass *pc = new ParametersClass();
        				pc->class_name = it1->first;
        				pc->paramList = new vector<Param>();
        				addClass(*pc);
        			}
        			Param tmp;
        			tmp.name = it2->first;
        			tmp.value = it2->second.default_value;
        			addParameterToClass(it1->first, tmp);
        		}
        	}
        }
    }
}
