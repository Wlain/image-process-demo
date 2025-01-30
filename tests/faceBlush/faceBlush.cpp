//
// Created by william on 2025/1/30.
//

#include "faceBlush.h"

#include "makeupBase.h"

int faceBlush(const Texture& originTexture, const int srcFacePoints[202], const Texture& maskTexture, const int maskKeyPoints[2 * 3], bool isLeft, int ratio)
{
    if (isLeft)
    {
        int srcKeyPoints[2 * 3] = { srcFacePoints[2 * 1], srcFacePoints[2 * 1 + 1], srcFacePoints[2 * 6], srcFacePoints[2 * 6 + 1], srcFacePoints[2 * 64], srcFacePoints[2 * 64 + 1] };
        return makeupBase(originTexture, srcKeyPoints, maskTexture, maskKeyPoints, ratio);
    }
    else
    {
        int srcKeyPoints[2 * 3] = { srcFacePoints[2 * 17], srcFacePoints[2 * 17 + 1], srcFacePoints[2 * 12], srcFacePoints[2 * 12 + 1], srcFacePoints[2 * 73], srcFacePoints[2 * 73 + 1] };
        return makeupBase(originTexture, srcKeyPoints, maskTexture, maskKeyPoints, ratio);
    }
}