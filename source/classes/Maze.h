#include <iostream>
#include <fstream>
#include <vector>
#include "Beacons.h"
#include "TargetAreas.h"
#include "Walls.h"
#include "Grid.h"

using namespace std;

/* http://www.cplusplus.com/reference/vector/vector/ */

struct Dimensions{
    int width, height;
};

class Maze {
    private:
    char* name;
    Dimensions dimensions;
    Beacons *beacons;
    TargetAreas *targetareas;
    Walls *walls;
    Grid *grid;

	public:
    Maze(){
        beacons = new Beacons();
        targetareas = new TargetAreas();
        walls = new Walls();
        grid = new Grid();
    }

    void setName(char* n);

    void setDimensions(int w, int h);
    Dimensions getDimensions();

    void addBeacon(Point position, int radius, int height);
    vector<Beacon> getBeacons();

    void addTargetArea(Point position, int radius);
    vector<TargetArea> getTargetAreas();

    void addWall(int height, int thickness, vector<Point>* corner_list);
    vector<Wall> getWalls();

    void addPose(int x, int y, int teta);
    vector<Pose> getPoses();

    void printTest();

    void gridOutputXML(ofstream& file);
void labOutputXML(ofstream& file);    

};
