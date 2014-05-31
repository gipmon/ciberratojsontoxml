#include <iostream>
#include <vector>
#include "Maze.h"

void Maze::setDimensions(){

}

Dimensions* Maze::getDimensions(){
	return NULL;
}

void Maze::addBeacon(Point position, int radius, int height){

}

std::vector<Beacon>* Maze::getBeacons(){
	return NULL;
}

void Maze::addTargetArea(Point position, int radius){

}

std::vector<TargetArea>* Maze::getTargetAreas(){
	return NULL;
}

void Maze::addWall(int height, int thickness, std::vector<Point>* corner_list){

}

std::vector<Wall>* Maze::getWalls(){
	return NULL;
}

void Maze::addPose(int x, int y, int teta){

}

std::vector<Pose>* Maze::getPoses(){
	return NULL;
}
