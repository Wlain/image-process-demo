//
// Created by william on 2025/1/31.
//

#ifndef SOBEL_H
#define SOBEL_H

#include "texture.h"
int sobel(const Texture& originTexture, int threshold);
int findEdges(const Texture& originTexture);

#endif // SOBEL_H
