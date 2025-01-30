//
// Created by william on 2025/1/30.
//

#include "eyeLash.h"

#include "makeupBase.h"

int eyeLash(const Texture& originTexture, const int srcFacePoints[202], const Texture& maskTexture, const int maskKeyPoints[2 * 3], bool isLeft, int ratio)
{
    if (isLeft)
    {
        int srcKeyPoints[2 * 3] = { srcFacePoints[2 * 39], srcFacePoints[2 * 39 + 1], srcFacePoints[2 * 42], srcFacePoints[2 * 42 + 1], srcFacePoints[2 * 45], srcFacePoints[2 * 45 + 1] };
        return makeupBase(originTexture, srcKeyPoints, maskTexture, maskKeyPoints, ratio);
    }
    else
    {
        int srcKeyPoints[2 * 3] = { srcFacePoints[2 * 51], srcFacePoints[2 * 51 + 1], srcFacePoints[2 * 54], srcFacePoints[2 * 54 + 1], srcFacePoints[2 * 57], srcFacePoints[2 * 57 + 1] };
        return makeupBase(originTexture, srcKeyPoints, maskTexture, maskKeyPoints, ratio);
    }
}