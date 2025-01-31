//
// Created by william on 2025/1/31.
//
#include "gaussFilter.h"
int main()
{
    Texture dog("dog.png");
    fastGaussFilter(dog, 5);
    dog.save("dog_fastGaussFilter.png");
}