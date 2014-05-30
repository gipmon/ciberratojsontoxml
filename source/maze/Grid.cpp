#include <iostream>
#include <map>

using namespace std;

struct Pose{
    int x, y, teta; /* teta => orientação do robot */
};

class Grid {
    private:
    LinkedList<Pose>* PosesList = new LinkedList<Pose>();

	public:
    void addPose(Pose add){

    }

    void removePose(Pose removePose){

    }

    void modifyPose(Pose toModify, Pose newPose){

    }

    LinkedList<Pose>* PosesList(){

    }
};