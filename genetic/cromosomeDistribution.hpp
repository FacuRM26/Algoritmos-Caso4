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
    int shape;
    int size;
    int grayTone;
    int quantity;
    int totalQuantity;
    float minProbability;
    float maxProbability;
};


#endif