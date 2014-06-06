#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Pose{
    double x, y, teta; /* teta => orientação do robot por isso tem de estar entre -180 e 180 */
};

class Grid {
    private:
    vector<Pose>  *posesList;

	public:
    Grid(){ posesList = new vector<Pose>(); }
    void addPose(Pose add);
    void removePose(Pose removePose);
    void modifyPose(Pose toModify, Pose newPose);
    vector<Pose> getPosesList();


    int countPoses();

    void printTest();

    void gridOutputXML(ofstream& file);
    void URDFOutput(ofstream& file);
};
