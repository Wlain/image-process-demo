//
// Created by william on 2025/1/30.
//

#include "faceBlush.h"
#include "faceData.h"
#include "texture.h"

int main()
{
    const Texture maskLeft("mask_blush_left.png");
    int ratio = 50;
    Texture originTexture("test.png");
    faceBlush(originTexture, srcFacePoints, maskLeft, maskFaceBlushLeftKeyPoints, true, ratio);
    Texture maskRight("mask_blush_right.png");
    faceBlush(originTexture, srcFacePoints, maskRight, maskFaceBlushRightKeyPoints, false, ratio);
    originTexture.save("faceBlush.png");
    return 0;
}
