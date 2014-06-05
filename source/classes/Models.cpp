#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "Models.h"

using namespace std;

void Models::addModel(Model add){
	modelsList->push_back(add);
}

vector<Model> Models::getModelsList(){
	return *modelsList;
}

void Models::printTest(){
	cout << "\tmodels\" : [ " << endl;

	for (vector<Model>::iterator it = modelsList->begin() ; it != modelsList->end(); ++it){
		cout << "\n\t\t" << "{  name: " <<  (*it).name << "}\n\t] height: \"" <<  (*it).height << "\" first point\" : [" << (*it).first_point.getX() << ", " << (*it).first_point.getY() << "], \"second_point \" : [" << (*it).second_point.getX() << ", " << (*it).second_point.getY() << "], thickness: " <<  (*it).thickness << "}\n\t]," << endl;
	}
}

Model Models::getModel(char* name){
	for (vector<Model>::iterator it = modelsList->begin() ; it != modelsList->end(); ++it){
		if(!strcmp((*it).name, name)){
			return (*it);
		}
	}
	//throw MODEL_DOESNT_EXISTS;
	Model tmp;
	return tmp;
}

/* a implementar se existir tempo */
void Models::removeModel(Model removeModel){}
void Models::modifyModel(Model toModify, Model newModel){}
