//
// Created by william on 2025/1/30.
//

#ifndef EYELINE_H
#define EYELINE_H
#include "texture.h"

int eyeLine(const Texture& originTexture, const int srcFacePoints[202], const Texture& maskTexture, const int maskKeyPoints[2 * 3], bool isLeft, int ratio);

#endif // EYELINE_H
