//
// Created by william on 2025/1/30.
//

#ifndef FACEBLUSH_H
#define FACEBLUSH_H
#include "texture.h"

int faceBlush(const Texture& originTexture, const int srcFacePoints[202], const Texture& maskTexture, const int maskKeyPoints[2 * 3], bool isLeft, int ratio);

#endif // FACEBLUSH_H
