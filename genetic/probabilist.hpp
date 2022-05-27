#ifndef PROBABILIST_HPP
#define PROBABILIST_HPP 1

#include <vector>
#include "quadrant.hpp"
#include "point.hpp"

class Probabilist
{
private:
    vector<Point*> points;
    int image_Width;
    int image_Height;
    vector<Quadrant *> quadrants;
    int placedPoint;
    float total;
    int MaxPoints;
    int QuadrantSize;
    int middle;

public:
    ~Probabilist() {
        for (Quadrant* i : quadrants) {
            delete i;
        }
        for (Point* i : points) {
            delete i;
        }
    }
    Probabilist(int width, int height, int sample, int maxPoints, int QuadrantSize)
    {
        this->image_Height = height;
        this->image_Width = width;
        this->placedPoint = 0;
        this->MaxPoints = maxPoints;
        this->total = 50000.0 + maxPoints;
        this->middle = QuadrantSize / 2;

        for (int i = 0; i < sample; i++)
        {
            int randomX = middle + rand() % (this->image_Width - QuadrantSize);
            int randomY = middle + rand() % (this->image_Height - QuadrantSize);

            pair<int, int> downLeft = make_pair(randomX - middle, randomY - middle);
            pair<int, int> upRight = make_pair(randomX + middle, randomY + middle);

            // Buscar un random que sirva basado en CROMO_MAX_VALUE
            Quadrant *newQuadrant = new Quadrant(downLeft, upRight, make_pair(width, height), total / sample);
            quadrants.push_back(newQuadrant);
        }
        updateProbability();
    }
    int chooseQuadrant(float pRandom)
    {
        for (int quadrant = 0; quadrant < quadrants.size(); quadrant++) {

            Quadrant* newQua = quadrants[quadrant];
            if (newQua->getMinProbability() < pRandom && newQua->getMaxProbability() > pRandom)
            {
                return quadrant;
            }
        }
        return -1;
    }
    void updateProbability(){
        float minProbability = 0.0;
        float maxProbability = 0.0;
        float intervalProbability = 0.0;

        for (int i = 0; i < quadrants.size(); i++) {

            Quadrant* individual = quadrants[i];
            
            intervalProbability = individual->getPoints()/total;
            //cout<<intervalProbability<<endl;
            maxProbability = minProbability + intervalProbability;

            individual->setMinProbabilty(minProbability);
            individual->setMaxProbabilty(maxProbability);

            minProbability += intervalProbability;
        }
    }
    void sample(unsigned char *image)
    {
        const size_t RGB = 3;
        while (placedPoint < MaxPoints)
        {
            updateProbability();
            // Get the center point of the quadrant
            float random = (rand() % 1001) / 1000.0f;
            int randomQuadrant = chooseQuadrant(random);
            if(randomQuadrant==-1){
                continue;
            }
            Quadrant* quadrant=quadrants[randomQuadrant];
            //cout<<"Quadrant "<<randomQuadrant<<endl;

            // Get a random point inside the cuadrant
            int randomX = rand() % (quadrant->getUpRight().first - quadrant->getDownLeft().first) + quadrant->getDownLeft().first;
            int randomY = rand() % (quadrant->getUpRight().second - quadrant->getDownLeft().second) + quadrant->getDownLeft().second;

            // Get the RGB values of the pixel selected by that point
            size_t index = RGB * (randomY * image_Width + randomX);
            int red = image[index];
            int green = image[index + 1];
            int blue = image[index + 2];
            int gray = (0.299 * red + 0.587 * green + 0.114 * blue) / 25;
            Point* newPoint = new Point(randomX, randomY, gray);
            points.push_back(newPoint);
            total--;
            placedPoint++;
            quadrant->increasePoints();
            incrementQuadrant(image, quadrant, gray);
        }
        cout<<points.size()<<endl;
    }
    void incrementQuadrant(unsigned char *image, Quadrant *quadrant, int gray)
    {
        int count = 0;
        const size_t RGB = 3;
        while (count < 20)
        {
            int randomX2 = rand() % (quadrant->getUpRight().first - quadrant->getDownLeft().first) + quadrant->getDownLeft().first;
            int randomY2 = rand() % (quadrant->getUpRight().second - quadrant->getDownLeft().second) + quadrant->getDownLeft().second;
            size_t index2 = RGB * (randomY2 * image_Width + randomX2);
            int red2 = image[index2];
            int green2 = image[index2 + 1];
            int blue2 = image[index2 + 2];
            int gray2 = (0.299 * red2 + 0.587 * green2 + 0.114 * blue2) / 25;
            if (gray == gray2)
            {
                //cout<<quadrant->getArea()<<endl;
                if (quadrant->getArea() < 2500)
                {
                    // cout << "Downleft " << quadrant->getDownLeft().first << ", " << quadrant->getDownLeft().second << endl;
                    // cout << "UpRight " << quadrant->getUpRight().first << ", " << quadrant->getUpRight().second << endl;
                    if( (quadrant->getDownLeft().first == image_Width || quadrant->getDownLeft().second == image_Height || quadrant->getUpRight().first == image_Width || quadrant->getUpRight().second == image_Height)){
                        count = 10;
                    }
                    else if (quadrant->getDownLeft().first == 0 || quadrant->getDownLeft().second == 0 || quadrant->getUpRight().first == 0 || quadrant->getUpRight().second == 0)
                    {
                        count = 10;
                    }
                    else if (quadrant->getUpRight().first - middle> randomX2 & quadrant->getUpRight().second - middle> randomY2)
                    {
                        //cout << "entro" << endl;
                        quadrant->setDownLeft(make_pair((quadrant->getDownLeft().first - 2), (quadrant->getDownLeft().second - 2)));
                    }
                    else if (quadrant->getUpRight().first - middle < randomX2 & quadrant->getUpRight().second - middle> randomY2)
                    {
                        //cout << "entro2" << endl;
                        quadrant->setDownLeft(make_pair(quadrant->getDownLeft().first, (quadrant->getDownLeft().second - 2)));
                        quadrant->setUpRight(make_pair((quadrant->getUpRight().first + 2), quadrant->getUpRight().second));
                    }
                    else if (quadrant->getUpRight().first - middle > randomX2 & quadrant->getUpRight().second - middle < randomY2)
                    {
                        //cout << "entro3" << endl;
                        quadrant->setDownLeft(make_pair((quadrant->getDownLeft().first - 2), quadrant->getDownLeft().second));
                        quadrant->setUpRight(make_pair(quadrant->getUpRight().first, (quadrant->getUpRight().second + 2)));
                    }
                    else if (quadrant->getUpRight().first - middle < randomX2 & quadrant->getUpRight().second - middle < randomY2)
                    {
                        //cout << "entro4" << endl;
                        quadrant->setUpRight(make_pair(quadrant->getUpRight().first + 2, quadrant->getUpRight().second + 2));
                    }
                    count++;
                    Point* newPoint = new Point(randomX2, randomY2, gray2);
                    points.push_back(newPoint);
                    total--;
                    placedPoint++;
                    quadrant->increasePoints();
                    // cout << "Downleft " << quadrant->getDownLeft().first << ", " << quadrant->getDownLeft().second << endl;
                    // cout << "UpRight " << quadrant->getUpRight().first << ", " << quadrant->getUpRight().second << endl;
                }
                else
                {
                    count++;
                    Point* newPoint = new Point(randomX2, randomY2, gray2);
                    points.push_back(newPoint);
                    total--;
                    placedPoint++;
                    quadrant->increasePoints();
                }
            }
            else
                count = 10;
        }
    }
    vector<Quadrant*> getQuadrants() {
        return quadrants;
    }
    vector<Point*> getPoints() {
        return this->points;
    }
};
#endif