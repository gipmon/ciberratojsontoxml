#include <iostream>
#include <map>

using namespace std;

struct Point{
    int x, y;
};

struct Wall{
    int height;
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