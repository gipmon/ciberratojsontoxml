#include <iostream>
#include <vector>
#include "Maze.h"
#include <iostream>
#include <fstream>

using namespace std;

void Maze::setName(char* n){
	name = n;
}

void Maze::setDimensions(int w, int h){
	dimensions.width = w;
	dimensions.height = h;
}

Dimensions Maze::getDimensions(){
	return dimensions;
}

void Maze::addBeacon(Point p, int r, int h){
    Beacon tmp;

    tmp.position = p;
    tmp.radius = r;
    tmp.height = h;

    beacons->addBeacon(tmp);
}

std::vector<Beacon> Maze::getBeacons(){
	return beacons->beaconsList();
}

void Maze::addTargetArea(Point p, int r){
	TargetArea tmp;

	tmp.radius = r;
	tmp.position = p;

	targetareas->addTargetArea(tmp);
}

std::vector<TargetArea> Maze::getTargetAreas(){
	return targetareas->targetAreasList();
}

void Maze::addWall(int h, int t, std::vector<Point>* cl){
	Wall tmp;

	tmp.height = h;
	tmp.thickness = t;
	tmp.corner_list = cl;

	walls->addWall(tmp);
}

std::vector<Wall> Maze::getWalls(){
	return walls->wallsList();
}

void Maze::addPose(int xx, int yy, int t){
	Pose tmp;

	tmp.x = xx;
	tmp.y = yy;
	tmp.teta = t;

	grid->addPose(tmp);
}

std::vector<Pose> Maze::getPoses(){
	return grid->getPosesList();
}

void Maze::printTest(){
	std::cout << "scenario description : \n\t" << "name : " << name << "\n\t" << "dimensions : " << "[" << dimensions.width << ", " << dimensions.height << "],\n\t" << std::endl;
	beacons->printTest();
	targetareas->printTest();
	walls->printTest();
	grid->printTest();
}

void Maze::gridOutputXML(ofstream& file){
	grid->gridOutputXML(file);
}

void Maze::labOutputXML(ofstream& file){
	
	file << "<Lab Name=\"" << name << "\" Width=\"" << dimensions.width << "\" Height=\"" << dimensions.height << "\">\n";
	beacons->labOutputXML(file);
	targetareas->labOutputXML(file);
	walls->labOutputXML(file);
	file << "</Lab>";
	file.close();
}
