#include <iostream>
#include <fstream>
#include <vector>
#include "Beacons.h"
#include "TargetAreas.h"
#include "Walls.h"
#include "Grid.h"
#include "Models.h"
#include "SuperModels.h"

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
    Models *models;
    SuperModels *supermodels;

	public:
    Maze(){
        beacons = new Beacons();
        targetareas = new TargetAreas();
        walls = new Walls();
        grid = new Grid();
        models = new Models();
        supermodels = new SuperModels();
    }

    void setName(char* n);

    void setDimensions(double w, double h);
    Dimensions getDimensions();

    void addBeacon(Point position, double height);
    vector<Beacon> getBeacons();
    int countBeacons();

    void addTargetArea(Point position, double radius);
    vector<TargetArea> getTargetAreas();
    int countTargetAreas();

    void addWall(double height, double thickness, vector<Point>* corner_list);
    vector<Wall> getWalls();
    int countWalls();

    void addPose(double x, double y, double teta);
    vector<Pose> getPoses();

    void validateScenarioDescription();

    void validateBeaconsPoints(double x, double y);
    void validateTargetAreaPoints(double x, double y);
    void validateWallsPoints(double x, double y);

    void addModel(char* name, double h, Point fp, Point sp, double t);
    void loadModel(const char* name, double x, double y, double rot);
    int existsModel(const char* name);

    void createSuperModel(const char* name);
    void addModelToSuperModel(const char* supermodel_name, Model add);
    bool superModelExists(const char* name);
    void loadSuperModeltoWalls(const char* name, double x, double y, double rot); 

    void printTest();
    void printTestModels();

    void removeNotPerpendicularWalls();

    void modify_vector(vector<Point>* cl);
    void gridOutputXML(ofstream& file);
    void labOutputXML(ofstream& file);
    void URDFOutput(ofstream& file);

};
