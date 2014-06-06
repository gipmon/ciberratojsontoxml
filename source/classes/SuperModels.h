#include <iostream>
#include <vector>
#include <fstream>
#include "Models.h"
#include "../error.h"

using namespace std;

struct SuperModel{
    char* name;
    vector<char*> *names_models_List;
};

class SuperModels{
    private:
    vector<SuperModel>  *superModelList;

	public:
    SuperModels(){ superModelList = new vector<SuperModel>(); }
    void createSuperModel(const char* supermodel_name);
    void addModelToSuperModel(const char* supermodel_name, const char* model_name_to_add);

    void removeSuperModel(SuperModel removeSuperModel);
    void modifySuperModel(SuperModel toModify, SuperModel newSuperModel);
    
    SuperModel getSuperModel(const char* name);
    bool superModelExists(const char* name);

    void printTest();

    vector<SuperModel> getModelsList();
};
