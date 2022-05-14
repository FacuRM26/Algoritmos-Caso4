//Link del Jamboar https://jamboard.google.com/d/1VLKBIY-nAF1BT9_USrzkJGjmS6Ls--JVPn31pt8yDC8/edit?usp=sharing
#include <bits/stdc++.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "quadrant.hpp"
using namespace std;



int main() {
    vector<Quadrant*> quadrants;

    int width, height, channels;
    unsigned char *image = stbi_load("zelda.jpg", &width, &height, &channels, 0);
    size_t imageSize = width * height * channels;
    int area = width * height;

    if(image!=NULL) { 
        cout << "Image loaded successfully" << endl;
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Channels: " << channels << endl;
        cout << "Image size: " << imageSize << endl;
    } else {
        cout << "Image not loaded" << endl;
    }

    Quadrant leftTop(make_pair(0, 0), make_pair(width/2, height/2));
    Quadrant rightTop(make_pair(width/2, 0), make_pair(width, height/2));
    Quadrant leftBottom(make_pair(0, height/2), make_pair(width/2, height));
    Quadrant rightBottom(make_pair(width/2, height/2), make_pair(width, height));

    quadrants.push_back(&leftTop);
    quadrants.push_back(&rightTop);
    quadrants.push_back(&leftBottom);
    quadrants.push_back(&rightBottom);


    const size_t RGB = 3;


    for (int i = 0; i < quadrants.size(); i++) {
        Quadrant* quadrant = quadrants[i];
        int pixeles = (area*0.40)/4;
        while (pixeles > 0) {
            int randomX = rand() % (quadrant->getUpRight().first - quadrant->getDownLeft().first) + quadrant->getDownLeft().first;
            int randomY = rand() % (quadrant->getUpRight().second - quadrant->getDownLeft().second) + quadrant->getDownLeft().second;

            size_t index = RGB * (randomY * width + randomX);
            int red = image[index];
            int green = image[index + 1];
            int blue = image[index + 2];
            quadrant->verifyRange(red, green, blue);
            pixeles--;
        }
    }

    
    for (Quadrant* quadrant : quadrants) {
        quadrant->getPredominantColorRange();
    }


    // for (Quadrant* quadrant : quadrants) {
    //     cout << "Quadrant " << i << endl;
    //     quadrant->getRanges();
    //     i++;
    // }

}
