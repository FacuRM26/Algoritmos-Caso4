#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "socketClient.hpp"

#include "genetic/probabilist.hpp"
#include "genetic/geneticBase.hpp"

int main() {

    // Socket Initialization
    socketclient client;
    client.init();
    client.clear();


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

    // Set the probabilistic chart
    Probabilist probabilist(width, height, 500, 400000, 20, image);
    probabilist.sample();
    
    vector<Quadrant *> quadrantsSelected = probabilist.getQuadrants();

    // Start the genetic
    geneticBase Genetic(width, height);
    Genetic.addDistribution(quadrantsSelected);
    Genetic.initPopulation(500);
    Genetic.produceGeneration(10, 700);

    // Paint the points into the screen
    vector<Point*> pop = Genetic.getPopulation();
    for (Point* i : pop) {
        client.paintDot(i->getGreyTone()*25,i->getGreyTone()*25,i->getGreyTone()*25,255,
            i->getX(), i->getY(), rand() % 10);
    }

    // Free the socket and the image
    client.closeConnection();
    stbi_image_free(image);
    return 0;
}