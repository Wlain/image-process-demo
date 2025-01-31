//
// Created by william on 2025/1/31.
//

#include "gray.h"
int main()
{
    {
        Texture dog("dog.png");
        gray(dog, 0);
        dog.save("dog_mean_gray_method.png");
    }
    {
        Texture dog("dog.png");
        gray(dog, 1);
        dog.save("dog_classic_gray_method.png");
    }
    {
        Texture dog("dog.png");
        gray(dog, 2);
        dog.save("dog_photoshop_gray_method.png");
    }
    return 0;
}