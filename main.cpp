#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "genetic/geneticBase.hpp"


int main() {
    // Load Image Section
    int width, height, channels;
    unsigned char *image = stbi_load("images/cara2.jpg", &width, &height, &channels, 0);
    
    size_t imageSize = width * height * channels;
    int area = width * height;
    
    if (image != NULL) {
        cout << "Image loaded successfully" << endl;
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Channels: " << channels << endl;
        cout << "Image size: " << imageSize << endl;
    }
    else {
        cout << "Image not loaded" << endl;
        exit(1);
    }

    // Class Genetic
    geneticBase Genetic(width, height);

    // 0. Distribution is dinamic so in every generation is updated

    // 1. Initialize the population
    Genetic.initPopulation(10);



    vector<cromosomeDistribution> prueba = Genetic.getRepresentation();
    for (auto i : prueba) {
        cout << "Quadrant " << &i << endl;
        cout << i.areaQuadrant << endl;
        cout << i.minProbability << endl;
        cout << i.maxProbability << endl << endl;
    }

    stbi_image_free(image);
    return 0;
}