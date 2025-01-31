//
// Created by william on 2025/1/29.
//

#ifndef MEANFILTER_H
#define MEANFILTER_H
#include "texture.h"

// fast mean filter based histagram computation
int fastMeanFilter(const Texture& originTexture, int radius);
int fastMeanFilter(unsigned char* srcData, int width, int height, int stride, int radius);

int meanFilter(const Texture& originTexture, int radius);
int meanFilter(unsigned char* srcData, int width, int height, int stride, int radius);

#endif //MEANFILTER_H
