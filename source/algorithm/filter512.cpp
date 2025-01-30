//
// Created by william on 2025/1/30.
//

#include "filter512.h"

void filter512(const Texture& originTexture, const Texture& lutTexture)
{
    auto originInfo = originTexture.getInfo();
    unsigned char* srcData = originInfo.data;
    int width = originInfo.width;
    int height = originInfo.height;
    int stride = originInfo.stride;
    unsigned char* lut = lutTexture.getInfo().data;

    int pos, nx, ny, k;
    unsigned char* pSrc = srcData;
    // 处理行对齐
    int offset = stride - (width * 4);
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            int r = pSrc[0];
            int g = pSrc[1];
            int b = pSrc[2];
            k = b / 256.0f * 64;
            nx = (r / 256.0f * 64) + (k - (k / 8) * 8) * 64;
            ny = (k / 8 * (512 / 8)) + (g / 256.0f * 64);
            pos = nx * 4 + ny * 512 * 4;
            pSrc[0] = lut[pos];
            pSrc[1] = lut[pos + 1];
            pSrc[2] = lut[pos + 2];
            pSrc += 4;
        }
        pSrc += offset;
    }
}
