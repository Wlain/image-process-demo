//
// Created by william on 2025/1/30.
//

#include "makeupBase.h"

#include "affineTransfrom.h"

#include <algorithm>

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
    float H[6] = { 0 };
    affinetransformMetrixCompute((float)maskKeyPoints[0], (float)maskKeyPoints[1], (float)maskKeyPoints[2], (float)maskKeyPoints[3], (float)maskKeyPoints[4], (float)maskKeyPoints[5], (float)srcKeyPoints[0], (float)srcKeyPoints[1], (float)srcKeyPoints[2], (float)srcKeyPoints[3], (float)srcKeyPoints[4], (float)srcKeyPoints[5], H);
    unsigned char* pSrc = srcData;
    int alpha = 128 * ratio / 100;
    int nalpha = 128 - alpha;
    int AR, AG, AB, AA;
    int x0, y0, index_x0y0, index_x0y1, index_x1y0, index_x1y1;
    int disX, disY, tmp1, tmp2;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            float cx = (H[0] * i + H[1] * j + H[2]);
            float cy = (H[3] * i + H[4] * j + H[5]);
            if (cx > 0 && cx < mWidth - 1 && cy > 0 && cy < mHeight - 1)
            {
                x0 = (int)std::clamp(floor(cx), 0.0f, mWidth - 2.0f);
                y0 = (int)std::clamp(floor(cy), 0.0f, mHeight - 2.0f);
                index_x0y0 = (x0 << 2) + y0 * mStride;
                index_x1y0 = index_x0y0 + 4;
                index_x0y1 = index_x0y0 + mStride;
                index_x1y1 = index_x0y1 + 4;
                disX = (int)((cx - x0) * 16384);
                disY = (int)((cy - y0) * 16384);
                tmp1 = mskData[index_x0y0] + ((disX * (mskData[index_x1y0] - mskData[index_x0y0])) >> 14);
                tmp2 = mskData[index_x0y1] + ((disX * (mskData[index_x1y1] - mskData[index_x0y1])) >> 14);
                AB = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                tmp1 = mskData[index_x0y0 + 1] + ((disX * (mskData[index_x1y0 + 1] - mskData[index_x0y0 + 1])) >> 14);
                tmp2 = mskData[index_x0y1 + 1] + ((disX * (mskData[index_x1y1 + 1] - mskData[index_x0y1 + 1])) >> 14);
                AG = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                tmp1 = mskData[index_x0y0 + 2] + ((disX * (mskData[index_x1y0 + 2] - mskData[index_x0y0 + 2])) >> 14);
                tmp2 = mskData[index_x0y1 + 2] + ((disX * (mskData[index_x1y1 + 2] - mskData[index_x0y1 + 2])) >> 14);
                AR = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                tmp1 = mskData[index_x0y0 + 3] + ((disX * (mskData[index_x1y0 + 3] - mskData[index_x0y0 + 3])) >> 14);
                tmp2 = mskData[index_x0y1 + 3] + ((disX * (mskData[index_x1y1 + 3] - mskData[index_x0y1 + 3])) >> 14);
                AA = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);

                int pos = (x0 << 2) + y0 * mStride;
                int k = AA;
                int b = (k * AB + (255 - k) * pSrc[0]) / 255;
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

inline int modeSmoothLight(int basePixel, int mixPixel)
{
    int res = 0;
    res = mixPixel > 128 ? ((int)((float)basePixel + ((float)mixPixel + (float)mixPixel - 255.0f) * ((sqrt((float)basePixel / 255.0f)) * 255.0f - (float)basePixel) / 255.0f)) :
                           ((int)((float)basePixel + ((float)mixPixel + (float)mixPixel - 255.0f) * ((float)basePixel - (float)basePixel * (float)basePixel / 255.0f) / 255.0f));
    return std::clamp(res, 0, 255);
}

inline bool isBelowLine(int inputPoint[4], float x, float y)
{
    int x1 = inputPoint[0];
    int y1 = inputPoint[1];
    int x2 = inputPoint[2];
    int y2 = inputPoint[3];
    float val = (x2 - x1) * (y - y1) - (x - x1) * (y2 - y1);
    return (val > 0);
}

int makeupBaseShadow(const Texture& originTexture, int srcKeyPoints[2 * 4], const Texture& maskTexture, const int maskKeyPoints[2 * 4], int mode, int ratio)
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
    float HU[6] = { 0 }, HD[6] = { 0 };
    affinetransformMetrixCompute((float)maskKeyPoints[0], (float)maskKeyPoints[1], (float)maskKeyPoints[2], (float)maskKeyPoints[3], (float)maskKeyPoints[4], (float)maskKeyPoints[5], (float)srcKeyPoints[0], (float)srcKeyPoints[1], (float)srcKeyPoints[2], (float)srcKeyPoints[3], (float)srcKeyPoints[4], (float)srcKeyPoints[5], HU);
    affinetransformMetrixCompute((float)maskKeyPoints[0], (float)maskKeyPoints[1], (float)maskKeyPoints[6], (float)maskKeyPoints[7], (float)maskKeyPoints[4], (float)maskKeyPoints[5], (float)srcKeyPoints[0], (float)srcKeyPoints[1], (float)srcKeyPoints[6], (float)srcKeyPoints[7], (float)srcKeyPoints[4], (float)srcKeyPoints[5], HD);
    unsigned char* pSrc = srcData;
    int alpha = 128 * ratio / 100;
    int nalpha = 128 - alpha;
    int Line[4] = { srcKeyPoints[0], srcKeyPoints[1], srcKeyPoints[4], srcKeyPoints[5] };
    int AR, AG, AB, AA;
    int x0, y0, index_x0y0, index_x0y1, index_x1y0, index_x1y1;
    int disX, disY, tmp1, tmp2;
    if (mode == 0)
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                bool belowLined = isBelowLine(Line, i, j);
                float cx = 0, cy = 0;
                if (!belowLined)
                {
                    cx = (HU[0] * i + HU[1] * j + HU[2]);
                    cy = (HU[3] * i + HU[4] * j + HU[5]);
                }
                else
                {
                    cx = (HD[0] * i + HD[1] * j + HD[2]);
                    cy = (HD[3] * i + HD[4] * j + HD[5]);
                }
                if (cx > 0 && cy < mWidth - 1 && cx > 0 && cy < mHeight - 1)
                {
                    x0 = (int)std::clamp(floor(cx), 0.0f, mWidth - 2.0f);
                    y0 = (int)std::clamp(floor(cy), 0.0f, mHeight - 2.0f);
                    index_x0y0 = (x0 << 2) + y0 * mStride;
                    index_x1y0 = index_x0y0 + 4;
                    index_x0y1 = index_x0y0 + mStride;
                    index_x1y1 = index_x0y1 + 4;
                    disX = (int)((cx - x0) * 16384);
                    disY = (int)((cy - y0) * 16384);
                    tmp1 = mskData[index_x0y0] + ((disX * (mskData[index_x1y0] - mskData[index_x0y0])) >> 14);
                    tmp2 = mskData[index_x0y1] + ((disX * (mskData[index_x1y1] - mskData[index_x0y1])) >> 14);
                    AB = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                    tmp1 = mskData[index_x0y0 + 1] + ((disX * (mskData[index_x1y0 + 1] - mskData[index_x0y0 + 1])) >> 14);
                    tmp2 = mskData[index_x0y1 + 1] + ((disX * (mskData[index_x1y1 + 1] - mskData[index_x0y1 + 1])) >> 14);
                    AG = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                    tmp1 = mskData[index_x0y0 + 2] + ((disX * (mskData[index_x1y0 + 2] - mskData[index_x0y0 + 2])) >> 14);
                    tmp2 = mskData[index_x0y1 + 2] + ((disX * (mskData[index_x1y1 + 2] - mskData[index_x0y1 + 2])) >> 14);
                    AR = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                    tmp1 = mskData[index_x0y0 + 3] + ((disX * (mskData[index_x1y0 + 3] - mskData[index_x0y0 + 3])) >> 14);
                    tmp2 = mskData[index_x0y1 + 3] + ((disX * (mskData[index_x1y1 + 3] - mskData[index_x0y1 + 3])) >> 14);
                    AA = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                    if (AA != 0)
                    {
                        int mb = AB;
                        int mg = AG;
                        int mr = AR;
                        mb = (mb * AA + pSrc[0] * (255 - AA)) / 255;
                        mg = (mg * AA + pSrc[1] * (255 - AA)) / 255;
                        mr = (mr * AA + pSrc[2] * (255 - AA)) / 255;
                        pSrc[0] = (pSrc[0] * (100 - ratio) + mb * ratio) / 100;
                        pSrc[1] = (pSrc[1] * (100 - ratio) + mg * ratio) / 100;
                        pSrc[2] = (pSrc[2] * (100 - ratio) + mr * ratio) / 100;
                    }
                }
                pSrc += 4;
            }
        }
    }
    else
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                bool belowLined = isBelowLine(Line, i, j);
                float cx = 0, cy = 0;
                if (!belowLined)
                {
                    cx = (HU[0] * i + HU[1] * j + HU[2]);
                    cy = (HU[3] * i + HU[4] * j + HU[5]);
                }
                else
                {
                    cx = (HD[0] * i + HD[1] * j + HD[2]);
                    cy = (HD[3] * i + HD[4] * j + HD[5]);
                }
                if (cx > 0 && cx < mWidth - 1 && cy > 0 && cy < mHeight - 1)
                {
                    x0 = (int)std::clamp(floor(cx), 0.0f, mWidth - 2.0f);
                    y0 = (int)std::clamp(floor(cy), 0.0f, mHeight - 2.0f);
                    index_x0y0 = (x0 << 2) + y0 * mStride;
                    index_x1y0 = index_x0y0 + 4;
                    index_x0y1 = index_x0y0 + mStride;
                    index_x1y1 = index_x0y1 + 4;
                    disX = (int)((cx - x0) * 16384);
                    disY = (int)((cy - y0) * 16384);
                    tmp1 = mskData[index_x0y0] + ((disX * (mskData[index_x1y0] - mskData[index_x0y0])) >> 14);
                    tmp2 = mskData[index_x0y1] + ((disX * (mskData[index_x1y1] - mskData[index_x0y1])) >> 14);
                    AB = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                    tmp1 = mskData[index_x0y0 + 1] + ((disX * (mskData[index_x1y0 + 1] - mskData[index_x0y0 + 1])) >> 14);
                    tmp2 = mskData[index_x0y1 + 1] + ((disX * (mskData[index_x1y1 + 1] - mskData[index_x0y1 + 1])) >> 14);
                    AG = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                    tmp1 = mskData[index_x0y0 + 2] + ((disX * (mskData[index_x1y0 + 2] - mskData[index_x0y0 + 2])) >> 14);
                    tmp2 = mskData[index_x0y1 + 2] + ((disX * (mskData[index_x1y1 + 2] - mskData[index_x0y1 + 2])) >> 14);
                    AR = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                    tmp1 = mskData[index_x0y0 + 3] + ((disX * (mskData[index_x1y0 + 3] - mskData[index_x0y0 + 3])) >> 14);
                    tmp2 = mskData[index_x0y1 + 3] + ((disX * (mskData[index_x1y1 + 3] - mskData[index_x0y1 + 3])) >> 14);
                    AA = tmp1 + ((disY * (tmp2 - tmp1)) >> 14);
                    if (AA != 0)
                    {
                        int mb = AB;
                        int mg = AG;
                        int mr = AR;
                        int b = modeSmoothLight(pSrc[0], mb);
                        int g = modeSmoothLight(pSrc[1], mg);
                        int r = modeSmoothLight(pSrc[2], mr);
                        b = (b * AA + pSrc[0] * (255 - AA)) / 255;
                        g = (g * AA + pSrc[1] * (255 - AA)) / 255;
                        r = (r * AA + pSrc[2] * (255 - AA)) / 255;
                        pSrc[0] = (pSrc[0] * (100 - ratio) + b * ratio) / 100;
                        pSrc[1] = (pSrc[1] * (100 - ratio) + g * ratio) / 100;
                        pSrc[2] = (pSrc[2] * (100 - ratio) + r * ratio) / 100;
                    }
                }
                pSrc += 4;
            }
        }
    }
    return ret;
}