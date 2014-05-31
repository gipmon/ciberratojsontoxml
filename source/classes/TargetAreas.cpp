#include <iostream>
#include <vector>
#include "TargetAreas.h"

void TargetAreas::addTargetArea(TargetArea add){
	targetareas->push_back(add);
}

std::vector<TargetArea> TargetAreas::targetAreasList(){
	return *targetareas;
}

/* a implementar se existir tempo */
void TargetAreas::removeTargetArea(TargetArea removeWall){}
void TargetAreas::modifyTargetArea(TargetArea toModify, TargetArea newWall){}
