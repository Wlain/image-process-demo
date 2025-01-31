//
// Created by william on 2025/1/31.
//
#include "usm.h"
int main()
{
    Texture dog("dog.png");
    usm(dog, 100, 100, 20);
    dog.save("dog_usm.png");
}
