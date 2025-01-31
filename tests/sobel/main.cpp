//
// Created by william on 2025/1/31.
//

#include "sobel.h"

int main()
{
    {
        Texture dog("dog.png");
        sobel(dog, 80);
        dog.save("dog_sobel.png");
    }
    {
        Texture dog("dog.png");
        findEdges(dog);
        dog.save("dog_findEdges.png");
    }
    return 0;
}