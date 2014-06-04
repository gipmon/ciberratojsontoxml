#include <iostream>
#include <vector>
#include <fstream>
#include "Grid.h"

using namespace std;

void Grid::addPose(Pose add){
	posesList->push_back(add);
}

vector<Pose> Grid::getPosesList(){
	return *posesList;
}

void Grid::printTest(){
	cout << "\tgrid\" : [ " << endl;

	for (vector<Pose>::iterator it1 = posesList->begin() ; it1 != posesList->end(); ++it1){
		cout << "\t\t[" << (*it1).x << ", " << (*it1).y << ", " <<  (*it1).teta << "]," << endl;
	}
	cout << "\t]," << endl;
}

void Grid::gridOutputXML(ofstream& file){
	
	file << "<Grid>\n";
	for (vector<Pose>::iterator it1 = posesList->begin() ; it1 != posesList->end(); ++it1){
		file << "\t<Position X=\"" << (*it1).x << "\" Y=\"" << (*it1).y << "\" Dir=\"" << (*it1).teta << "\"/>\n";
	}
	file << "</Grid>";

	file.close();
}

/* a implementar se existir tempo */
void Grid::removePose(Pose removePose){}
void Grid::modifyPose(Pose toModify, Pose newPose){}
