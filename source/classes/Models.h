#include <iostream>
#include <vector>
#include <fstream>
#include "Point.h"

using namespace std;

struct Model{
    char* name;
    Point first_point;
    Point second_point;
    double thickness;
    double height;
};

class Models {
    private:
    vector<Model>  *modelsList;

	public:
    Models(){ modelsList = new vector<Model>(); }
    void addModel(Model add);
    void removeModel(Model removeModel);
    void modifyModel(Model toModify, Model newModel);
    Model getModel(const char* name);

    void printTest();
    int existsModel(const char* name);
    vector<Model> getModelsList();
};
