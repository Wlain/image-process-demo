//
// Created by william on 2025/1/30.
//

#ifndef EYELID_H
#define EYELID_H
#include "texture.h"

int eyeLid(const Texture& originTexture, const int srcFacePoints[202], const Texture& maskTexture, const int maskKeyPoints[2 * 3], bool isLeft, int ratio);

#endif //EYELID_H
