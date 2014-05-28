#include <iostream>
#include <map>

using namespace std;

struct Beacon{
    Point position;
    int radius;
    int height;
};

class Beacons {
    private:
    LinkedList<Beacon>* beacons = new LinkedList<Beacon>();

	public:
    void addBeacon(Beacon add){

    }

    void removeBeacon(Beacon removeWall){

    }

    void modifyBeacon(Beacon toModify, Beacon newWall){

    }

    LinkedList<Beacon>* pointsList(){

    }
};