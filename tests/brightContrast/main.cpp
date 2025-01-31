//
// Created by william on 2025/1/31.
//
#include "brightContrast.h"
int main()
{
    Texture dog("dog.png");
    brightContrast(dog, 50,50);
    dog.save("dog_brightContrast_50_50.png");
    return 0;
}