#ifndef POINT_H
#define POINT_H
class Point {
    private:
    double x, y;

	public:
    Point(double x, double y) : x(x), y(y) {}
    Point(){}
    double getX(){ return x; }
    double getY(){ return y; }
};
#endif