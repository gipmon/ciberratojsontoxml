#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <locale>
#include <cctype>
#include <cstring>
#include <string>
#include "Challenge.h"

using namespace std;

void Challenge::setChallengeName(char* c_name){
	if(c_name == NULL){
		throw NULL_CHALLENGE_NAME;
	}
	challenge_name = c_name;
}

void Challenge::setChallengeType(char* c_type){
	if(c_type == NULL){
		throw NULL_CHALLENGE_TYPE;
	}
	challenge_type = c_type;
}

void Challenge::setCycleTime(int c_time){
	if(c_time <= 0){
		throw NULL_CYCLE_TIME;
	}
	cycle_time = c_time;
}

void Challenge::setDuration(int d){
	if(d <= 0){
		throw NULL_DURATION;
	}

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

void Challenge::setParametersWithDefaultValues(){
	pm->setParametersWithDefaultValues();
}

void Challenge::validateRequiredValues(){
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

void Challenge::validateScenarioDescription(){
	maze->validateScenarioDescription();
}

void Challenge::validateTypes(char* value_type, char* value){
	if(!strcmp("uint", value_type)){
		validateIntType(value);
	}else if(!strcmp("double", value_type)){
		validateDoubleType(value);
	}else if(!strcmp("boolean", value_type)){
		validateBooleanType(value);
	}else if(!strcmp("switch", value_type)){
		validateSwitchType(value);
	}
}

void Challenge::validateIntType(char* num){
	string tmp = string(num);
	if(!is_digits(tmp)){
		throw INT_TYPE_ERROR;
	}
}

void Challenge::validateDoubleType(char* num){
	string tmp = string(num);
	if(!is_Doubledigits(tmp)){
		throw DOUBLE_TYPE_ERROR;
	}
}

void Challenge::validateBooleanType(char* value){
	if(strcmp("true", value) && strcmp("false", value)){
		throw BOOLEAN_TYPE_ERROR;
	}
}

void Challenge::validateSwitchType(char* value){
	if(strcmp("on", value) && strcmp("off", value)){
		throw SWITCH_TYPE_ERROR;
	}
}

bool Challenge::is_Doubledigits(const string &str){
	return str.find_first_not_of("0123456789.") == string::npos;
}

bool Challenge::is_digits(const string &str)
{
    return str.find_first_not_of("0123456789") == string::npos;
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

void Challenge::URDFOutputRotate(ofstream& file){
    maze->URDFOutputRotate(file);
}

void Challenge::URDFOutputFixed(ofstream& file){
    maze->URDFOutputFixed(file);
}
