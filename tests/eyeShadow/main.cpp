//
// Created by william on 2025/1/30.
//

#include "eyeBrow.h"
#include "eyeLash.h"
#include "eyeLid.h"
#include "eyeLine.h"
#include "eyeShadow.h"
#include "faceData.h"
#include "steroNose.h"
#include "lipsRecolor.h"

int main()
{
    Texture originTexture("test.png");
    Texture shadowMaskLeft("shadow_l_mask.png");
    Texture shadowMaskLeft2("shadow_l_mask2.png");
    int ratio = 100;
    // 眼影
    eyeShadow(originTexture, srcFacePoints, shadowMaskLeft, maskEyeShadowLeftKeyPoints, true, 1, ratio);
    eyeShadow(originTexture, srcFacePoints, shadowMaskLeft2, maskEyeShadowLeftKeyPoints, true, 0, ratio);
    Texture shadowMaskRight("shadow_r_mask.png");
    Texture shadowMaskRight2("shadow_r_mask2.png");
    eyeShadow(originTexture, srcFacePoints, shadowMaskRight, maskEyeShadowRightKeyPoints, false, 1, ratio);
    eyeShadow(originTexture, srcFacePoints, shadowMaskRight2, maskEyeShadowRightKeyPoints, false, 0, ratio);
    // 眼线
    Texture eyeLineMaskLeft("eyeline_l_mask.png");
    Texture eyeLineMaskRight("eyeline_r_mask.png");
    eyeLine(originTexture, srcFacePoints, eyeLineMaskLeft, maskEyeShadowLeftKeyPoints, true, ratio);
    eyeLine(originTexture, srcFacePoints, eyeLineMaskRight, maskEyeShadowRightKeyPoints, false, ratio);
    // 眼睫毛
    Texture eyeLashMaskLeft("eyelash_l_mask.png");
    Texture eyeLashMaskRight("eyelash_r_mask.png");
    eyeLash(originTexture, srcFacePoints, eyeLashMaskLeft, maskEyeShadowLeftKeyPoints, true, ratio);
    eyeLash(originTexture, srcFacePoints, eyeLashMaskRight, maskEyeShadowRightKeyPoints, false, ratio);
    // 双眼皮
    Texture eyeLidMaskLeft("eyelid_l_mask.png");
    Texture eyeLidMaskRight("eyelid_r_mask.png");
    eyeLid(originTexture, srcFacePoints, eyeLidMaskLeft, maskEyeShadowLeftKeyPoints, true, ratio);
    eyeLid(originTexture, srcFacePoints, eyeLidMaskRight, maskEyeShadowRightKeyPoints, false, ratio);
    // 眉毛
    Texture eyebrowMask("eyebrow_l_mask.png");
    Texture eyebrowMask2("eyebrow_r_mask.png");
    eyeBrow(originTexture, srcFacePoints, eyebrowMask, maskEyeBrowLeftKeyPoints, true, ratio);
    eyeBrow(originTexture, srcFacePoints, eyebrowMask2, maskEyeBrowRightKeyPoints, false, ratio);
    // 修鼻
    Texture steroNoseMask("steronose_mask.png");
    steroNose(originTexture, srcFacePoints, steroNoseMask, maskSteroNoseKeyPoints, ratio);
    // 唇彩
    Texture lipsMask("lips_mask.png");
    Texture lipsLut("lipsLut.png");
    lipsRecolor(originTexture, srcFacePoints, lipsMask, maskLipKeyPoints, lipsLut, ratio);
    originTexture.save("eyeShadow.png");
    return 0;
}
