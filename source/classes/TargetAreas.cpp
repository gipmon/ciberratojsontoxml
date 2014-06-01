#include <iostream>
#include <fstream>
#include <vector>
#include "TargetAreas.h"

using namespace std;

void TargetAreas::addTargetArea(TargetArea add){
	targetareas->push_back(add);
}

vector<TargetArea> TargetAreas::targetAreasList(){
	return *targetareas;
}

void TargetAreas::printTest(){
	cout << "\ttarget areas\" : [ " << endl;

	for (vector<TargetArea>::iterator it = targetareas->begin() ; it != targetareas->end(); ++it){
		cout << "\n\t\t" << "{ \"position\" : [" << (*it).position.getX() << ", " << (*it).position.getY() << "], radius: " <<  (*it).radius << "}\n\t]," << endl;
	}
}

void TargetAreas::labOutputXML(ofstream& file){
	file << "\t<Target ";

	for (vector<TargetArea>::iterator it = targetareas->begin() ; it != targetareas->end(); ++it){
		file << "X=\"" << (*it).position.getX() << "\" Y=\"" << (*it).position.getY() << "\" Radius=\"" <<  (*it).radius <<  "\"/>\n";
	}
}

/* a implementar se existir tempo */
void TargetAreas::removeTargetArea(TargetArea removeWall){}
void TargetAreas::modifyTargetArea(TargetArea toModify, TargetArea newWall){}
