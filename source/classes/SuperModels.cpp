#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string.h>
#include "Models.h"
#include "SuperModels.h"

using namespace std;

void SuperModels::createSuperModel(const char* supermodel_name){
	SuperModel tmp;

	tmp.name = strdup(supermodel_name);
	tmp.names_models_List = new vector<char*>();

	superModelList->push_back(tmp);
}

void SuperModels::addModelToSuperModel(const char* supermodel_name, const char* model_to_add){
	for (vector<SuperModel>::iterator it = superModelList->begin() ; it != superModelList->end(); ++it){
		if(!strcmp((*it).name, supermodel_name)){
			(*it).names_models_List->push_back(strdup(model_to_add));
		}
	}
}

vector<SuperModel> SuperModels::getModelsList(){
	return *superModelList;
}

bool SuperModels::superModelExists(const char* name){
	for (vector<SuperModel>::iterator it = superModelList->begin() ; it != superModelList->end(); ++it){
		if(!strcmp((*it).name, name)){
			return true;
		}
	}
	return false;
}

SuperModel SuperModels::getSuperModel(const char* name){
	if(!superModelExists(name)){
		throw SUPER_MODEL_DOESNT_EXISTS;
	}

	for(vector<SuperModel>::iterator it = superModelList->begin() ; it != superModelList->end(); ++it){
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
