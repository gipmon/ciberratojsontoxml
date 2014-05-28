#include <iostream>
#include <map>

using namespace std;

struct TargetArea{
    Point position;
    int radius;
    int height;
};

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