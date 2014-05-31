#include <iostream>
#include <vector>
#include "Point.h"
/* http://www.cplusplus.com/reference/std::vector/std::vector/ */

struct TargetArea{
    Point position;
    int radius;
};

/* no futuro pode ter várias formas, para já é circular*/

class TargetAreas {
    private:
    std::vector<TargetArea>* targetareas;

	public:
    TargetAreas(){ targetareas = new std::vector<TargetArea>();}
    void addTargetArea(TargetArea add);
    void removeTargetArea(TargetArea removeWall);
    void modifyTargetArea(TargetArea toModify, TargetArea newWall);
    std::vector<TargetArea> targetAreasList();

    void printTest();
};