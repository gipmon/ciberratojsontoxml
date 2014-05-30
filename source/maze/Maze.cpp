#include <iostream>
#include <map>

using namespace std;

struct Dimensions{
    int width, height;
};

class Maze {
    private:
    char* name;
    Dimensions* dimension = new Dimensions();
    Beacons* beacons = new Beacons();
    TargetAreas* targetareas = new TargetAreas();
    Walls* walls = new Walls();
    Grid* grid = new Grid();

	public:

};