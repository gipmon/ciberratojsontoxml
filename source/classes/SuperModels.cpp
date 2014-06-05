#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "Models.h"
#include "SuperModels.h"

using namespace std;

void SuperModels::addModel(Model add){
	superModelList->push_back(add);
}

vector<SuperModels> SuperModels::getModelsList(){
	return *superModelList;
}

vector<Model*> Models::getSuperModel(const char* name){
	for (vector<SuperModels>::iterator it = superModelList->begin() ; it != superModelList->end(); ++it){
		if(!strcmp((*it).name, name)){
			return (*it);
		}
	}
	return *(new vector<Model*>());
}

/* a implementar se existir tempo */
void removeSuperModel(SuperModel removePose);
void modifySuperModel(SuperModel toModify, SuperModel newSuperModel);
