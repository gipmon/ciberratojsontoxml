#ifndef POINT_H
#define POINT_H
class Point {
    private:
    int x, y;

	public:
    Point(int x, int y) : x(x), y(y) {}
    int getX(){ return x; }
    int getY(){ return y; }
};
#endif