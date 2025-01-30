//
// Created by william on 2025/1/30.
//

#include "hsvAdjust.h"
#include "rgb2hsv.h"
#include <iostream>

void hsvAdjust(const Texture& inputTexture, float hIntensity, float sIntensity, float vIntensity)
{
    auto& info = inputTexture.getInfo();
    auto& srcData = info.data;
    auto& stride = info.stride;
    auto& width = info.width;
    auto& height = info.height;

    int ret = 0;
    if(srcData == nullptr)
    {
        std::cout << "input image is null!" << std::endl;
        return;
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
            rgb2hsv(R, G, B, &h, &s, &v);
            h = h + hIntensity > 360 ? h + hIntensity - 360 : h + hIntensity;
            s = std::clamp(s + sIntensity, 0.0f, 1.0f);
            v = std::clamp(v + vIntensity, 0.0f, 1.0f);
            hsv2rgb(h, s, v, &R, &G, &B);
            pSrc[0] = R;
            pSrc[1] = G;
            pSrc[2] = B;
            pSrc += 4;
        }
        pSrc += offset;
    }
}

