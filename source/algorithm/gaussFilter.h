//
// Created by william on 2025/1/31.
//

#ifndef GAUSSFILTER_H
#define GAUSSFILTER_H
#include "texture.h"
int fastGaussFilter(const Texture& originTexture, float r);
int fastGaussFilter(unsigned char* srcData,int width, int height,int stride,float r);

#endif // GAUSSFILTER_H
