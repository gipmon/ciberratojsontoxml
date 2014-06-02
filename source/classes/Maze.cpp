#include <iostream>
#include <fstream>
#include <vector>
#include "Maze.h"

using namespace std;

void Maze::setName(char* n){
	name = n;
}

void Maze::setDimensions(double w, double h){
	dimensions.width = w;
	dimensions.height = h;
}

Dimensions Maze::getDimensions(){
	return dimensions;
}

void Maze::addBeacon(Point p, double r, double h){
    Beacon tmp;

    tmp.position = p;
    tmp.radius = r;
    tmp.height = h;

    beacons->addBeacon(tmp);
}

vector<Beacon> Maze::getBeacons(){
	return beacons->beaconsList();
}

void Maze::addTargetArea(Point p, double r){
	TargetArea tmp;

	tmp.radius = r;
	tmp.position = p;

	targetareas->addTargetArea(tmp);
}

vector<TargetArea> Maze::getTargetAreas(){
	return targetareas->targetAreasList();
}

void Maze::addWall(double h, double t, vector<Point>* cl){
	Wall tmp;

	tmp.height = h;
	tmp.thickness = t;
	tmp.corner_list = cl;

	walls->addWall(tmp);
}

vector<Wall> Maze::getWalls(){
	return walls->wallsList();
}

void Maze::addPose(double xx, double yy, double t){
	Pose tmp;

	tmp.x = xx;
	tmp.y = yy;
	tmp.teta = t;

	grid->addPose(tmp);
}

vector<Pose> Maze::getPoses(){
	return grid->getPosesList();
}

void Maze::printTest(){
	cout << "scenario description : \n\t" << "name : " << name << "\n\t" << "dimensions : " << "[" << dimensions.width << ", " << dimensions.height << "],\n\t" << endl;
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
