#include <iostream>
#include <vector>
/* http://www.cplusplus.com/reference/std::vector/std::vector/ */

struct Pose{
    int x, y, teta; /* teta => orientação do robot */
};

class Grid {
    private:
    std::vector<Pose>  *posesList;

	public:
    Grid(){ posesList = new std::vector<Pose>();}
    void addPose(Pose add);
    void removePose(Pose removePose);
    void modifyPose(Pose toModify, Pose newPose);
    std::vector<Pose> getPosesList();

    void printTest();

    void gridOutputXML();
};
