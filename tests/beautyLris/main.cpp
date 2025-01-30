//
// Created by william on 2025/1/28.
//

#include "beautyIris.h"
#include "texture.h"
#include "faceData.h"

int main()
{
    Texture originTexture("test.png");
    Texture mask("lris.png");
    auto& maskInfo = mask.getInfo();
    const int maskPoints[] = {maskInfo.width / 2, maskInfo.height / 2 };
    int ratio = 100;
    beautyIris(originTexture, maskBeautyLrisLeftKeyPoints, mask, maskPoints, ratio);
    beautyIris(originTexture, maskBeautyLrisRightKeyPoints, mask, maskPoints, ratio);
    originTexture.save("beautyIris.png");
    return 0;
}
