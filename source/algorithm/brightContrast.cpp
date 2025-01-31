//
// Created by william on 2025/1/31.
//

#include "brightContrast.h"

int brightContrast(const Texture& originTexture, int bright, int contrast)
{
    auto& info = originTexture.getInfo();
    unsigned char* srcData = info.data;
    int width = info.width;
    int height = info.height;
    int stride = info.stride;

    int ret = 0;
    bright = std::clamp(bright, -100, 100);
    contrast = std::clamp(contrast, -100, 100);
    // compute average light of image
    int Average = 0;
    int offset = stride - width * 4;
    unsigned char* pSrc = srcData;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            Average += (299 * pSrc[2] + 587 * pSrc[1] + 114 * pSrc[0]) / 1000;
            pSrc += 4;
        }
        pSrc += offset;
    }
    Average = Average / (width * height);
    pSrc = srcData;
    unsigned char BC_MAP[256];
    int temp = 0;
    for (int i = 0; i < 256; i++)
    {
        int temp = contrast > 0 ? std::clamp(i + bright, 0, 255) : i;
        if (contrast > 0)
        {
            temp = std::clamp(i + bright, 0, 255);
            temp = std::clamp(Average + (temp - Average) * (1.0f / (1.0f - contrast / 100.0f)), 0.0f, 255.f);
        }
        else
        {
            temp = i;
            temp = std::clamp(Average + (temp - Average) * (1.0f + contrast / 100.0f), 0.0f, 255.f);
            temp = std::clamp(temp + bright, 0, 255);
        }
        BC_MAP[i] = temp;
    }
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            pSrc[0] = BC_MAP[pSrc[0]];
            pSrc[1] = BC_MAP[pSrc[1]];
            pSrc[2] = BC_MAP[pSrc[2]];
            pSrc += 4;
        }
        pSrc += offset;
    }
    return ret;
}