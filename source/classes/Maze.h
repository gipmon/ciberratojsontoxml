#include <iostream>
#include <fstream>
#include <vector>
#include "Beacons.h"
#include "TargetAreas.h"
#include "Walls.h"
#include "Grid.h"

using namespace std;

struct Dimensions{
    double width, height;
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

    void setDimensions(double w, double h);
    Dimensions getDimensions();

    void addBeacon(Point position, double radius, double height);
    vector<Beacon> getBeacons();

    void addTargetArea(Point position, double radius);
    vector<TargetArea> getTargetAreas();

    void addWall(double height, double thickness, vector<Point>* corner_list);
    vector<Wall> getWalls();

    void addPose(double x, double y, double teta);
    vector<Pose> getPoses();

    void printTest();

    bool validate_corner_list(vector<Point>* cl);
    void modify_vector(vector<Point>* cl);

    void gridOutputXML(ofstream& file);
    void labOutputXML(ofstream& file);
    void URDFOutput(ofstream& file);

};
