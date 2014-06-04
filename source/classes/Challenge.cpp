#include <iostream>
#include <vector>
#include <fstream>
#include "Challenge.h"

using namespace std;

void Challenge::addParameter(){

}

void Challenge::setChallengeName(char* c_name){
	challenge_name = c_name;
}

void Challenge::setChallengeType(char* c_type){
	challenge_type = c_type;
}

void Challenge::setCycleTime(int c_time){
	cycle_time = c_time;
}

void Challenge::setDuration(int d){
	duration = d;
}

void Challenge::printTest(){
    cout << "\n!!CHALLENGE!!\n" << "challenge name : " << challenge_name << "\n" << "challenge type : " << challenge_type << "\n" << "cycle time : " << cycle_time << "\n" << "duration : " << duration << "\n" << endl;
    maze->printTest();
    pm->printTest();
}

void Challenge::gridOutputXML(ofstream& file){
	maze->gridOutputXML(file);
}

void Challenge::labOutputXML(ofstream& file){
	maze->labOutputXML(file);
}

void Challenge::paramOutputXML(ofstream& file, ParamTable *param_table){
	file << "<Parameters SimTime=\"" << duration << "\" CycleTime=\"" << cycle_time << "\" ";
	pm->paramOutputXML(file, param_table);
	file << "\n/>";
	file.close();
}

void Challenge::URDFOutput(ofstream& file){
    maze->URDFOutput(file);
}
