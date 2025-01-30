//
// Created by william on 2025/1/30.
//

#ifndef EYESHADOW_H
#define EYESHADOW_H
#include "texture.h"
int eyeShadow(const Texture& originTexture, const int srcFacePoints[202], const Texture& maskTexture, const int maskKeyPoints[2 * 2], bool isLeft, int mode, int ratio);

#endif // EYESHADOW_H
