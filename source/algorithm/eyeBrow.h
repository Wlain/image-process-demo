//
// Created by william on 2025/1/30.
//

#ifndef EYEBROW_H
#define EYEBROW_H
#include "texture.h"

int eyeBrow(const Texture& originTexture, const int srcFacePoints[202], const Texture& maskTexture, const int maskKeyPoints[2 * 4], bool isLeft, int ratio);

#endif // EYEBROW_H
