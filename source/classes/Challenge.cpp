#include <iostream>
#include <vector>
#include "Challenge.h"
#include <iostream>
#include <fstream>

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
    std::cout << "\n!!CHALLENGE!!\n" << "challenge name : " << challenge_name << "\n" << "challenge type : " << challenge_type << "\n" << "cycle time : " << cycle_time << "\n" << "duration : " << duration << "\n" << std::endl;
    maze->printTest();
    pm->printTest();
}

void Challenge::gridOutputXML(){
	maze->gridOutputXML();
}

void Challenge::labOutputXML(ofstream& file){
	
	maze->labOutputXML(file);
}
