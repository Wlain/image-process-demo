//
// Created by william on 2025/1/30.
//

#ifndef MAKEUPBASE_H
#define MAKEUPBASE_H
#include "texture.h"

int makeupBase(const Texture& originTexture, const int srcKeyPoints[2 * 3], const Texture& maskTexture, const int maskKeyPoints[2 * 3], int ratio);

#endif //MAKEUPBASE_H
