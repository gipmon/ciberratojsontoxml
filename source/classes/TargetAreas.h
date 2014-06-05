#include <iostream>
#include <vector>
#include <fstream>
#include "Point.h"

using namespace std;

struct TargetArea{
    Point position;
    double radius;
};

/* no futuro pode ter várias formas, para já é circular*/

class TargetAreas {
    private:
    vector<TargetArea>* targetareas;

	public:
    TargetAreas(){ targetareas = new vector<TargetArea>();}
    void addTargetArea(TargetArea add);
    void removeTargetArea(TargetArea removeWall);
    void modifyTargetArea(TargetArea toModify, TargetArea newWall);
    vector<TargetArea> targetAreasList();

    int countTargetAreas();

    void printTest();
    void labOutputXML(ofstream& file);
    void URDFOutput(ofstream& file);
};
