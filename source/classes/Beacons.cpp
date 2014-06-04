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
		cout << "\n\t\t" << "{ \"position\" : [" << (*it).position.getX() << ", " << (*it).position.getY() << "], height: " << (*it).height << "}\n\t]," << endl;
	}
}

void Beacons::labOutputXML(ofstream& file){
	file << "\t<Beacon ";

	for (vector<Beacon>::iterator it = beacons->begin() ; it != beacons->end(); ++it){
		file << "X=\"" << (*it).position.getX() << "\" Y=\"" << (*it).position.getY() << "\" Height=\"" << (*it).height <<  "\"/>\n";
	}
}

void Beacons::URDFOutput(ofstream& file){
    
    int count = 1;
    
    for (vector<Beacon>::iterator it = beacons->begin() ; it != beacons->end(); ++it){
        file << "\t<link name=\""<< "beacon" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << (*it).position.getX() << " "<< (*it).position.getY() << " "<< (*it).height <<"\"/>\n\t\t\t<geometry>\n\t\t\t\t<sphere radius=\"0.3\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Yellow2\">\n\t\t\t\t<color rgba=\"0.8 0.8 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
        
    }
    
}


/* a implementar se existir tempo */
void Beacons::removeBeacon(Beacon removeWall){}
void Beacons::modifyBeacon(Beacon toModify, Beacon newWall){}
