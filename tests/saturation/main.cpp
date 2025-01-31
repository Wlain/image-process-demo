//
// Created by william on 2025/1/31.
//

#include "saturation.h"
int main()
{
    Texture dog("dog.png");
    saturation(dog, 100);
    dog.save("dog_saturation.png");
    return 0;
}