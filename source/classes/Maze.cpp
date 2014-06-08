#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include "Maze.h"
#include "../error.h"
#include <cmath>

#define PI 3.14159265359
using namespace std;
const char* warning = "[WARNING!] Warning description below:\n";

void Maze::setName(char* n){
	if(n == NULL){
		throw NULL_SCENARIO_DESCRIPTION_NAME;
	}
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

    if(validateXPoints(p.getX())){ 
    	printf("%sThe x-coordinate (%.2f) of the Beacon is out the dimensions\n", warning, p.getX());
    }
    if(validateYPoints(p.getY())){
    	printf("%sThe y-coordinate (%.2f) of the Beacon is outside the dimensions\n", warning, p.getY());
    }
    beacons->addBeacon(tmp);
}

void Maze::addModel(char* nm, double h, Point fp, Point sp, double t){
	Model tmp;

	tmp.height = h;
	if(nm == NULL){
		throw NULL_MODEL_NAME;
	}
	tmp.name = nm;

	if(validateXPoints(fp.getX())){
		printf("%sThe x-coordinate (%.2f) of the first point of the Model %s is out the dimensions\n", warning, fp.getX(), nm);
	}
	if(validateYPoints(fp.getY())){
		printf("%sThe y-coordinate (%.2f) of the first point of the Model %s is out the dimensions\n", warning, fp.getY(), nm);
	}
	if(validateXPoints(sp.getX())){
		printf("%sThe x-coordinate (%.2f) of the second point of the Model %s is out the dimensions\n", warning, sp.getX(), nm);
	}
	if(validateYPoints(sp.getY())){
		printf("%sThe y-coordinate (%.2f) of the second point of the Model %s is out the dimensions\n", warning, sp.getY(), nm);
	}
	tmp.first_point = fp;
	tmp.second_point = sp;
	
	tmp.thickness = t;

    models->addModel(tmp);
}

void Maze::createSuperModel(const char* supermodel_name){
	supermodels->createSuperModel(supermodel_name);
}

void Maze::addModelToSuperModel(const char* supermodel_name, const char* model_to_add){
	if(!models->existsModel(model_to_add)){
		throw MODEL_DOESNT_EXISTS;
	}
	supermodels->addModelToSuperModel(supermodel_name, model_to_add);
}

void Maze::printSuperModels(){
	supermodels->printTest();
}

void Maze::loadSuperModeltoWalls(const char* name, double x, double y, double rot){
	if(!supermodels->superModelExists(name)){
		throw SUPER_MODEL_DOESNT_EXISTS;
	}

	SuperModel tmp = supermodels->getSuperModel(name);

	for(vector<char*>::iterator it = tmp.names_models_List->begin() ; it != tmp.names_models_List->end(); ++it){
		this->loadModel((*it), x, y, rot);
	}
}

bool Maze::existsSuperModel(const char* name){
	return supermodels->superModelExists(name);
}

int Maze::countSuperModels(){
	return supermodels->countSuperModels();
}

vector<Beacon> Maze::getBeacons(){
	return beacons->beaconsList();
}

int Maze::countBeacons(){
	return beacons->countBeacons();
}

void Maze::addTargetArea(Point p, double r){
	TargetArea tmp;
	if(r <= 0){
		throw NULL_TARGET_RADIUS;
	}
	tmp.radius = r;

	tmp.position = p;
	if(validateXPoints(p.getX())){
		printf("%sThe x-coordinate (%.2f) of the Target Area is outside the dimensions\n", warning, p.getX());
	}
	if(validateYPoints(p.getY())){
		printf("%sThe y-coordinate (%.2f) of the Target Area is outside the dimensions\n", warning, p.getY());
	}
	targetareas->addTargetArea(tmp);
}

vector<TargetArea> Maze::getTargetAreas(){
	return targetareas->targetAreasList();
}

int Maze::countTargetAreas(){
	return targetareas->countTargetAreas();
}

void Maze::addWall(double h, double t, vector<Point>* cl){
  	
  		Wall tmp;

		tmp.height = h;
	
		if(t==0){
			tmp.thickness = 0.1;
		}
		else if(t>0){
			tmp.thickness = t;
		}
		else{
			tmp.thickness = 0.1;
		}

		for (vector<Point>::iterator it1 = cl->begin() ; it1 != cl->end(); ++it1){

			if(validateXPoints((*it1).getX())){
				printf("%sThe x-coordinate (%.2f) of the Wall is outside the dimensions\n", warning, ((*it1).getX()));
			}
			if(validateYPoints((*it1).getY())){
				printf("%sThe y-coordinate (%.2f) of the Wall is out the dimensions\n", warning, ((*it1).getY()));
			}
		}
		tmp.corner_list = cl;

		walls->addWall(tmp);

}

void Maze::removeNotPerpendicularWalls(){
	walls->removeNotPerpendicularWalls();
}

void Maze::modify_vector(vector<Point>* cl){

}

vector<Wall> Maze::getWalls(){
	return walls->wallsList();
}

int Maze::countWalls(){
	return walls->countWalls();
}

void Maze::addPose(double xx, double yy, double t){
	Pose tmp;
	tmp.x = xx;
	tmp.y = yy;
	tmp.teta = t;
	if(validateXPoints(xx)){
		printf("%sThe x-coordinate (%.2f) of the Grid is outside the dimensions\n", warning, xx);
	}
	if(validateYPoints(yy)){
		printf("%sThe y-coordinate (%.2f) of the Grid is outside the dimensions\n", warning, yy);
	}
	grid->addPose(tmp);



}

vector<Pose> Maze::getPoses(){
	return grid->getPosesList();
}

void Maze::validateScenarioDescription(){
	if(name == NULL){
		throw NULL_SCENARIO_DESCRIPTION_NAME;
	}
	
	if(beacons->countBeacons() < 1){
		throw NULL_BEACONS;
	}
	if(targetareas->countTargetAreas() < 1){
		throw NULL_TARGET_AREAS;
	}
	if(grid->countPoses() < 1){
		throw WRONG_GRID;
	}

}

int Maze::validateXPoints(double x){
	if(x > dimensions.width || x < 0){
		return 1;
	}
	return 0;
}

int Maze::validateYPoints(double y){
	if(y > dimensions.height || y < 0){
		return 1;
	}
	return 0;
}


void Maze::printTest(){
	cout << "scenario description : \n\t" << "name : " << name << "\n\t" << "dimensions : " << "[" << dimensions.width << ", " << dimensions.height << "],\n\t" << endl;
	beacons->printTest();
	targetareas->printTest();
	walls->printTest();
	grid->printTest();
}

void Maze::printTestModels(){
	models->printTest();
}

void Maze::loadModel(const char* name, double x, double y, double rot_angle){
	Model md = models->getModel(name);

	Wall tmp;

	tmp.height = md.height;
	if(md.thickness==0){
		tmp.thickness = 0.1;
	}else if(md.thickness>0){
		tmp.thickness = md.thickness;
	}else{
		tmp.thickness = 0.1;
	}

	vector<Point> *new_cl = new vector<Point>();
	Point *fp = new Point(md.first_point.getX()+x, md.first_point.getY()+y);
	Point *sp = new Point(md.second_point.getX()+x, md.second_point.getY()+y);

	Point *middle = walls->middle_point(fp, sp);
	double distance = walls->two_points_distance(fp,sp);
	double d2 = distance/2;

	double a = cos(rot_angle)*d2;
	double o = sin(rot_angle)*d2;

	double fp_x = middle->getX()-a;
	double fp_y = middle->getY()-o;

	double sp_x = middle->getX()+a;
	double sp_y = middle->getY()+o;

	if(validateXPoints(fp_x)){
		printf("%sThe x-coordinate (%.2f) of the first point of the Model %s is out the dimensions\n", warning, fp_x, name);
	}
	if(validateYPoints(fp_y)){
		printf("%sThe y-coordinate (%.2f) of the first point of the Model %s is out the dimensions\n", warning, fp_y, name);
	}
	if(validateXPoints(sp_x)){
		printf("%sThe x-coordinate (%.2f) of the second point of the Model %s is out the dimensions\n", warning, sp_x, name);
	}
	if(validateYPoints(sp_y)){
		printf("%sThe y-coordinate (%.2f) of the second point of the Model %s is out the dimensions\n", warning, sp_y, name);
	}
	fp = new Point(fp_x, fp_y);
	sp = new Point(sp_x, sp_y);

	new_cl->push_back(*fp);
	new_cl->push_back(*sp);

	tmp.corner_list = new_cl;
	walls->addWall(tmp);
	/*
	struct Model{
	    char* name;
	    Point first_point;
	    Point second_point;
	    double thickness;
	    double height;
	};
	*/
}

int Maze::existsModel(const char* name){
	return models->existsModel(name);
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

void Maze::URDFOutputRotate(ofstream& file){
    int count=1;

    file << "<robot name=\"TOS challenge\">\n";

    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << dimensions.width/2 << " 0 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << dimensions.width << " 0.05 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << dimensions.width/2 << " "<< dimensions.height <<" 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << dimensions.width << " 0.05 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"0 " << dimensions.height/2 <<" 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 "<< dimensions.height << " 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\""<< dimensions.width << " " << dimensions.height/2 <<" 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 "<< dimensions.height << " 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    file << "\t<link name=\"base\">\n\t\t<visual>\n\t\t\t<origin xyz=\""<< dimensions.width/2 << " " << dimensions.height/2 <<" 0\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\""<< dimensions.width << " " << dimensions.height << " 0.2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"yellow2\">\n\t\t\t\t<color rgba=\"1 1 0.5 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    beacons->URDFOutput(file);
    targetareas->URDFOutput(file);
    walls->URDFOutputRotate(file);
    grid->URDFOutput(file);
    file << "</robot>";
    file.close();
}

void Maze::URDFOutputFixed(ofstream& file){
    int count=1;

    file << "<robot name=\"TOS challenge\">\n";

    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << dimensions.width/2 << " 0 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << dimensions.width << " 0.05 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << dimensions.width/2 << " "<< dimensions.height <<" 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << dimensions.width << " 0.05 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"0 " << dimensions.height/2 <<" 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 "<< dimensions.height << " 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    file << "\t<link name=\""<< "parede" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\""<< dimensions.width << " " << dimensions.height/2 <<" 1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 "<< dimensions.height << " 2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    file << "\t<link name=\"base\">\n\t\t<visual>\n\t\t\t<origin xyz=\""<< dimensions.width/2 << " " << dimensions.height/2 <<" 0\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\""<< dimensions.width << " " << dimensions.height << " 0.2\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"yellow2\">\n\t\t\t\t<color rgba=\"1 1 0.5 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

    beacons->URDFOutput(file);
    targetareas->URDFOutput(file);
    walls->URDFOutputFixed(file);
    grid->URDFOutput(file);
    file << "</robot>";
    file.close();
}
