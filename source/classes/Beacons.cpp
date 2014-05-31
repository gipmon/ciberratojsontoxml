#include <iostream>
#include <vector>
#include "Beacons.h"
/* http://www.cplusplus.com/reference/std::vector/std::vector/ */

void Beacons::addBeacon(Beacon add){
	beacons->push_back(add);
}

std::vector<Beacon> Beacons::beaconsList(){
    return *beacons;
}

/* a implementar se existir tempo */
void Beacons::removeBeacon(Beacon removeWall){}
void Beacons::modifyBeacon(Beacon toModify, Beacon newWall){}
