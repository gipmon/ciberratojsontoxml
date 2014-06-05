#include <iostream>
#include <vector>
#include <fstream>
#include "Models.h"

using namespace std;

struct SuperModel{
    char* name;
    vector<Model*> *modelsList;
};

class SuperModels{
    private:
    vector<SuperModel>  *superModelList;

	public:
    SuperModels(){ superModelList = new vector<SuperModel>(); }
    void addSuperModel(SuperModel add);
    void removeSuperModel(SuperModel removeSuperModel);
    void modifySuperModel(SuperModel toModify, SuperModel newSuperModel);
    SuperModel getSuperModel(const char* name);

    void printTest();

    vector<SuperModel> getModelsList();
};
