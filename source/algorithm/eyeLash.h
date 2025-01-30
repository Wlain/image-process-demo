//
// Created by william on 2025/1/30.
//

#ifndef EYELASH_H
#define EYELASH_H
#include "texture.h"
int eyeLash(const Texture& originTexture, const int srcFacePoints[202], const Texture& maskTexture, const int maskKeyPoints[2 * 3], bool isLeft, int ratio);

#endif // EYELASH_H
