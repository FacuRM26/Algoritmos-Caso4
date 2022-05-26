#ifndef POINT_HPP
#define POINT_HPP 1

class Point{
private:
    int x;
    int y;
    int gray;
    int boundery;
    int distance;
public:
    Point(int x,int y,int gray){
        this->x=x;
        this->y=y;
        this->gray=gray;
    }
};
#endif