//
// Created by william on 2025/1/30.
//

#include "faceData.h"
#include "texture.h"
#include "eyeShadow.h"

int main()
{
    Texture originTexture("test.png");
    Texture maskLeft("shadow_l_mask.png");
    Texture maskLeft2("shadow_l_mask2.png");
    int ratio = 100;
    eyeShadow(originTexture, srcFacePoints, maskLeft, maskEyeShadowLeftKeyPoints,true, 1, ratio);
    eyeShadow(originTexture, srcFacePoints, maskLeft2, maskEyeShadowLeftKeyPoints, true, 0, ratio);
    Texture maskRight("shadow_r_mask.png");
    Texture maskRight2("shadow_r_mask2.png");
    eyeShadow(originTexture, srcFacePoints, maskRight, maskEyeShadowRightKeyPoints,false, 1, ratio);
    eyeShadow(originTexture, srcFacePoints, maskRight2, maskEyeShadowRightKeyPoints, false, 0, ratio);
    originTexture.save("eyeShadow.png");
    return 0;
}
