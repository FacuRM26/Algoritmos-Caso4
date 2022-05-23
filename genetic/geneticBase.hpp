#ifndef GENETICBASE_HPP
#define GENETICBASE_HPP 1
#include <vector>
#include "cromosomeDistribution.hpp"
#include "quadrant.hpp"


class geneticBase {
private:
    vector<cromosomeDistribution> representation;
    vector<Quadrant*> population;

    int image_Width;
    int image_Height;

public:
    geneticBase(int width, int height) {
        this->image_Width = width;
        this->image_Height = height;
    }

    void updateDistribution() {
        int width = 0;
        int height = 0;
        int areaPerQuadrant = 0;
        int totalArea = 0;

        // Set the individual area of each quadrant
        for(int i = 0; i < representation.size(); i++) {

            cromosomeDistribution* individual = &representation[i];

            width  = abs(individual->x1 - individual->x2);
            height = abs(individual->y1 - individual->y2);

            areaPerQuadrant = width * height;
            totalArea += areaPerQuadrant;

            individual->areaQuadrant = areaPerQuadrant;
        }

        // Set the total area and the probability in every quadrant distribution
        float minProbability = 0.0;
        float maxProbability = 0.0;
        float intervalProbability = 0.0;

        for (int i = 0; i < representation.size(); i++) {

            cromosomeDistribution* individual = &representation[i];

            individual->totalArea = totalArea;

            intervalProbability = individual->areaQuadrant/individual->totalArea;
            maxProbability = minProbability + intervalProbability;

            individual->minProbability = minProbability;
            individual->maxProbability = maxProbability;

            minProbability += intervalProbability;
        }

    }

    void addDistribution() {
        for (Quadrant* individualQuadrant : population) {
            pair<int, int> Quadrant_DownLeft = individualQuadrant->getDownLeft();
            pair<int, int> Quadrant_UpRight  = individualQuadrant->getUpRight();

            representation.push_back(
            {
                Quadrant_DownLeft.first,
                Quadrant_DownLeft.second,
                Quadrant_UpRight.first,
                Quadrant_UpRight.second,
                0.0,
                0.0,
                0.0,
                0.0
            });
        }
    };

    void initPopulation(int pAmountInitialPopulation) {
        population.clear();

        // Generate the first population
        for (int i = 0; i < pAmountInitialPopulation; i++) {
            int randomX = 15 + rand() % (this->image_Width - 30);
            int randomY = 15 + rand() % (this->image_Height - 30);

            pair<int, int> downLeft = make_pair(randomX - 15, randomY - 15);
            pair<int, int> upRight  = make_pair(randomX + 15, randomY + 15);
            
            // Buscar un random que sirva basado en CROMO_MAX_VALUE
            Quadrant *newQuadrant = new Quadrant(downLeft, upRight, 777);
            population.push_back(newQuadrant);
        }

        // Create the distribution based on the population
        addDistribution();
        updateDistribution();
    };

    vector<cromosomeDistribution> getRepresentation() {
        return representation;
    }
    vector<Quadrant*> getPopulation() {
        return population;
    }
};




#endif