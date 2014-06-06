#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "Models.h"
#include "SuperModels.h"

using namespace std;

void SuperModels::createSuperModel(char* supermodel_name){
	Model tmp;
	tmp.name = supermodel_name;
	tmp.modelsList = new vector<Model>();
	superModelList->push_back(tmp);
}

void SuperModels::addModelToSuperModel(const char* supermodel_name, Model add){
	for (vector<SuperModel>::iterator it = superModelList->begin() ; it != superModelList->end(); ++it){
		if(!strcmp((*it).name, supermodel_name)){
			(*it).modelsList->push_back(add);
		}
	}
}

vector<SuperModel> SuperModels::getModelsList(){
	return *superModelList;
}

SuperModel SuperModels::getSuperModel(const char* name){
	for (vector<SuperModel>::iterator it = superModelList->begin() ; it != superModelList->end(); ++it){
		if(!strcmp((*it).name, name)){
			return (*it);
		}
	}
	SuperModel tmp;
	return tmp;
}

/* a implementar se existir tempo */
void removeSuperModel(SuperModel removeSuperModel);
void modifySuperModel(SuperModel toModify, SuperModel newSuperModel);
