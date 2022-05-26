#ifndef CROMOSOMEDISTRIBUTION_HPP
#define CROMOSOMEDISTRIBUTION_HPP 1

#include <iostream>
using namespace std;

// Define the structure of the quadrant
struct cromosomeDistribution {
    int x1;
    int y1;
    int x2;
    int y2;
    float minProbability;
    float maxProbability;
    float areaQuadrant;
    float totalArea;
};


#endif