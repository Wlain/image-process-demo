//
// Created by william on 2025/1/31.
//

#include "usm.h"
#include "gaussFilter.h"

int usm(const Texture& originTexture ,int radius, int amount, int threshold)
{
    auto& info = originTexture.getInfo();
    unsigned char* srcData = info.data;
    int width = info.width;
    int height = info.height;
    int stride = info.stride;
    
    int ret = 0;
    if(radius == 0)
		return ret;
	radius = std::clamp(radius, 0, 100);
	amount = std::clamp(amount, 0,500);
	threshold = std::clamp(threshold, 0,255);
	unsigned char* gaussData = (unsigned char*)malloc(sizeof(unsigned char) * height * stride);
	memcpy(gaussData, srcData, sizeof(unsigned char) * height * stride);
	fastGaussFilter(gaussData, width, height, stride, radius);
	int i, j, r, g, b, offset;
	offset = stride - width * 4;
	amount = amount * 128 / 100;
	unsigned char* pSrc = srcData;
	unsigned char* pDst = gaussData;
	unsigned char* maskData = (unsigned char*)malloc(sizeof(unsigned char) * height * stride);
	unsigned char* pMask = maskData;
	for(j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			pMask[0] = abs(pSrc[0] - pDst[0]) < threshold ? 0 : 128;
			pMask[1] = abs(pSrc[1] - pDst[1]) < threshold ? 0 : 128;
			pMask[2] = abs(pSrc[2] - pDst[2]) < threshold ? 0 : 128;
			pDst += 4;
			pSrc += 4;
			pMask += 4;
		}
		pDst += offset;
		pSrc += offset;
		pMask += offset;
	}
	pDst = gaussData;
	pSrc = srcData;
	pMask = maskData;
	fastGaussFilter(maskData, width, height, stride, radius);
	for(j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			b = pSrc[0] - pDst[0];
			g = pSrc[1] - pDst[1];
			r = pSrc[2] - pDst[2];

			b = (pSrc[0] + ((b * amount) >> 7));
			g = (pSrc[1] + ((g * amount) >> 7));
			r = (pSrc[2] + ((r * amount) >> 7));
			
			b = (b * pMask[0] + pSrc[0] * (128 - pMask[0])) >> 7;
			g = (g * pMask[1] + pSrc[1] * (128 - pMask[1])) >> 7;
			r = (r * pMask[2] + pSrc[2] * (128 - pMask[2])) >> 7;

			pSrc[0] = std::clamp(b, 0, 255);
			pSrc[1] = std::clamp(g, 0, 255);
			pSrc[2] = std::clamp(r, 0, 255);
			pSrc += 4;
			pDst += 4;
			pMask += 4;
		}
		pSrc += offset;
		pDst += offset;
		pMask += offset;
	}
	free(gaussData);
	free(maskData);
	return ret;
}