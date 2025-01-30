//
// Created by william on 2025/1/28.
//

#include "beautyIris.h"
#include "texture.h"

int main()
{
    int srcPoints[] = { 88, 214, 118, 193, 153, 182, 193, 179, 232,191,267,217,297,247,261,260,222,268,180,268,137,259,107,240,191,207};
    Texture originTexture("5-4-0.bmp");
    Texture mask("5-5-0.png");
    auto& maskInfo = mask.getInfo();
    int maskPoints[] = {maskInfo.width / 2, maskInfo.height / 2 };
    int ratio = 20;
    auto ret = beautyIris(originTexture, srcPoints, mask, maskPoints, ratio);
    originTexture.save("beautyIris.png");
    return 0;
}
