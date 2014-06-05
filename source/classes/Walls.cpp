#include <iostream>
#include <vector>
#include <fstream>
#include "Walls.h"
#include <cmath>
#include <numeric>

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

void Walls::removeNotPerpendicularWalls(){
	for (vector<Wall>::iterator it1 = walls->begin() ; it1 != walls->end(); ++it1){
		if(!validate_corner_list((*it1).corner_list)){
			walls->erase(it1);
			printf("erase\n");
		}
		printf("noterase\n");
	}
}

bool Walls::validate_corner_list(vector<Point>* cl){

	if(cl->size()<2){
		return false;
	}
	if(cl->size()==2){
		return true;
	}

	vector<Point*> *scalar_vector = new vector<Point*>();

	for(vector<Point>::iterator it = cl->begin() ; it != (cl->end()-1); ++it){
		Point *tmp =  new Point((*(it+1)).getX()-(*it).getX(), (*(it+1)).getY()-(*it).getY());
		scalar_vector->push_back(tmp);
	}
	for(vector<Point*>::iterator it = scalar_vector->begin() ; it != (scalar_vector->end()-1); ++it){

		vector<double> *series1 = new vector<double>();
		series1->push_back((*it)->getX());
		series1->push_back((*it)->getY());

		vector<double> *series2 = new vector<double>();
		series2->push_back((*(it+1))->getX());
		series2->push_back((*(it+1))->getY());

		if(!scalar_product(*series1, *series2)){
			return true;
		}
		printf("%d dsf", scalar_product(*series1, *series2));
	}
	return false;
}

int Walls::scalar_product(vector<double> a, vector<double> b){
    if(a.size() != b.size()){
        puts("Error a's size not equal to b's size");
        return -1;
    }

    double product = 0;
    for (unsigned int i = 0; i <= a.size()-1; i++){
       product += (a[i])*(b[i]);
    }
    return (int)product;
}

/* a implementar se existir tempo */
void Walls::removeWall(Wall removeWall){}
void Walls::modifyWall(Wall toModify, Wall newWall){}
