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
	printf("\nList of Models: \n");
	for (vector<Model>::iterator it = modelsList->begin() ; it != modelsList->end(); ++it){
		cout << "\n" << "Model name: " <<  (*it).name << ", height: \"" <<  (*it).height << ", \" first point\" : (" << (*it).first_point.getX() << ", " << (*it).first_point.getY() << "), \"second_point \" : (" << (*it).second_point.getX() << ", " << (*it).second_point.getY() << ") , thickness: " <<  (*it).thickness << endl;
	}
}

Model Models::getModel(const char* name){
	for (vector<Model>::iterator it = modelsList->begin() ; it != modelsList->end(); ++it){
		if(!strcmp((*it).name, name)){
			return (*it);
		}
	}
	//throw MODEL_DOESNT_EXISTS;
	Model tmp;
	return tmp;
}

int Models::existsModel(const char* name){
	for (vector<Model>::iterator it = modelsList->begin() ; it != modelsList->end(); ++it){
		if(!strcmp((*it).name, name)){
			return 1;
		}
	}
	return 0;
}

/* a implementar se existir tempo */
void Models::removeModel(Model removeModel){}
void Models::modifyModel(Model toModify, Model newModel){}
