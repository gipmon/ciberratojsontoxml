#include <iostream>
#include <map>

using namespace std;

struct Point{
    int x, y, z;
};

class Grid {
    private:
    LinkedList<Point>* PointsList = new LinkedList<Point>();

	public:
    void addPoint(Point add){

    }

    void removePoint(Point removePoint){

    }

    void modifyPoint(Point toModify, Point newPoint){

    }

    LinkedList<Point>* pointsList(){

    }
};