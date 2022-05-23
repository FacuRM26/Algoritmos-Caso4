#ifndef QUADRANT_HPP
#define QUADRANT_HPP 1

#include <bits/stdc++.h>
using namespace std;

// Pensar mejor estos valores, bro...
#define CROMO_MAX_VALUE 256
#define NIBBLE_SIZE 8
#define MIN_GENOTYPE_SIZE_BY_PARENT 2
#define AMOUNT_QUADRANTS 10

class Quadrant {
    private:
        pair<int, int> downLeft;
        pair<int, int> upRight;
        int grayValue;

        float fitnessValue;
        int cromosoma;


    public:
        Quadrant(pair<int, int> pDownLeft, pair<int, int> pUpRight, int pValue) {
            this->downLeft = pDownLeft;
            this->upRight = pUpRight;
            this->cromosoma = pValue;
        }

        int getCromosoma() {
            return this->cromosoma;
        }

        void setFitnessValue(float pValue) {
            this->fitnessValue = pValue;
        }

        float getFitnessValue() {
            return this->fitnessValue;
        }

        pair<int, int> getDownLeft() {
            return this->downLeft;
        }
        pair<int, int> getUpRight() {
            return this->upRight;
        }
};


#endif