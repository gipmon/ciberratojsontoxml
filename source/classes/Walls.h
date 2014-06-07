#include <iostream>
#include <vector>
#include <fstream>
#include "Point.h"

using namespace std;

struct Wall{
    double height;
    /* thickness = 0; linha poligonal fechada, define os 6 pontos da paredes ou é thickness ≠ 0, define só 3 pontos */
    double thickness;
    vector<Point>* corner_list;
};

class Walls {
    private:
    vector<Wall>* walls;

	public:
    Walls(){ walls = new vector<Wall>();}
    void addWall(Wall add);
    void removeWall(Wall removeWall);
    void modifyWall(Wall toModify, Wall newWall);
    vector<Wall> wallsList();

    int countWalls();

    void printTest();

    void removeNotPerpendicularWalls();
    int scalar_product(vector<double> a, vector<double> b);
    bool validate_corner_list(vector<Point>* cl);

    void labOutputXML(ofstream& file);
    void URDFOutputRotate(ofstream& file);
    void URDFOutputFixed(ofstream& file);
    Point* middle_point(Point* a, Point* b);
    double two_points_distance(Point* a, Point* b);
};
