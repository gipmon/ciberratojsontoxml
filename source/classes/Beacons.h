#include <iostream>
#include <vector>
#include "Point.h"
#include <iostream>
#include <fstream>

using namespace std;


/* http://www.cplusplus.com/reference/std::vector/std::vector/ */

/* Considerações especiais: não pode ter um beacon fora do cenário de jogo, os farois não podem estar sobrepostos. */

/* Farol */
struct Beacon{
    Point position;
    int radius;
    int height;
};

class Beacons {
    private:
    std::vector<Beacon> *beacons;

	public:
    Beacons(){ beacons = new std::vector<Beacon>();}
    void addBeacon(Beacon add);
    void removeBeacon(Beacon removeWall);
    void modifyBeacon(Beacon toModify, Beacon newWall);
    std::vector<Beacon> beaconsList();

    void printTest();
	void labOutputXML(ofstream& file);
};
