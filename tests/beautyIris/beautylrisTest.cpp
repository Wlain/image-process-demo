//
// Created by william on 2025/1/28.
//

#include "beautyIris.h"
#include "texture.h"

int main()
{
    int srcPoints[] = { 88, 214, 118, 193, 153, 182, 193, 179, 232,191,267,217,297,247,261,260,222,268,180,268,137,259,107,240,191,207};
    Texture mask("5-5-0.png");
    Texture origin("5-4-0.bmp");
    auto& maskInfo = mask.getInfo();
    int maskPoints[] = {maskInfo.width / 2, maskInfo.height / 2 };
    int ratio = 100;
    auto& textureInfo = origin.getInfo();
    auto ret = beautyIris(textureInfo.data, textureInfo.width, textureInfo.height,textureInfo.stride, srcPoints, maskInfo.data, maskInfo.width, maskInfo.height, maskInfo.stride, maskPoints, ratio);
    origin.save("beautyIris.png");
    return 0;
}
