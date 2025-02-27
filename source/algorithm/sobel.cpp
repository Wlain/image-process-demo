//
// Created by william on 2025/1/31.
//

#include "sobel.h"

int sobel(const Texture& originTexture, int threshold)
{
    auto& info = originTexture.getInfo();
    unsigned char* srcData = info.data;
    int width = info.width;
    int height = info.height;
    int stride = info.stride;
    int ret = 0;
    unsigned char* dstData = (unsigned char*)malloc(sizeof(unsigned char) * height * stride);
    memset(dstData, 255, sizeof(unsigned char) * height * stride);
    int x, y, i, k, pos;
    int hValue, vValue, value;
    unsigned char* pSrcL0;
    unsigned char* pSrcL1;
    unsigned char* pSrcL2;
    unsigned char* pDstL;
    unsigned char SqrtValue[65026];
    pSrcL0 = srcData;
    pSrcL1 = srcData + stride;
    pSrcL2 = srcData + stride * 2;
    pDstL = dstData + stride;
    for (i = 0; i < 65026; i++)
    {
        SqrtValue[i] = (unsigned char)(sqrt((float)i) < threshold ? 0 : 255);
    }
    for (y = 1; y < height - 1; y++)
    {
        for (x = 1; x < width - 1; x++)
        {
            pos = x * 4;
            hValue = (-pSrcL0[pos - 4] + pSrcL0[pos + 4] - 2 * pSrcL1[pos - 4] + 2 * pSrcL1[pos + 4] - pSrcL2[pos - 4] + pSrcL2[pos + 4]);
            vValue = (pSrcL0[pos - 4] + 2 * pSrcL0[pos] + pSrcL0[pos + 4] - pSrcL2[pos - 4] - 2 * pSrcL2[pos] - pSrcL2[pos + 4]);
            k = hValue * hValue + vValue * vValue;
            k = std::min(k, 65025);
            pDstL[pos] = SqrtValue[k];
            pos++;
            hValue = (-pSrcL0[pos - 4] + pSrcL0[pos + 4] - 2 * pSrcL1[pos - 4] + 2 * pSrcL1[pos + 4] - pSrcL2[pos - 4] + pSrcL2[pos + 4]);
            vValue = (pSrcL0[pos - 4] + 2 * pSrcL0[pos] + pSrcL0[pos + 4] - pSrcL2[pos - 4] - 2 * pSrcL2[pos] - pSrcL2[pos + 4]);
            k = hValue * hValue + vValue * vValue;
            k = std::min(k, 65025);
            pDstL[pos] = SqrtValue[k];
            pos++;
            hValue = (-pSrcL0[pos - 4] + pSrcL0[pos + 4] - 2 * pSrcL1[pos - 4] + 2 * pSrcL1[pos + 4] - pSrcL2[pos - 4] + pSrcL2[pos + 4]);
            vValue = (pSrcL0[pos - 4] + 2 * pSrcL0[pos] + pSrcL0[pos + 4] - pSrcL2[pos - 4] - 2 * pSrcL2[pos] - pSrcL2[pos + 4]);
            k = hValue * hValue + vValue * vValue;
            k = std::min(k, 65025);
            pDstL[pos] = SqrtValue[k];
        }
        pSrcL0 += stride;
        pSrcL1 += stride;
        pSrcL2 += stride;
        pDstL += stride;
    }
    memcpy(srcData, dstData, sizeof(unsigned char) * height * stride);
    free(dstData);
    return ret;
}

int findEdges(const Texture& originTexture)
{
    auto& info = originTexture.getInfo();
    unsigned char* srcData = info.data;
    int width = info.width;
    int height = info.height;
    int stride = info.stride;
    int ret = 0;
    unsigned char* dstData = (unsigned char*)malloc(sizeof(unsigned char) * height * stride);
    memset(dstData, 255, sizeof(unsigned char) * height * stride);
    int x, y, i, k, pos;
    int hValue, vValue, value;
    unsigned char* pSrcL0;
    unsigned char* pSrcL1;
    unsigned char* pSrcL2;
    unsigned char* pDstL;
    unsigned char SqrtValue[65026];
    pSrcL0 = srcData;
    pSrcL1 = srcData + stride;
    pSrcL2 = srcData + stride * 2;
    pDstL = dstData + stride;
    for (i = 0; i < 65026; i++)
    {
        SqrtValue[i] = (unsigned char)(255 - (int)sqrt((float)i));
    }
    for (y = 1; y < height - 1; y++)
    {
        for (x = 1; x < width - 1; x++)
        {
            pos = x * 4;
            hValue = (-pSrcL0[pos - 4] + pSrcL0[pos + 4] - 2 * pSrcL1[pos - 4] + 2 * pSrcL1[pos + 4] - pSrcL2[pos - 3] + pSrcL2[pos + 4]);
            vValue = (pSrcL0[pos - 4] + 2 * pSrcL0[pos] + pSrcL0[pos + 4] - pSrcL2[pos - 4] - 2 * pSrcL2[pos] - pSrcL2[pos + 4]);
            k = hValue * hValue + vValue * vValue;
            k = std::min(k, 65025);
            pDstL[pos] = SqrtValue[k];
            pos++;
            hValue = (-pSrcL0[pos - 4] + pSrcL0[pos + 4] - 2 * pSrcL1[pos - 4] + 2 * pSrcL1[pos + 4] - pSrcL2[pos - 4] + pSrcL2[pos + 4]);
            vValue = (pSrcL0[pos - 4] + 2 * pSrcL0[pos] + pSrcL0[pos + 4] - pSrcL2[pos - 4] - 2 * pSrcL2[pos] - pSrcL2[pos + 4]);
            k = hValue * hValue + vValue * vValue;
            k = std::min(k, 65025);
            pDstL[pos] = SqrtValue[k];
            pos++;
            hValue = (-pSrcL0[pos - 4] + pSrcL0[pos + 4] - 2 * pSrcL1[pos - 4] + 2 * pSrcL1[pos + 4] - pSrcL2[pos - 4] + pSrcL2[pos + 4]);
            vValue = (pSrcL0[pos - 4] + 2 * pSrcL0[pos] + pSrcL0[pos + 4] - pSrcL2[pos - 4] - 2 * pSrcL2[pos] - pSrcL2[pos + 4]);
            k = hValue * hValue + vValue * vValue;
            k = std::min(k, 65025);
            pDstL[pos] = SqrtValue[k];
        }
        pSrcL0 += stride;
        pSrcL1 += stride;
        pSrcL2 += stride;
        pDstL += stride;
    }
    memcpy(srcData, dstData, sizeof(unsigned char) * height * stride);
    free(dstData);
    return ret;
}
