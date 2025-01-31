//
// Created by william on 2025/1/31.
//
#include "laplaceSharpen.h"
int main()
{
    {
        Texture dog("dog.png");
        laplaceSharpen(dog, 0);
        dog.save("dog_laplaceSharpen_0.png");
    }
    {
        Texture dog("dog.png");
        laplaceSharpen(dog, 1);
        dog.save("dog_laplaceSharpen_1.png");
    }
}
