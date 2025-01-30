//
// Created by william on 2025/1/30.
//

#include "eyeBrow.h"
#include "makeupBase.h"

int eyeBrow(const Texture& originTexture, const int srcFacePoints[202], const Texture& maskTexture, const int maskKeyPoints[2 * 4], bool isLeft, int ratio)
{
    if (isLeft)
    {
        int srcKeyPoints[2 * 3] = { srcFacePoints[2 * 19], srcFacePoints[2 * 19 + 1], (srcFacePoints[2 * 22] + srcFacePoints[2 * 26]) / 2, (srcFacePoints[2 * 22 + 1] + srcFacePoints[2 * 26 + 1]) / 2, srcFacePoints[2 * 24], srcFacePoints[2 * 24 + 1] };
        return makeupBase(originTexture, srcKeyPoints, maskTexture, maskKeyPoints, ratio);
    }
    else
    {
        int srcKeyPoints[2 * 3] = { srcFacePoints[2 * 29], srcFacePoints[2 * 29 + 1], (srcFacePoints[2 * 31] + srcFacePoints[2 * 37]) / 2, (srcFacePoints[2 * 37 + 1] + srcFacePoints[2 * 31 + 1]) / 2, srcFacePoints[2 * 34], srcFacePoints[2 * 34 + 1] };
        return makeupBase(originTexture, srcKeyPoints, maskTexture, maskKeyPoints, ratio);
    }
}