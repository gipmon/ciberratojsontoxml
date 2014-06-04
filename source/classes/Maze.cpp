#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
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

void Maze::addBeacon(Point p, double h){
    Beacon tmp;

    tmp.position = p;
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
  	if(validate_corner_list(cl)){
  		Wall tmp;

		tmp.height = h;
		if(t!=0){
			modify_vector(cl);
		}
		tmp.thickness = 0;
		tmp.corner_list = cl;

		walls->addWall(tmp);
  	}
}

bool Maze::validate_corner_list(vector<Point>* cl){
	if(cl->size()<3){
		return true;
	}

	vector<Point*> *scalar_vector = new vector<Point*>();

	for(vector<Point>::iterator it = cl->begin() ; it != cl->end(); ++it){
		Point *tmp =  new Point((*(it+1)).getX()-(*it).getX(), (*(it+1)).getY()-(*it).getY());
		scalar_vector->push_back(tmp);
	}
	for(vector<Point*>::iterator it = scalar_vector->begin() ; it != scalar_vector->end()-1; ++it){

		double series1[] = {(*it)->getX(), (*it)->getY()};
	  	double series2[] = {(*(it+1))->getX(), (*(it+1))->getY()};
		if(!inner_product(series1, series1+2, series2, 0)){
			return true;
		}
	}
	return false;
}

void Maze::modify_vector(vector<Point>* cl){
	
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
    int count=1;
    
    file << "<robot name=\"TOS challenge\">\n";
    
    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << dimensions.width/2 << " 0 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << dimensions.width << " 0.2 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << dimensions.width/2 << " "<< dimensions.height <<" 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << dimensions.width << " 0.2 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
    
    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"0 " << dimensions.height/2 <<" 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.2 "<< dimensions.height << " 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
    
    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\""<< dimensions.width << " " << dimensions.height/2 <<" 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.2 "<< dimensions.height << " 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
    
    file << "\t<link name=\"base\">\n\t\t<visual>\n\t\t\t<origin xyz=\""<< dimensions.width/2 << " " << dimensions.height/2 <<" 0\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\""<< dimensions.width << " " << dimensions.height << " 0.2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"yellow2\">\n\t\t\t\t<color rgba=\"1 1 0.5 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    beacons->URDFOutput(file);
    targetareas->URDFOutput(file);
    //walls->URDFOutput(file);
    file << "</robot>";
    file.close();
}
