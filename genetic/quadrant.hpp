#ifndef QUADRANT_HPP
#define QUADRANT_HPP 1

#include <bits/stdc++.h>
using namespace std;

// Pensar mejor estos valores, bro...
#define CROMO_MAX_VALUE 65536
#define NIBBLE_SIZE 16
#define MIN_GENOTYPE_SIZE_BY_PARENT 5
#define AMOUNT_QUADRANTS 10

class Quadrant
{
private:
    pair<int, int> downLeft;
    pair<int, int> upRight;
    pair<int, int> size;
    float minProbability;
    float maxProbability;
    int points;
    int totalPoints;

public:
    Quadrant(pair<int, int> pDownLeft, pair<int, int> pUpRight, pair<int, int> size, int points)
    {
        this->downLeft = pDownLeft;
        this->upRight = pUpRight;
        this->size = size;
        this->points = points;
        this->totalPoints = 0;
    }

    void setDownLeft(pair<int, int> leftdown)
    {
        if (leftdown.first < 1)
            leftdown.first = 0;
        if (leftdown.second < 1)
            leftdown.second = 0;
        if (leftdown.first > size.first)
            leftdown.first = size.first;
        if (leftdown.second > size.second)
            leftdown.second = size.second;

        this->downLeft = leftdown;
    }
    void setUpRight(pair<int, int> rightUp)
    {
        if (rightUp.first < 1)
            rightUp.first = 0;
        if (rightUp.second < 1)
            rightUp.second = 0;
        if (rightUp.first > size.first)
            rightUp.first = size.first;
        if (rightUp.second > size.second)
            rightUp.second = size.second;

        this->upRight = rightUp;
    }

    pair<int, int> getDownLeft()
    {
        return this->downLeft;
    }
    pair<int, int> getUpRight()
    {
        return this->upRight;
    }
    int getPoints(){
        return points;
    }
    void increasePoints(){
        points--;
        totalPoints++;
        if(points<1){
            points=1;
        }
    }
    float getMinProbability(){
        return minProbability;
    }
    float getMaxProbability(){
        return maxProbability;
    }
    void setMinProbabilty(float pMinProba){
        this->minProbability=pMinProba;
    }
    void setMaxProbabilty(float pMaxProba){
        this->maxProbability=pMaxProba;
    }
    int getArea(){
        int width=upRight.first-downLeft.first;
        int height=upRight.second-downLeft.second;
        return width*height;
    }
    int getTotalPoints() {
        return this->totalPoints;
    }


};

#endif