//
// Created by william on 2025/1/31.
//
#include "yuvAdjust.h"

int main()
{
    {
        Texture dog("dog.png");
        yuvAdjust(dog, 0);
        dog.save("dog_v.png");
    }
    {
        Texture dog("dog.png");
        yuvAdjust(dog, 1);
        dog.save("dog_v.png");
    }
    {
        Texture dog("dog.png");
        yuvAdjust(dog, 2);
        dog.save("dog_v.png");
    }
    return 0;
}