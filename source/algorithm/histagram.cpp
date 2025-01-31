//
// Created by william on 2025/1/31.
//

#include "histagram.h"

int histagram(Texture& originTexture, int hist[256], int mode)
{
    auto& info = originTexture.getInfo();
    unsigned char* srcData = info.data;
    int width = info.width;
    int height = info.height;
    int stride = info.stride;

    int ret = 0;
    int i, j, gray, offset;
    offset = stride - width * 4;
    unsigned char* pSrc = srcData;
    switch (mode)
    {
    case 0: // Gray histagram
        for (j = 0; j < height; j++)
        {
            for (i = 0; i < width; i++)
            {
                gray = (pSrc[0] + pSrc[1] + pSrc[2]) / 3;
                hist[gray]++;
                pSrc += 4;
            }
            pSrc += offset;
        }
        break;
    case 1: // Red histagram
        for (j = 0; j < height; j++)
        {
            for (i = 0; i < width; i++)
            {
                hist[pSrc[2]]++;
                pSrc += 4;
            }
            pSrc += offset;
        }
        break;
    case 2: // Green histagram
        for (j = 0; j < height; j++)
        {
            for (i = 0; i < width; i++)
            {
                hist[pSrc[1]]++;
                pSrc += 4;
            }
            pSrc += offset;
        }
        break;
    case 3: // Blue histagram
        for (j = 0; j < height; j++)
        {
            for (i = 0; i < width; i++)
            {
                hist[pSrc[0]]++;
                pSrc += 4;
            }
            pSrc += offset;
        }
        break;
    default:
        break;
    }

    return ret;
}