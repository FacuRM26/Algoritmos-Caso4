// Link del Jamboar https://jamboard.google.com/d/1VLKBIY-nAF1BT9_USrzkJGjmS6Ls--JVPn31pt8yDC8/edit?usp=sharing
#include <bits/stdc++.h>
#include "quadrant.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

int main()
{
    vector<Quadrant *> quadrants;

    int width, height, channels;
    unsigned char *image = stbi_load("images/cara2.jpg", &width, &height, &channels, 0);
    size_t imageSize = width * height * channels;
    int area = width * height;
    srand(time(NULL));
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
    const size_t RGB = 3;

    /*
    // Create the initial points population
    for (int i = 0; i < 10; i++)
    {
        int randomX = 15 + rand() % (width - 30);
        int randomY = 15 + rand() % (height - 30);
        Quadrant *newQuadrant = new Quadrant(make_pair(randomX - 15, randomY - 15), make_pair(randomX + 15, randomY + 15));
        quadrants.push_back(newQuadrant);
    }


    for (int i = 0; i < quadrants.size(); i++)
    {
        Quadrant *quadrant = quadrants[i];

        int pixeles = (area * 0.40) / 10;
        while (pixeles > 0)
        {
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


    int cont = 0;
    for (Quadrant *quadrant : quadrants)
    {
        cout << "Quadrant : " << cont << endl;
        cout << "Downleft " << quadrant->getDownLeft().first << ", " << quadrant->getDownLeft().second << endl;
        cout << "UpRight " << quadrant->getUpRight().first << ", " << quadrant->getUpRight().second << endl;
        quadrant->getPredominantColorRange();
        cont++;
    }
    cout << "---------------------------" << endl;
    for (int i = 0; i < 10; i++)
    {
        // Get the center point of the quadrant
        int randomQuadrant = rand() % 10;
        Quadrant *quadrant = quadrants[randomQuadrant];

        // Get a random point inside the cuadrant
        int randomX = rand() % (quadrant->getUpRight().first - quadrant->getDownLeft().first) + quadrant->getDownLeft().first;
        int randomY = rand() % (quadrant->getUpRight().second - quadrant->getDownLeft().second) + quadrant->getDownLeft().second;
        
        // Get the RGB values of the pixel selected by that point
        size_t index = RGB * (randomY * width + randomX);
        int red = image[index];
        int green = image[index + 1];
        int blue = image[index + 2];

        int count = 0;
        while (count < 10)
        {
            int randomX2 = rand() % (quadrant->getUpRight().first - quadrant->getDownLeft().first) + quadrant->getDownLeft().first;
            int randomY2 = rand() % (quadrant->getUpRight().second - quadrant->getDownLeft().second) + quadrant->getDownLeft().second;
            size_t index2 = RGB * (randomY2 * width + randomX2);
            int red2 = image[index2];
            int green2 = image[index2 + 1];
            int blue2 = image[index2 + 2];
            
            if (red2 >= red && red2 <= red + 25)
            {

                if (green2 >= green && green2 <= green + 25)
                {

                    if (blue2 >= blue && blue2 <= blue + 25)
                    {
                        // cout << "Downleft " << quadrant->getDownLeft().first << ", " << quadrant->getDownLeft().second << endl;
                        // cout << "UpRight " << quadrant->getUpRight().first << ", " << quadrant->getUpRight().second << endl;
                        count++;
                        if(quadrant->getDownLeft().first==0 ||quadrant->getDownLeft().second==0 ||quadrant->getUpRight().first==0 ||quadrant->getUpRight().second==0 ){
                            count = 10;
                        }
                        else if (quadrant->getUpRight().first - 15 > randomX2 & quadrant->getUpRight().second - 15 > randomY2)
                        {
                            cout << "entro" << endl;
                            quadrant->setDownLeft(make_pair((quadrant->getDownLeft().first - 10), (quadrant->getDownLeft().second - 10)));
                        }
                        else if (quadrant->getUpRight().first - 15 < randomX2 & quadrant->getUpRight().second - 15 > randomY2)
                        {
                            cout << "entro2" << endl;
                            quadrant->setDownLeft(make_pair(quadrant->getDownLeft().first,( quadrant->getDownLeft().second - 10)));
                            quadrant->setUpRight(make_pair((quadrant->getUpRight().first + 10), quadrant->getUpRight().second));
                        }
                        else if (quadrant->getUpRight().first - 15 > randomX2 & quadrant->getUpRight().second - 15 < randomY2)
                        {
                            cout << "entro3" << endl;
                            quadrant->setDownLeft(make_pair((quadrant->getDownLeft().first - 10), quadrant->getDownLeft().second));
                            quadrant->setUpRight(make_pair(quadrant->getUpRight().first, (quadrant->getUpRight().second + 10)));
                        }
                        else if (quadrant->getUpRight().first - 15 < randomX2 & quadrant->getUpRight().second - 15 < randomY2)
                        {
                            cout << "entro4" << endl;
                            quadrant->setUpRight(make_pair(quadrant->getUpRight().first + 10, quadrant->getUpRight().second + 10));
                        }
                        // cout << "Downleft " << quadrant->getDownLeft().first << ", " << quadrant->getDownLeft().second << endl;
                        // cout << "UpRight " << quadrant->getUpRight().first << ", " << quadrant->getUpRight().second << endl;

                    }
                }
            }
            else
                count = 10;
        }
    }
    cout << "---------------------------" << endl;
    cont = 0;
    for (Quadrant *quadrant : quadrants)
    {
        cout << "Quadrant : " << cont << endl;
        cout << "Downleft " << quadrant->getDownLeft().first << ", " << quadrant->getDownLeft().second << endl;
        cout << "UpRight " << quadrant->getUpRight().first << ", " << quadrant->getUpRight().second << endl;
        cont++;
    }
    */

    stbi_image_free(image);
    return 0;
}
