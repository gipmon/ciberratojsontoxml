#include <vector>
#include "Beacons.h"
#include "TargetAreas.h"
#include "Walls.h"
#include "Grid.h"
#include <iostream>
#include <fstream>

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
    std::vector<Beacon> getBeacons();

    void addTargetArea(Point position, int radius);
    std::vector<TargetArea> getTargetAreas();

    void addWall(int height, int thickness, std::vector<Point>* corner_list);
    std::vector<Wall> getWalls();

    void addPose(int x, int y, int teta);
    std::vector<Pose> getPoses();

    void printTest();

    void gridOutputXML(ofstream& file);
void labOutputXML(ofstream& file);    

};
