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

void Walls::URDFOutputFixed(ofstream& file){
	int count = 1;
	int iteration = 0;
	int complement = 1;

	printRobot(file);

	for (vector<Wall>::iterator it1 = walls->begin() ; it1 != walls->end(); ++it1){
		if(validate_corner_list((*it1).corner_list) && (*it1).corner_list->size()>2){
			for(vector<Point>::iterator it2 = (*it1).corner_list->begin() ; it2 != (*it1).corner_list->end()-1; ++it2){
				if(iteration == 0){
					Point *a =  new Point((*it2).getX(), (*it2).getY());
					Point *b =  new Point((*(it2+1)).getX(), (*(it2+1)).getY());
					Point *middle = middle_point(a,b);
					double angle = atan2(((*(it2+1)).getY() - (*it2).getY()), ((*(it2+1)).getX() - (*it2).getX()));
					double distance = two_points_distance(a,b);
					file << "\t<link name=\""<< "wall" << count <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << middle->getX() << " " << middle->getY() << " " << (*it1).height/2 << "\" rpy=\"0 0 "<< angle <<"\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << distance << " "<< (*it1).thickness << " " << (*it1).height << "\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
					count++;
				}
				else{
					Point *a =  new Point((*it2).getX(), (*it2).getY());
					Point *b =  new Point((*(it2+1)).getX(), (*(it2+1)).getY());
					Point *middle = middle_point(a,b);
					double angle = atan2(((*(it2+1)).getY() - (*it2).getY()), ((*(it2+1)).getX() - (*it2).getX()));
					double distance = two_points_distance(a,b);
					file << "\t<link name=\""<< "wall" << count <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << middle->getX() << " " << middle->getY() << " " << (*it1).height/2 << "\" rpy=\"0 0 "<< angle <<"\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << distance << " "<< (*it1).thickness << " " << (*it1).height << "\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
					file << "\t<link name=\""<< "complement" << complement++ <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << a->getX() << " " << a->getY() << " " << (*it1).height/2 << "\" rpy=\"0 0 "<< angle <<"\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << (*it1).thickness << " "<< (*it1).thickness << " " << (*it1).height << "\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
					count++;
				}
				iteration++;
			}
		}
		else{
			for(vector<Point>::iterator it2 = (*it1).corner_list->begin() ; it2 != (*it1).corner_list->end()-1; ++it2){

				Point *a =  new Point((*it2).getX(), (*it2).getY());
				Point *b =  new Point((*(it2+1)).getX(), (*(it2+1)).getY());
				Point *middle = middle_point(a,b);
				double angle = atan2(((*(it2+1)).getY() - (*it2).getY()), ((*(it2+1)).getX() - (*it2).getX()));
				double distance = two_points_distance(a,b);
				file << "\t<link name=\""<< "wall" << count <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"" << middle->getX() << " " << middle->getY() << " " << (*it1).height/2 << "\" rpy=\"0 0 "<< angle <<"\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << distance << " "<< (*it1).thickness << " " << (*it1).height << "\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
				count++;
			}
		}


	}
}

void Walls::URDFOutputRotate(ofstream& file){
	int count = 1;

	printRobot(file);

	for (vector<Wall>::iterator it1 = walls->begin() ; it1 != walls->end(); ++it1){
		for(vector<Point>::iterator it2 = (*it1).corner_list->begin() ; it2 != (*it1).corner_list->end()-1; ++it2){

				Point *a =  new Point((*it2).getX(), (*it2).getY());
				Point *b =  new Point((*(it2+1)).getX(), (*(it2+1)).getY());
				Point *middle = middle_point(a,b);
				double angle = atan2(((*(it2+1)).getY() - (*it2).getY()), ((*(it2+1)).getX() - (*it2).getX()));
				double distance = two_points_distance(a,b);
				file << "\t<link name=\""<< "wall" << count <<"\">\n\t\t<visual>\n\t\t\t<origin xyz=\"0 0 0\" rpy=\"0 0 "<< angle <<"\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"" << distance << " "<< (*it1).thickness << " " << (*it1).height << "\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n";
				file << "\t<joint name=\""<< "joint" << count <<"\" type=\"continuous\">\n\t\t<parent link=\"wall"<< count <<"\"/>\n\t\t<child link=\"wall" << count << "\"/>\n\t\t<origin xyz=\"" << middle->getX() << " " << middle->getY() << " " << (*it1).height/2 << "\" rpy=\"0 0 0\"/>\n\t\t<axis xyz=\"0 0 1\"/>\n\t</joint>\n";
				count++;
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
			it1--; /*SIM, PARECE ESTRANHO MAS E MESMO ASSIM! DEPOIS EXPLICO SE QUISERES!! NAO MEXER*/
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
	double scalarP=0;
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
		if((scalarP = scalar_product(*series1, *series2)) != 0 ){
			return false;
		}

	}
	if(scalarP==0){
			return true;
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

void Walls::printRobot(ofstream& file){
	file << "<robot name=\"pi_robot\">\t<link name=\"Base1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2 -2 0\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"1\" length=\"0.01\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Color1\">\n\t\t\t\t<color rgba=\"0.1 0.6 0.51 0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"Base2_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2 -2 0.5\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"1\" length=\"0.01\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Color1\">\n\t\t\t\t<color rgba=\"0.8 0.8 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t\t\t<link name=\"unionBase1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.5 -1.5 0.25\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.5\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"unionBase2_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.5 -2.5 0.25\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.5\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"unionBase3_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.5 -1.5 0.25\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.5\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"unionBase4_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.5 -2.5 0.25\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.5\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Cyan1\">\n\t\t\t\t<color rgba=\"0 0.9 0.9 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t\t<link name=\"wheel1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.2 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.4\" length=\"0.08\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Black\">\n\t\t\t\t<color rgba=\"0 0 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"wheel1_1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.2 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.3\" length=\"0.08\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"White\">\n\t\t\t\t<color rgba=\"1 1 1 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"wheel2_1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.8 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.3\" length=\"0.08\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"White\">\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t\t<link name=\"wheel2_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.8 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.4\" length=\"0.08\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Black\">\n\t\t\t\t<color rgba=\"0 0 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t\t\t\t<link name=\"Motor1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.55 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.1\" length=\"0.3\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Red\">\n\t\t\t\t<color rgba=\"0.9 0 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"Motor2_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.45 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.1\" length=\"0.3\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Red\">\n\t\t\t\t<color rgba=\"0.9 0 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t\t<link name=\"Motor2Conection_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.7 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.02\" length=\"0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Grey\">\n\t\t\t\t<color rgba=\"0.5 0.5 0.5 0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"Motor1Conection_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.3 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.02\" length=\"0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Grey\">\n\t\t\t\t<color rgba=\"0.5 0.5 0.5 0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"Motor1Suport1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.55 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.15\" length=\"0.05\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"1 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"Motor2Suport1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.45 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.15\" length=\"0.05\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"1 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"Motor1Suport2_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.35 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.15\" length=\"0.05\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"1 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"Motor2Suport2_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.65 -2 0.25\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.15\" length=\"0.05\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"1 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor1_1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.45 -2 0.12\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.04 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"1 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor2_1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.55 -2 0.12\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.04 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"1 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor1_2_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.45 -2 0.38\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.04 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"1 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor2_2_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.55 -2 0.38\" rpy=\"1.5 1.5 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.04 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"1 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor1_3_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.35 -2 0.39\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"1 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor1_4_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.55 -2 0.39\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"1 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor2_3_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.65 -2 0.39\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"1 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor2_4_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.45 -2 0.39\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"0.3 0.3 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor2_5_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.45 -2 0.1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"0.3 0.3 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor2_6_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.65 -2 0.1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"0.3 0.3 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor1_5_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.55 -2 0.1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"0.3 0.3 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"suportMotor1_6_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.35 -2 0.1\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.05 0.05 0.25\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t\t<color rgba=\"0.3 0.3 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"SuportSensor_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2 -2 1.0\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.03\" length=\"1.9\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Grey\">\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t\t\t<link name=\"Sensor_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"0 0.1 1.90\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.1 0.4 0.1\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"sensorDist1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-1.74 -1.72 0.25\" rpy=\"0 0 -0.75\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.01 0.68 0.5\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"White\">\n\t\t\t\t<color rgba=\"1 1 1 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"sensorDist2_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2.26 -1.72 0.25\" rpy=\"0 0 0.75\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.01 0.68 0.5\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"White\">\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t\t<link name=\"BatterySlot_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2 -2.6 0.12\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.55 0.45 0.20\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"White\">\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t\t<link name=\"Pilha1_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2 -2.46 0.21\" rpy=\"0 1.57 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.06\" length=\"0.45\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"Pilha2_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2 -2.6 0.21\" rpy=\"0 1.57 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.06\" length=\"0.45\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"Pilha3_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2 -2.75 0.21\" rpy=\"0 1.57 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<cylinder radius=\"0.06\" length=\"0.45\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Orange\">\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t<link name=\"Board_link\">\n\t\t<visual>\n\t\t\t<origin xyz=\"-2 -2.6 00.52\" rpy=\"0 0 0\"/>\n\t\t\t<geometry>\n\t\t\t\t<box size=\"0.6 0.5 0.03\"/>\n\t\t\t</geometry>\n\t\t\t<material name=\"Green\">\n\t\t\t\t<color rgba=\"0.2 0.6 0 1.0\"/>\n\t\t\t</material>\n\t\t</visual>\n\t</link>\n\t\t<joint name=\"ServoSensor\" type=\"revolute\">\n\t\t<axis xyz=\"0 0 1\"/>\n\t\t<limit effort=\"1000.0\" lower=\"-1.57\" upper=\"1.57\" velocity=\"0.5\"/>\n\t\t<origin rpy=\"0 0 0\" xyz=\"-2 -2 0\"/>\n\t\t<parent link=\"SuportSensor_link\"/>\n\t\t<child link=\"Sensor_link\"/>\n\t</joint>\n\t\t\t\t\t\t</robot>\n";
}
