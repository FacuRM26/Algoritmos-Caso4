#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "genetic/probabilist.hpp"

int main()
{
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
    Probabilist proba(width, height, 100, 200000, 20);
    vector<Quadrant *> prueba = proba.getQuadrants();
    for (int i = 0; i < prueba.size(); i++)
    {
        Quadrant *nuevo = prueba[i];
        cout << "Quadrant " << i << endl;
        cout << nuevo->getDownLeft().first << " " << nuevo->getDownLeft().second << endl;
        cout << nuevo->getUpRight().first << " " << nuevo->getUpRight().second << endl;
        cout << nuevo->getMinProbability() << endl;
        cout << nuevo->getMaxProbability() << endl
             << endl;
    }

    proba.sample(image);
    prueba = proba.getQuadrants();
    for (int i = 0; i < prueba.size(); i++)
    {
        Quadrant *nuevo = prueba[i];
        cout << "Quadrant " << i << endl;
        cout << nuevo->getDownLeft().first << " " << nuevo->getDownLeft().second << endl;
        cout << nuevo->getUpRight().first << " " << nuevo->getUpRight().second << endl;
        cout << nuevo->getMinProbability() << endl;
        cout << nuevo->getMaxProbability() << endl
             << endl;
    }

    stbi_image_free(image);
    return 0;
}