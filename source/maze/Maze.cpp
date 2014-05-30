#include <iostream>
#include <map>

using namespace std;

struct Point{
    int x, y;
};

class Maze {
    private:
    char* name;
    Point* dimension = new Point(); /* largura e altura do labirinto */
    Beacons* beacons = new Beacons();
    TargetAreas* targetareas = new TargetAreas();
    Walls* walls = new Walls();
    Grid* grid = new Grid();

	public:
    
};