#include <iostream>
#include <vector>
#include "TargetAreas.h"

void TargetAreas::addTargetArea(TargetArea add){
	targetareas->push_back(add);
}

std::vector<TargetArea> TargetAreas::targetAreasList(){
	return *targetareas;
}

void TargetAreas::printTest(){
	std::cout << "\ttarget areas\" : [ " << std::endl;

	for (std::vector<TargetArea>::iterator it = targetareas->begin() ; it != targetareas->end(); ++it){
		std::cout << "\n\t\t" << "{ \"position\" : [" << (*it).position.getX() << ", " << (*it).position.getY() << "], radius: " <<  (*it).radius << "}\n\t]," << std::endl;
	}
}

/* a implementar se existir tempo */
void TargetAreas::removeTargetArea(TargetArea removeWall){}
void TargetAreas::modifyTargetArea(TargetArea toModify, TargetArea newWall){}
