//
// Created by william on 2025/1/28.
//

#include "texture.h"
#include "RGB2HSV.h"
#include <iostream>

int HSVAdjust(unsigned char *srcData, int width, int height, int stride, float hIntensity, float sIntensity, float vIntensity)
{
    int ret = 0;
    if(srcData == nullptr)
    {
        printf("input image is null!");
        return -1;
    }
    //Process
    unsigned char R, G, B;
    float h = 0, s = 0, v = 0;
    unsigned char* pSrc = srcData;
    int offset = stride - width * 4;
    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            R = pSrc[0];
            G = pSrc[1];
            B = pSrc[2];
            RGB2HSV(R, G, B, &h, &s, &v);
            h = h + hIntensity > 360 ? h + hIntensity - 360 : h + hIntensity;
            s = std::clamp(s + sIntensity, 0.0f, 1.0f);
            v = std::clamp(v + vIntensity, 0.0f, 1.0f);
            HSV2RGB(h, s, v, &R, &G, &B);
            pSrc[0] = R;
            pSrc[1] = G;
            pSrc[2] = B;
            pSrc += 4;
        }
        pSrc += offset;
    }
    return ret;
};

int main()
{
    Texture dog("dog.png");
    auto& info = dog.getInfo();
    int result = HSVAdjust(info.data, info.width, info.height, info.stride, 180.0, 0.1, 0.1);
    dog.save("dog_hsv.png");
    return 0;
}
