#include <iostream>
#include <vector>
#include <fstream>
#include "Walls.h"

using namespace std;

void Walls::addWall(Wall add){
	walls->push_back(add);
}

vector<Wall> Walls::wallsList(){
    return *walls;
}

void Walls::printTest(){
	cout << "\twalls\" : [ " << endl;

	for (vector<Wall>::iterator it1 = walls->begin() ; it1 != walls->end(); ++it1){
		cout << "\t\t{ height: " << (*it1).height << ", corner list: [" << endl;
		for(vector<Point>::iterator it2 = (*it1).corner_list->begin() ; it2 != (*it1).corner_list->end(); ++it2){
			cout << "\t\t\t[" << (*it2).getX() << "," << (*it2).getY()  << "]" << endl;
		}
		cout << "\t\t]},\n" << endl;
	}
	cout << "\t]," << endl;
}

void Walls::labOutputXML(ofstream& file){
	

	for (vector<Wall>::iterator it1 = walls->begin() ; it1 != walls->end(); ++it1){
		file << "\t<Wall Height=\"" << (*it1).height << "\">\n";
		for(vector<Point>::iterator it2 = (*it1).corner_list->begin() ; it2 != (*it1).corner_list->end(); ++it2){
			file << "\t\t<Corner X=\"" << (*it2).getX() << "\" Y=\"" << (*it2).getY()  << "\"/>\n";
		}
		file << "\t</Wall>\n";
	}
	
}

/* a implementar se existir tempo */
void Walls::removeWall(Wall removeWall){}
void Walls::modifyWall(Wall toModify, Wall newWall){}
