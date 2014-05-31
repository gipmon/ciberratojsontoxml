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

void Beacons::printTest(){
	std::cout << "\tbeacons\" : [ " << std::endl;

	for (std::vector<Beacon>::iterator it = beacons->begin() ; it != beacons->end(); ++it){
		std::cout << "\n\t\t" << "{ \"position\" : [" << (*it).position.getX() << ", " << (*it).position.getY() << "], radius: " <<  (*it).radius << ", height: " << (*it).height << "}\n\t]," << std::endl;
	}
}

/* a implementar se existir tempo */
void Beacons::removeBeacon(Beacon removeWall){}
void Beacons::modifyBeacon(Beacon toModify, Beacon newWall){}
