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
	if(t==0){
		tmp.thickness = 0.1;
	}else{
		tmp.thickness = t;
	}
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

void Maze::URDFOutput(ofstream& file){
    int count=0;
    
    file << "<robot name=\"TOS challenge\">\n";
    
    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << dimensions.width/2 << " 0 0\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << dimensions.width << " 0.2 5\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << dimensions.width/2 << " "<< dimensions.height <<" 0\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << dimensions.width << " 0.2 5\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
    
    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"0 " << dimensions.height/2 <<" 0\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.2 "<< dimensions.height << " 5\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
    
    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\""<< dimensions.width << " " << dimensions.height/2 <<" 0\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.2 "<< dimensions.height << " 5\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    //beacons->URDFOutput(file);
    //targetareas->URDFOutput(file);
    //walls->URDFOutput(file);
    file << "</robot>";
    file.close();
}
