#include <iostream>
#include <vector>
#include "Walls.h"
#include <iostream>
#include <fstream>

using namespace std;

/* http://www.cplusplus.com/reference/std::vector/std::vector/ */

void Walls::addWall(Wall add){
	walls->push_back(add);
}

std::vector<Wall> Walls::wallsList(){
    return *walls;
}

void Walls::printTest(){
	std::cout << "\twalls\" : [ " << std::endl;

	for (std::vector<Wall>::iterator it1 = walls->begin() ; it1 != walls->end(); ++it1){
		std::cout << "\t\t{ height: " << (*it1).height << ", corner list: [" << std::endl;
		for(std::vector<Point>::iterator it2 = (*it1).corner_list->begin() ; it2 != (*it1).corner_list->end(); ++it2){
			std::cout << "\t\t\t[" << (*it2).getX() << "," << (*it2).getY()  << "]" << std::endl;
		}
		std::cout << "\t\t]},\n" << std::endl;
	}
	std::cout << "\t]," << std::endl;
}

void Walls::labOutputXML(ofstream& file){
	

	for (std::vector<Wall>::iterator it1 = walls->begin() ; it1 != walls->end(); ++it1){
		file << "\t<Wall Height=\"" << (*it1).height << "\">\n";
		for(std::vector<Point>::iterator it2 = (*it1).corner_list->begin() ; it2 != (*it1).corner_list->end(); ++it2){
			file << "\t\t<Corner X=\"" << (*it2).getX() << "\" Y=\"" << (*it2).getY()  << "\"/>\n";
		}
		file << "\t</Wall>\n";
	}
	
}

/* a implementar se existir tempo */
void Walls::removeWall(Wall removeWall){}
void Walls::modifyWall(Wall toModify, Wall newWall){}
