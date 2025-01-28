//
// Created by william on 2025/1/28.
//

#include "RGB2HSV.h"
#include <algorithm>

void RGB2HSV(unsigned char R, unsigned char G, unsigned char B, float* h, float* s, float * v)
{
    float min, max;
    float r = R / 255.0;
    float g = G / 255.0;
    float b = B / 255.0;
    min = std::min(r,std::min(g,b));
    max = std::max(r,std::max(g,b));
    if (max == min)
        *h = 0;
    else if (max == r && g >= b)
        *h = 60.0 * (g - b) / (max - min);
    else if (max == r && g < b)
        *h = 60.0 * (g - b) / (max - min) + 360.0;
    else if (max == g)
        *h = 60.0 * (b - r) / (max - min) + 120.0;
    else if (max == b)
        *h = 60.0 * (r - g) / (max - min) + 240.0;
    *h = std::clamp(*h, 0.0f, 360.0f);
    if (max == 0)
        *s = 0;
    else
        *s = (max - min) / max;
    *v = max;
};
void HSV2RGB(float h, float s, float v, unsigned char* R, unsigned char *G, unsigned char *B)
{
    float q = 0, p = 0, t = 0, f = 0, r = 0, g = 0, b = 0;
    int hN = 0;
    if(h == 360)
        h = 0;
    if (h < 0)
        h = 360 + h;
    hN = (int)((int)h / 60);
    f = h / 60.0f - hN;
    p = v * (1.0 - s);
    q = v * (1.0 - f * s);
    t = v * (1.0 - (1.0 - f) * s);
    switch (hN)
    {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
        r = v;
        g = p;
        b = q;
        break;
    default:
        break;
    }
    *R = (unsigned char)std::clamp((r * 255.0f),0.0f,255.0f);
    *G = (unsigned char)std::clamp((g * 255.0f),0.0f,255.0f);
    *B = (unsigned char)std::clamp((b * 255.0f),0.0f,255.0f);
}