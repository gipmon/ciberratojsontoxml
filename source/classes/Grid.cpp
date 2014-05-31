#include <iostream>
#include <vector>
#include "Grid.h"
/* http://www.cplusplus.com/reference/std::vector/std::vector/ */

void Grid::addPose(Pose add){
	posesList->push_back(add);
}

std::vector<Pose> Grid::getPosesList(){
	return *posesList;
}

/* a implementar se existir tempo */
void Grid::removePose(Pose removePose){}
void Grid::modifyPose(Pose toModify, Pose newPose){}
