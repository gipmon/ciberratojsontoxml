#include <iostream>
#include <map>

using namespace std;

struct Beacon{
    Point position;
    int radius;
    int height;
};

/*
não pode ter um beacon fora do senario de jogo etc
o beacon não pode estar sobreposto
*/

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