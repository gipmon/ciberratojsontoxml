#include <iostream>
#include <vector>
#include "Grid.h"
#include <iostream>
#include <fstream>

using namespace std;

/* http://www.cplusplus.com/reference/std::vector/std::vector/ */

void Grid::addPose(Pose add){
	posesList->push_back(add);
}

std::vector<Pose> Grid::getPosesList(){
	return *posesList;
}

void Grid::printTest(){
	std::cout << "\tgrid\" : [ " << std::endl;

	for (std::vector<Pose>::iterator it1 = posesList->begin() ; it1 != posesList->end(); ++it1){
		std::cout << "\t\t[" << (*it1).x << ", " << (*it1).y << ", " <<  (*it1).teta << "]," << std::endl;
	}
	std::cout << "\t]," << std::endl;
}
void Grid::gridOutputXML(){
	ofstream outputFile ( "grid.xml" );
	
	outputFile << "<Grid>\n";
	
	for (std::vector<Pose>::iterator it1 = posesList->begin() ; it1 != posesList->end(); ++it1){
		outputFile << "\t<Position X=\"" << (*it1).x << "\" Y=\"" << (*it1).y << "\" Dir=\"" << (*it1).teta << "\"/>\n";
	}
	outputFile << "</Grid>";
	outputFile.close();
}

/* a implementar se existir tempo */
void Grid::removePose(Pose removePose){}
void Grid::modifyPose(Pose toModify, Pose newPose){}
