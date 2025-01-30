//
// Created by william on 2025/1/31.
//
#include "labAdjust.h"
int main()
{
    {
        Texture dog("dog.png");
        labAdjust(dog, 0);
        dog.save("dog_l.png");
    }
    {
        Texture dog("dog.png");
        labAdjust(dog, 1);
        dog.save("dog_a.png");
    }
    {
        Texture dog("dog.png");
        labAdjust(dog, 2);
        dog.save("dog_b.png");
    }
    return 0;
}