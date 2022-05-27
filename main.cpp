#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "socketClient.hpp"

#include "genetic/probabilist.hpp"
#include "genetic/geneticBase.hpp"

int main() {

    socketclient client;
    client.init();
    client.clear();


    // Load Image Section
    int width, height, channels;
    unsigned char *image = stbi_load("images/cara2.jpg", &width, &height, &channels, 0);

    size_t imageSize = width * height * channels;
    int area = width * height;

    if (image != NULL)
    {
        cout << "Image loaded successfully" << endl;
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Channels: " << channels << endl;
        cout << "Image size: " << imageSize << endl;
    }
    else
    {
        cout << "Image not loaded" << endl;
        exit(1);
    }

    Probabilist proba(width, height, 500, 400000, 20, image);
    proba.sample();
    
    vector<Quadrant *> prueba = proba.getQuadrants();

    // for (Quadrant* i : prueba) {
    //     cout << i->getGray() << endl;
    // }


    geneticBase Genetic(width, height);
    Genetic.addDistribution(prueba);
    Genetic.initPopulation(500);


    Genetic.produceGeneration(10, 700);

    // vector<Quadrant*> qua = Genetic.getRepresentation();
    // for (Quadrant* i : qua) {
    //     client.paintLine(255, 15, 15, 255, i->getDownLeft().first, i->getDownLeft().second,
    //         i->getUpRight().first, i->getUpRight().second);
    // }

    vector<Point*> pop = Genetic.getPopulation();
    for (Point* i : pop) {
        client.paintDot(i->getGreyTone()*25,i->getGreyTone()*25,i->getGreyTone()*25,255,
            i->getX(), i->getY(), rand() % 10);
    }

    client.closeConnection();
    stbi_image_free(image);
    return 0;
}