#ifndef GENETICBASE_HPP
#define GENETICBASE_HPP 1
#include <vector>
#include "cromosomeDistribution.hpp"
#include "point.hpp"

#define NUM_SECTION 10

class geneticBase {
private:
    vector<Point*> fitnessPopulation;
    vector<Quadrant*> representation;
    vector<Point*> population;

    int image_Width;
    int image_Height;

    void getMinValue(vector<Quadrant*> quadrants, int* menorValor, int* index ) {

        int minorFound = INT_MAX;

        for (int i = 0; i < quadrants.size(); i++) {
            if (quadrants[i]->getTotalPoints() < minorFound) {
                minorFound = quadrants[i]->getTotalPoints();
                *menorValor = minorFound;
                *index = i;
            }
        }
    }
    void getMinimumFitness(int* minorValue, int* index) {
        int minorFound = INT_MAX;

        for (int i = 0; i < fitnessPopulation.size(); i++) {
            if (fitnessPopulation[i]->getFitness() < minorFound) {
                minorFound = fitnessPopulation[i]->getFitness();
                *minorValue = minorFound;
                *index = i;
            }
        }
    }

    void evaluateFitness() {
        fitnessPopulation.clear();


        // Get the 'bounderies' of the gray tones
        vector<int> bounderies = calculateGray();
        int total = accumulate(bounderies.begin(), bounderies.end(), 0) / bounderies.size();

        // Set the fitness value
        for (int i = 0; i < population.size(); i++) {
            fitness(i, bounderies, total);
        }


        // Get the better individuals
        float Selection_percentage = 0.4;
        int maxQuantity = ((float)population.size()) * Selection_percentage;

        fitnessPopulation.push_back(population[0]);

        int menorValor = population[0]->getFitness();
        int index = 0;

        for (int i = 1; i < population.size(); i++) {

            Point* currentPoint = population[i];

            // Si el vector no tiene la cantidad minima(el tanto %)
            if (fitnessPopulation.size() + 1 < maxQuantity) {
                fitnessPopulation.push_back(currentPoint);

                if (currentPoint->getFitness() < menorValor) {
                    menorValor = currentPoint->getFitness();
                    index = i;
                }
                continue;
            }

            // Si el vector ya esta lleno
            if (currentPoint->getFitness() > menorValor) {
                fitnessPopulation.erase(fitnessPopulation.begin() + index);
                fitnessPopulation.push_back(currentPoint);
                getMinimumFitness(&menorValor, &index);
            }
        }
    }

    void reproduce(int pAmountOfChildrens) {
        population.clear();

        for(int i = 0; i < pAmountOfChildrens; i++) {
            int parent_a_index = rand() % fitnessPopulation.size();
            Point* parent_a = fitnessPopulation[parent_a_index];

            int parent_b_index = rand() % fitnessPopulation.size();
            Point* parent_b = fitnessPopulation[parent_b_index];

            population.push_back(cross(parent_a, parent_b));
        }
    }

    Point* cross(Point* parent_a, Point* parent_b) {

        // cout << "Padre A:\n";
        // cout << parent_a->getX() << endl;
        // cout << parent_a->getY() << endl;
        // cout << "Padre B:\n";
        // cout << parent_b->getX() << endl;
        // cout << parent_b->getY() << endl;

        int cut_position = (rand() % (11-MIN_GENOTYPE_SIZE_BY_PARENT*2)) + MIN_GENOTYPE_SIZE_BY_PARENT;

        unsigned int mask_a = 2047;
        mask_a <<= cut_position;

        unsigned int mask_b = 2047;
        mask_b >>= 11 - cut_position;

        unsigned int kidPositionX = (parent_a->getX() & mask_a) | (parent_b->getX() & mask_b);
        unsigned int kidPositionY = (parent_a->getY() & mask_a) | (parent_b->getY() & mask_b);
        // cout << "Corte:\n";
        // cout << cut_position << endl;
        // cout << "Hijo:\n";
        // cout << kidPositionX << endl;
        // cout << kidPositionY << endl << endl;

        Point* children = new Point(kidPositionX, kidPositionY, (rand() % 256)/25);
        return children;
    }

public:
    geneticBase(int width, int height) {
        this->image_Width = width;
        this->image_Height = height;
    }

    

    void addDistribution(vector<Quadrant*> Quadrants_Selected) {

        // Seleccionar el % mayor
        float Selection_percentage = 0.4;
        int maxQuantity = ((float)Quadrants_Selected.size()) * Selection_percentage;

        vector<Quadrant*> mostQualified = {Quadrants_Selected[0]};

        int menorValor = Quadrants_Selected[0]->getTotalPoints();
        int index = 0;

        for (int i = 1; i < Quadrants_Selected.size(); i++) {

            Quadrant* currentQuadrant = Quadrants_Selected[i];

            // Si el vector no tiene la cantidad minima(el tanto %)
            if (mostQualified.size() + 1 < maxQuantity) {
                mostQualified.push_back(currentQuadrant);

                if (currentQuadrant->getTotalPoints() < menorValor) {
                    menorValor = currentQuadrant->getTotalPoints();
                    index = i;
                }
                continue;
            }

            // Si el vector ya esta lleno
            if (currentQuadrant->getTotalPoints() > menorValor) {
                mostQualified.erase(mostQualified.begin() + index);
                mostQualified.push_back(currentQuadrant);
                getMinValue(mostQualified, &menorValor, &index);
            }
        }

        // Aplicarle el rango del nibble
        float intervalNibble = CROMO_MAX_VALUE / mostQualified.size();
        float minProbability = 0.0;
        float maxProbability = intervalNibble;
        
        for (int i = 0; i < mostQualified.size(); i++) {
            Quadrant* currentCuadrant = mostQualified[i];

            currentCuadrant->setMinProbabilty(minProbability);
            currentCuadrant->setMaxProbabilty(maxProbability);

            minProbability = maxProbability;
            maxProbability += intervalNibble;
        }

        // Setear la distribucion
        representation = mostQualified;
    };

    void initPopulation(int pAmountInitialPopulation) {

        int intervalNibble = CROMO_MAX_VALUE / representation.size();

        for (int i = 0; i < pAmountInitialPopulation; i++) {

            int randomSelector = rand() % CROMO_MAX_VALUE;
            Quadrant* selectedCuadrant = representation[randomSelector / intervalNibble];

            int randomX = rand() % (selectedCuadrant->getUpRight().first - selectedCuadrant->getDownLeft().first) + selectedCuadrant->getDownLeft().first;
            int randomY = rand() % (selectedCuadrant->getUpRight().second - selectedCuadrant->getDownLeft().second) + selectedCuadrant->getDownLeft().second;

            population.push_back(new Point(randomX, randomY, selectedCuadrant->getGray()));
        }
    };

    vector<int> calculateGray() {
        vector<int> grayCollection = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int grayTone;

        for (Point* ind : population) {
            grayTone = ind->getGreyTone();
            grayCollection[grayTone]++;
        }

        return grayCollection;
    }

    void fitness(int indexIndividual, vector<int> bounderies, int total) {
        // Define the acceptance range
        Point* currentPoint = population[indexIndividual];
        int x1 = currentPoint->getX();
        int y1 = currentPoint->getY();

        float distance = 0.0;
        float maximumRange = 212.0;

        for (int i = 0; i < population.size(); i++) {

            // Skip the same individual
            if (i != indexIndividual) {
                Point* comparisonPoint = population[i];
                int x2 = comparisonPoint->getX();
                int y2 = comparisonPoint->getY();

                int num1 = (x2 - x1) * (x2 - x1);
                int num2 = (y2 - y1) * (y2 - y1);
                distance = sqrt(num1 + num2);

                if (distance < maximumRange)
                    currentPoint->increaseFitness(1);
            }
        }
        int grayTone = currentPoint->getGreyTone();
        if (bounderies[grayTone] > total) {
            currentPoint->increaseFitness(10);
        }
        else {
            currentPoint->increaseFitness(-5);
        }
    }

    void produceGeneration(int pAmountGeneration, int pAmoutChildren) {
        for (int i = 0; i < pAmountGeneration; i++) {
            evaluateFitness();
            reproduce(pAmoutChildren);

            // cout << "\nGeneracion " << i << endl;
            // for (int i = 0; i < population.size(); i++) {
            //     cout << population[i]->getX() << endl;
            //     cout << population[i]->getY() << endl << endl;
            // }

        }
    }

    vector<Point*> getPopulation() {
        return this->population;
    }
    vector<Quadrant*> getRepresentation() {
        return this->representation;
    }

};




#endif