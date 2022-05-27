#ifndef POINT_HPP
#define POINT_HPP 1

class Point{
private:
    unsigned int x;
    unsigned int y;
    int gray;
    int fitness;

public:
    Point(int x,int y,int gray){
        this->x = x;
        this->y = y;
        this->gray = gray;
        this->fitness = 0;
    }

    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
    int getGreyTone() {
        return this->gray;
    }
    void increaseFitness(int inc) {
        this->fitness += inc;
    }
    int getFitness() {
        return this->fitness;
    }
};
#endif