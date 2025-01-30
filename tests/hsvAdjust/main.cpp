//
// Created by william on 2025/1/28.
//

#include "texture.h"
#include "hsvAdjust.h"

int main()
{
    Texture dog("dog.png");
    hsvAdjust(dog, 0.2, 0.1, 0.1);
    dog.save("dog_hsv.png");
    return 0;
}
