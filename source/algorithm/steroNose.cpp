//
// Created by william on 2025/1/30.
//

#include "steroNose.h"

#include "affineTransfrom.h"

#include <algorithm>

inline int ModeSuperposition(int basePixel, int mixPixel)
{
    int res = 0;
    res = ((basePixel <= 128) ? (mixPixel * basePixel / 128) : (255 - (255 - mixPixel) * (255 - basePixel) / 128));
    return std::clamp(res, 0, 255);
}

int makeupBaseSteronose(const Texture& originTexture, const int srcKeyPoints[2 * 3], const Texture& maskTexture, const int maskKeyPoints[2 * 3], int ratio)
{
    auto& info = originTexture.getInfo();
    unsigned char* srcData = info.data;
    int width = info.width;
    int height = info.height;
    int stride = info.stride;

    auto& maskInfo = maskTexture.getInfo();
    unsigned char* maskData = maskInfo.data;
    int mWidth = maskInfo.width;
    int mHeight = maskInfo.height;
    int mStride = maskInfo.stride;

    int ret = 0;
    float H[6] = { 0 };
    affinetransformMetrixCompute((float)maskKeyPoints[0], (float)maskKeyPoints[1], (float)maskKeyPoints[2], (float)maskKeyPoints[3], (float)maskKeyPoints[4], (float)maskKeyPoints[5], (float)srcKeyPoints[0], (float)srcKeyPoints[1], (float)srcKeyPoints[2], (float)srcKeyPoints[3], (float)srcKeyPoints[4], (float)srcKeyPoints[5], H);
    unsigned char* pSrc = srcData;
    int alpha = 128 * ratio / 100;
    int nalpha = 128 - alpha;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int x0 = (H[0] * i + H[1] * j + H[2]);
            int y0 = (H[3] * i + H[4] * j + H[5]);
            if (x0 > 0 && x0 < mWidth - 1 && y0 > 0 && y0 < mHeight - 1)
            {
                int pos = (x0 << 2) + y0 * mStride;
                int k = maskData[pos + 3];
                int b = ModeSuperposition(pSrc[0], maskData[pos]);
                int g = ModeSuperposition(pSrc[1], maskData[pos + 1]);
                int r = ModeSuperposition(pSrc[2], maskData[pos + 2]);
                pSrc[0] = ((alpha * b + nalpha * pSrc[0]) >> 7);
                pSrc[1] = ((alpha * g + nalpha * pSrc[1]) >> 7);
                pSrc[2] = ((alpha * r + nalpha * pSrc[2]) >> 7);
            }
            pSrc += 4;
        }
    }
    return ret;
}

int steroNose(const Texture& originTexture, const int srcFacePoints[202], const Texture& maskTexture, const int maskKeyPoints[2 * 3], int ratio)
{
    int srcKeyPoints[2 * 3] = { srcFacePoints[2 * 97], srcFacePoints[2 * 97 + 1], srcFacePoints[2 * 66], srcFacePoints[2 * 66 + 1], srcFacePoints[2 * 71], srcFacePoints[2 * 71 + 1] };
    return makeupBaseSteronose(originTexture, srcKeyPoints, maskTexture, maskKeyPoints, ratio);
}
