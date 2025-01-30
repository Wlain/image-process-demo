//
// Created by william on 2025/1/30.
//

#include "makeupBase.h"
#include "algorithm"
#include "affineTransfrom.h"

// Makeup base with bilinear interpolation
int makeupBase(const Texture& originTexture, const int srcKeyPoints[2 * 3], const Texture& maskTexture, const int maskKeyPoints[2 * 3], int ratio)
{
    auto originInfo = originTexture.getInfo();
    unsigned char* srcData = originInfo.data;
    int width = originInfo.width;
    int height = originInfo.height;
    int stride = originInfo.stride;
    auto maskInfo = maskTexture.getInfo();
    unsigned char* mskData = maskInfo.data;
    int mWidth = maskInfo.width;
    int mHeight = maskInfo.height;
    int mStride = maskInfo.stride;

    int ret = 0;
    float H[6] = {0};
    affinetransformMetrixCompute((float)maskKeyPoints[0],(float)maskKeyPoints[1],(float)maskKeyPoints[2],(float)maskKeyPoints[3],(float)maskKeyPoints[4],(float)maskKeyPoints[5], (float)srcKeyPoints[0], (float)srcKeyPoints[1], (float)srcKeyPoints[2], (float)srcKeyPoints[3], (float)srcKeyPoints[4], (float)srcKeyPoints[5], H);
    unsigned char* pSrc = srcData;
    int alpha = 128 * ratio / 100;
    int nalpha = 128 - alpha;
    int AR, AG, AB, AA;
    int x0, y0, index_x0y0, index_x0y1, index_x1y0, index_x1y1;
    int disX, disY, tmp1, tmp2;
    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            float cx = (H[0] * i + H[1] * j + H[2]);
            float cy = (H[3] * i + H[4] * j + H[5]);
            if(cx > 0 && cx < mWidth - 1 && cy > 0 && cy < mHeight - 1)
            {

                x0 = (int)std::clamp(floor(cx), 0.0f, mWidth - 2.0f);
                y0 = (int)std::clamp(floor(cy), 0.0f, mHeight - 2.0f);
                index_x0y0 = (x0 << 2) + y0 * mStride;
                index_x1y0 = index_x0y0 + 4;
                index_x0y1 = index_x0y0 + mStride;
                index_x1y1 = index_x0y1 + 4;
                disX = (int)((cx - x0) * 16384);
                disY = (int)((cy - y0) * 16384);	
                tmp1 = mskData[index_x0y0] + ((disX *(mskData[index_x1y0] - mskData[index_x0y0])) >> 14);
                tmp2 = mskData[index_x0y1] + ((disX *(mskData[index_x1y1] - mskData[index_x0y1])) >> 14);
                AB = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                tmp1 = mskData[index_x0y0 + 1] + ((disX *(mskData[index_x1y0 + 1] - mskData[index_x0y0 + 1])) >> 14);
                tmp2 = mskData[index_x0y1 + 1] + ((disX *(mskData[index_x1y1 + 1] - mskData[index_x0y1 + 1])) >> 14);
                AG = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                tmp1 = mskData[index_x0y0 + 2] + ((disX *(mskData[index_x1y0 + 2] - mskData[index_x0y0 + 2])) >> 14);
                tmp2 = mskData[index_x0y1 + 2] + ((disX *(mskData[index_x1y1 + 2] - mskData[index_x0y1 + 2])) >> 14);
                AR = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                tmp1 = mskData[index_x0y0 + 3] + ((disX *(mskData[index_x1y0 + 3] - mskData[index_x0y0 + 3])) >> 14);
                tmp2 = mskData[index_x0y1 + 3] + ((disX *(mskData[index_x1y1 + 3] - mskData[index_x0y1 + 3])) >> 14);
                AA = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);

                int pos = (x0 << 2) + y0 * mStride;
                int k = AA;
                int b = (k * AB     + (255 - k) * pSrc[0]) / 255;
                int g = (k * AG + (255 - k) * pSrc[1]) / 255;
                int r = (k * AR + (255 - k) * pSrc[2]) / 255;
                pSrc[0] = ((alpha * b + nalpha * pSrc[0]) >> 7);
                pSrc[1] = ((alpha * g + nalpha * pSrc[1]) >> 7);
                pSrc[2] = ((alpha * r + nalpha * pSrc[2]) >> 7);
            }
            pSrc += 4;
        }
    }
    return ret;
}