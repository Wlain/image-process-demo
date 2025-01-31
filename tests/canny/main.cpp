//
// Created by william on 2025/1/31.
//
#include "canny.h"
int main()
{
    Texture dog("dog.png");
    cannyEdgedetection(dog, 30, 50);
    dog.save("dog_cannyEdgedetection.png");
}