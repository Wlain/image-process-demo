//
// Created by william on 2025/1/30.
//

#ifndef AFFINETRANSFROM_H
#define AFFINETRANSFROM_H
#include "texture.h"

void affinetransformMetrixCompute(float x1, float y1, float x2, float y2, float x3, float y3, float tx1, float ty1, float tx2, float ty2, float tx3, float ty3, float hMatrix[6]);
void getWHFromHMatrix(int width, int height, float H[6], int wh[2]);
int affineTransform(const Texture& texture, float H[6], unsigned char* dstData, int dWidth, int dHeight, int dStride);
#endif //AFFINETRANSFROM_H
