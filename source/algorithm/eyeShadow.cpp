//
// Created by william on 2025/1/30.
//

#include "eyeShadow.h"

#include "makeupBase.h"

#include <texture.h>

int eyeShadow(const Texture& originTexture, const int srcFacePoints[202], const Texture& maskTexture, const int maskKeyPoints[2 * 2], bool isLeft, int mode, int ratio)
{
    if (isLeft)
    {
        int srcKeyPoints[2 * 4] = { srcFacePoints[2 * 39], srcFacePoints[2 * 39 + 1], srcFacePoints[2 * 42], srcFacePoints[2 * 42 + 1], srcFacePoints[2 * 45], srcFacePoints[2 * 45 + 1], srcFacePoints[2 * 48], srcFacePoints[2 * 48 + 1] };
        return makeupBaseShadow(originTexture, srcKeyPoints, maskTexture, maskKeyPoints, mode, ratio);
    }
    else
    {
        int srcKeyPoints[2 * 4] = { srcFacePoints[2 * 51], srcFacePoints[2 * 51 + 1], srcFacePoints[2 * 54], srcFacePoints[2 * 54 + 1], srcFacePoints[2 * 57], srcFacePoints[2 * 57 + 1], srcFacePoints[2 * 60], srcFacePoints[2 * 60 + 1] };
        return makeupBaseShadow(originTexture, srcKeyPoints, maskTexture, maskKeyPoints, mode, ratio);
    }
}