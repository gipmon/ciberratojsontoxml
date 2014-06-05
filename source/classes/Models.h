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
    void removeModel(Model removePose);
    void modifyModel(Model toModify, Model newPose);
    Model getModel(char* name);

    void printTest();

    vector<Model> getModelsList();
};
