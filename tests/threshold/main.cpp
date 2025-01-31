//
// Created by william on 2025/1/31.
//
#include <threshold.h>

int main()
{
    Texture dog("dog.png");
    threshold(dog, 100);
    dog.save("dog_threshold_100.png");
    return 0;
}