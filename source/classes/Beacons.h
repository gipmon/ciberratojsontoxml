#include <iostream>
#include <vector>
#include <fstream>
#include "Point.h"

using namespace std;

/* Considerações especiais: não pode ter um beacon fora do cenário de jogo, os farois não podem estar sobrepostos. */

/* Farol */
struct Beacon{
    Point position;
    double radius;
    double height;
};

class Beacons {
    private:
    vector<Beacon> *beacons;

	public:
    Beacons(){ beacons = new vector<Beacon>();}
    void addBeacon(Beacon add);
    void removeBeacon(Beacon removeWall);
    void modifyBeacon(Beacon toModify, Beacon newWall);
    vector<Beacon> beaconsList();

    void printTest();
    void labOutputXML(ofstream& file);
    void URDFOutput(ofstream& file);
};
