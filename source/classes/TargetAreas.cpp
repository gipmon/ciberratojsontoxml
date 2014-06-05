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

int TargetAreas::countTargetAreas(){
	return targetareas->size();
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
void TargetAreas::URDFOutput(ofstream& file){
    int count = 1;
    
    for (vector<TargetArea>::iterator it = targetareas->begin() ; it != targetareas->end(); ++it){
         file << "\t<link name=\""<< "target_area" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << (*it).position.getX() << " "<< (*it).position.getY() << " 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"" << (*it).radius << "\" length=\"0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Blue1\">\n\t\t\t\t<color rgba=\"0 0 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
    }
}

/* a implementar se existir tempo */
void TargetAreas::removeTargetArea(TargetArea removeWall){}
void TargetAreas::modifyTargetArea(TargetArea toModify, TargetArea newWall){}
