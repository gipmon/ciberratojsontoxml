#include <iostream>
#include <vector>
#include <fstream>
#include "Walls.h"
#include <cmath>

using namespace std;

void Walls::addWall(Wall add){
	walls->push_back(add);
}

vector<Wall> Walls::wallsList(){
    return *walls;
}

int Walls::countWalls(){
	return walls->size();
}

void Walls::printTest(){
	cout << "\twalls\" : [ " << endl;

	for (vector<Wall>::iterator it1 = walls->begin() ; it1 != walls->end(); ++it1){
		cout << "\t\t{ height: " << (*it1).height << ", corner list: [" << endl;
		for(vector<Point>::iterator it2 = (*it1).corner_list->begin() ; it2 != (*it1).corner_list->end(); ++it2){
			cout << "\t\t\t[" << (*it2).getX() << "," << (*it2).getY()  << "]" << endl;
		}
		cout << "\t\t]},\n" << endl;
	}
	cout << "\t]," << endl;
}

void Walls::labOutputXML(ofstream& file){


	for (vector<Wall>::iterator it1 = walls->begin() ; it1 != walls->end(); ++it1){
		file << "\t<Wall Height=\"" << (*it1).height << "\">\n";
		for(vector<Point>::iterator it2 = (*it1).corner_list->begin() ; it2 != (*it1).corner_list->end(); ++it2){
			file << "\t\t<Corner X=\"" << (*it2).getX() << "\" Y=\"" << (*it2).getY()  << "\"/>\n";
		}
		file << "\t</Wall>\n";
	}

}

void Walls::URDFOutput(ofstream& file){
	int count = 1;
	for (vector<Wall>::iterator it1 = walls->begin() ; it1 != walls->end(); ++it1){

		for(vector<Point>::iterator it2 = (*it1).corner_list->begin() ; it2 != (*it1).corner_list->end()-1; ++it2){

			Point *a =  new Point((*it2).getX(), (*it2).getY());
			Point *b =  new Point((*(it2+1)).getX(), (*(it2+1)).getY());
			Point *middle = middle_point(a,b);
			double angle = atan2(((*(it2+1)).getY() - (*it2).getY()), ((*(it2+1)).getX() - (*it2).getX()));
			double distance = two_points_distance(a,b);
			file << "\t<link name=\""<< "wall" << count++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << middle->getX() << " " << middle->getY() << " " << (*it1).height/2 << "\" rpy=\"0 0 "<< angle <<"\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << distance << " "<< (*it1).thickness << " " << (*it1).height << "\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";

		}

	}
}

Point* Walls::middle_point(Point* a, Point* b){
	Point *tmp =  new Point((a->getX()+b->getX())/2, (a->getY()+b->getY())/2);
	return tmp;
}

double Walls::two_points_distance(Point* a, Point* b){

	double result;
	result = pow(b->getX() - a->getX(),2);
	result += pow(b->getY() - a->getY(),2);
	return result = sqrt(result);

}


/* a implementar se existir tempo */
void Walls::removeWall(Wall removeWall){}
void Walls::modifyWall(Wall toModify, Wall newWall){}
