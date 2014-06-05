#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <locale>
#include <cctype>
#include <string>
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

char* Challenge::getChallengeName(){
	return challenge_name;
}

char* Challenge::getChallengeType(){
	return challenge_type;
}

int Challenge::getCycleTime(){
	return cycle_time;
}

int Challenge::getDuration(){
	return duration;
}

void Challenge::validateDefaultValues(){
	if(challenge_name == NULL){
		throw NULL_CHALLENGE_NAME;
	}
	if(challenge_type == NULL){
		throw NULL_CHALLENGE_TYPE;
	}
	if(cycle_time <= 0){
		throw NULL_CYCLE_TIME;
	}
	if(duration <= 0){
		throw NULL_DURATION;
	}
	
}

void Challenge::validateIntType(char* num){
	string tmp = string(num);

    if(!is_digits(tmp)){
    	throw INT_TYPE_ERROR;
	}
}

bool Challenge::is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
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
