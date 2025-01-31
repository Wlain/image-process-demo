//
// Created by william on 2025/1/31.
//

#include "saturation.h"

int saturation(const Texture& originTexture, int saturation)
{
    auto& info = originTexture.getInfo();
    unsigned char* srcData = info.data;
    int width = info.width;
    int height = info.height;
    int stride = info.stride;
    
    int ret = 0;
	if(saturation == 0)
		return ret;
    unsigned char* pSrc = srcData;
	int r, g, b, rgbMin, rgbMax;
	saturation = std::clamp(saturation,-100,100);
	int k = saturation / 100.0f * 128;
	int alpha = 0;
	int offset = stride - width * 4;
	for(int j = 0; j < height; j++)
	{
		for(int i = 0; i < width; i++)
		{
			r = pSrc[2];
			g = pSrc[1];
			b = pSrc[0];
			rgbMin = std::min(std::min(r, g), b);
			rgbMax = std::max(std::max(r, g), b);
			int delta = (rgbMax - rgbMin);
			int value = (rgbMax + rgbMin);
			if(delta ==0)
			{
				pSrc += 4;
				continue;
			}			
			int L = value >> 1;
			int S = L < 128 ? (delta << 7) / value : (delta << 7) / (510 - value);
			if(k >= 0)
			{
				alpha = k + S >= 128 ? S : 128 - k;
				alpha = 128 * 128 / alpha - 128;
			}
			else
				alpha = k;
			r = r + ((r - L) * alpha >> 7);
			g = g + ((g - L) * alpha >> 7);
			b = b + ((b - L) * alpha >> 7);
			pSrc[0] = std::clamp(b, 0, 255);
			pSrc[1] = std::clamp(g, 0, 255);
			pSrc[2] = std::clamp(r, 0, 255);
			pSrc += 4;
		}
		pSrc += offset;
	}
	return ret;
}