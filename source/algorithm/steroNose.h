//
// Created by william on 2025/1/30.
//

#ifndef STERONOSE_H
#define STERONOSE_H

#include "texture.h"

int makeupBaseSteronose(const Texture& originTexture, const int srcKeyPoints[2 * 3], const Texture& maskTexture, const int maskKeyPoints[2 * 3], int ratio);
int steroNose(const Texture& originTexture, const int srcFacePoints[202],  const Texture& maskTexture, const int maskKeyPoints[2 * 3], int ratio);
#endif //STERONOSE_H
