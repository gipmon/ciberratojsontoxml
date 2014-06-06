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

void Grid::URDFOutput(ofstream& file){
	int count = 1;
	for (vector<Pose>::iterator it1 = posesList->begin() ; it1 != posesList->end(); ++it1){
		file << "\t<link name=\""<< "grid" << count <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << (*it1).x << " "<< (*it1).y << " 0.1\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder length=\"0.2\" radius=\"0.5\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Yellow2\">\n\t\t\t\t<color rgba=\"0.8 0.8 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
		file << "\t<link name=\""<< "pointer" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << (*it1).x << " "<< (*it1).y << " 0.15\" rpy=\"0 0 " << ((*it1).teta*3.14159265/180) << "\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.03 1 0.3\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

	}
}

int Grid::countPoses(){
	return posesList->size();
}
/*<link name="torso_link">
		<visual>
			<origin xyz="0 0 0.12" rpy="0 0 0"/>
			<geometry>
				<cylinder radius="0.05" length="0.24"/>
			</geometry>
	     	<material name="Yellow2">
				<color rgba="0.8 0.8 0 1.0"/>
			</material>
	   </visual>
	</link>*/

/* a implementar se existir tempo */
void Grid::removePose(Pose removePose){}
void Grid::modifyPose(Pose toModify, Pose newPose){}
