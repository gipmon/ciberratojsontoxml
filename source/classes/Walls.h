#include <iostream>
#include <vector>
#include "Point.h"
/* http://www.cplusplus.com/reference/std::vector/std::vector/ */

struct Wall{
    int height;
    /* thickness = 0; linha poligonal fechada, define os 6 pontos da paredes ou é thickness ≠ 0, define só 3 pontos */
    int thickness;
    std::vector<Point>* corner_list;
};

class Walls {
    private:
    std::vector<Wall>* walls;

	public:
    Walls(){ walls = new std::vector<Wall>();}
    void addWall(Wall add);
    void removeWall(Wall removeWall);
    void modifyWall(Wall toModify, Wall newWall);
    std::vector<Wall> wallsList();
};