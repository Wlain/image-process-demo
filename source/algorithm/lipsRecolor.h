//
// Created by william on 2025/1/31.
//

#ifndef LIPSRECOLOR_H
#define LIPSRECOLOR_H
#include "texture.h"

int lipsRecolor(const Texture& originTexture, const int srcFacePoints[202],const Texture& maskTexture, const int maskKeyPoints[2 * 28], const Texture& lipsColorLut, int ratio);

#endif //LIPSRECOLOR_H
