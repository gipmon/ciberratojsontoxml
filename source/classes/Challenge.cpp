#include <iostream>
#include <vector>
#include "Challenge.h"

Maze* Challenge::getMaze(){
	return maze;
}

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

void Challenge::setDuration(int duration){
	duration = duration;
}
