//
// Created by william on 2025/1/30.
//

#include "faceBlush.h"
#include "faceData.h"
#include "texture.h"

int main()
{
    Texture maskLeft("mask_blush_left.png");
    int ratio = 50;
    Texture originTexture("test.png");
    auto ret = faceBlush(originTexture, srcFacePoints, maskLeft, maskLeftKeyPointsleft, true, ratio);
    Texture maskRight("mask_blush_right.png");
    ret = faceBlush(originTexture, srcFacePoints, maskRight, maskLeftKeyPointsright, false, ratio);
    originTexture.save("test_blush.png");
    return 0;
}
