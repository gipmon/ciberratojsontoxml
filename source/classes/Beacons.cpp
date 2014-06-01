#include <iostream>
#include <vector>
#include <fstream>
#include "Beacons.h"

using namespace std;

void Beacons::addBeacon(Beacon add){
	beacons->push_back(add);
}

vector<Beacon> Beacons::beaconsList(){
    return *beacons;
}

void Beacons::printTest(){
	cout << "\tbeacons\" : [ " << endl;

	for (vector<Beacon>::iterator it = beacons->begin() ; it != beacons->end(); ++it){
		cout << "\n\t\t" << "{ \"position\" : [" << (*it).position.getX() << ", " << (*it).position.getY() << "], radius: " <<  (*it).radius << ", height: " << (*it).height << "}\n\t]," << endl;
	}
}

void Beacons::labOutputXML(ofstream& file){
	file << "\t<Beacon ";

	for (vector<Beacon>::iterator it = beacons->begin() ; it != beacons->end(); ++it){
		file << "X=\"" << (*it).position.getX() << "\" Y=\"" << (*it).position.getY() << "\" Height=\"" << (*it).height << "\" Radius=\"" <<  (*it).radius <<  "\"/>\n";
	}
}

/* a implementar se existir tempo */
void Beacons::removeBeacon(Beacon removeWall){}
void Beacons::modifyBeacon(Beacon toModify, Beacon newWall){}
