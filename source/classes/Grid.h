#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Pose{
    int x, y, teta; /* teta => orientação do robot */
};

class Grid {
    private:
    vector<Pose>  *posesList;

	public:
    Grid(){ posesList = new vector<Pose>();}
    void addPose(Pose add);
    void removePose(Pose removePose);
    void modifyPose(Pose toModify, Pose newPose);
    vector<Pose> getPosesList();

    void printTest();

    void gridOutputXML(ofstream& file);
};
