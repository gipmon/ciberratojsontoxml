#include <iostream>
#include <map>

using namespace std;

struct TargetArea{
    Point position;
    int radius;
};

/* no futuro pode ter várias formas, para já é circular*/

class TargetAreas {
    private:
    LinkedList<TargetArea>* targetareas = new LinkedList<TargetArea>();

	public:
    void addTargetArea(TargetArea add){

    }

    void removeTargetArea(TargetArea removeWall){

    }

    void modifyTargetArea(TargetArea toModify, TargetArea newWall){

    }

    LinkedList<TargetArea>* pointsList(){

    }
};