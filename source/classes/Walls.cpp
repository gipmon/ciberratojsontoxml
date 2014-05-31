#include <iostream>
#include <vector>
#include "Walls.h"
/* http://www.cplusplus.com/reference/std::vector/std::vector/ */

void Walls::addWall(Wall add){
	walls->push_back(add);
}

std::vector<Wall> Walls::wallsList(){
    return *walls;
}

/* a implementar se existir tempo */
void Walls::removeWall(Wall removeWall){}
void Walls::modifyWall(Wall toModify, Wall newWall){}
