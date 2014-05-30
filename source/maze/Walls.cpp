#include <iostream>
#include <map>

using namespace std;

struct Point{
    int x, y;
};

/* dois tiupos de paredes, uma q tem */
thickness = 0; linha poligonal fechada, define os 6 pontos da paredes
ou é thickness ≠ 0, define só 3 pontos

struct Wall{
    int height;
    int thickness;
    LinkedList<Point>* corner_list;
};

class Walls {
    private:
    LinkedList<Wall>* walls = new LinkedList<Wall>();

	public:
    void addWall(Wall add){

    }

    void removeWall(Wall removeWall){

    }

    void modifyWall(Wall toModify, Wall newWall){

    }

    LinkedList<Wall>* pointsList(){

    }
};