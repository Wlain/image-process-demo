//
// Created by william on 2025/1/28.
//

#include "rgb2hsv.h"
#include <algorithm>

void rgb2hsv(unsigned char R, unsigned char G, unsigned char B, float* h, float* s, float * v)
{
    float r = R / 255.0f;
    float g = G / 255.0f;
    float b = B / 255.0f;
    float min = std::min(r,std::min(g,b));
    float max = std::max(r,std::max(g,b));
    if (max == min)
        *h = 0.0f;
    else if (max == r && g >= b)
        *h = 60.0f * (g - b) / (max - min);
    else if (max == r && g < b)
        *h = 60.0f * (g - b) / (max - min) + 360.0f;
    else if (max == g)
        *h = 60.0f * (b - r) / (max - min) + 120.0f;
    else if (max == b)
        *h = 60.0f * (r - g) / (max - min) + 240.0f;
    *h = std::clamp(*h, 0.0f, 360.0f);
    if (max == 0)
        *s = 0;
    else
        *s = (max - min) / max;
    *v = max;
};
void hsv2rgb(float h, float s, float v, unsigned char* R, unsigned char *G, unsigned char *B)
{
    int hN = 0;
    if(h == 360)
        h = 0;
    if (h < 0)
        h = 360 + h;
    hN = (int)((int)h / 60);
    float f = h / 60.0f - hN;
    float p = v * (1.0 - s);
    float q = v * (1.0 - f * s);
    float t = v * (1.0 - (1.0 - f) * s);
    float r = 0, g = 0, b = 0;
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
    *R = static_cast<unsigned char>(std::clamp((r * 255.0f), 0.0f, 255.0f));
    *G = static_cast<unsigned char>(std::clamp((g * 255.0f), 0.0f, 255.0f));
    *B = static_cast<unsigned char>(std::clamp((b * 255.0f), 0.0f, 255.0f));
}