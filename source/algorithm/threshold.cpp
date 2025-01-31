//
// Created by william on 2025/1/31.
//

#include "threshold.h"

int threshold(const Texture& originTexture, int T)
{
    auto& info = originTexture.getInfo();
    unsigned char* srcData = info.data;
    int width = info.width;
    int height = info.height;
    int stride = info.stride;

    int ret = 0;
	int i, j, gray, offset;
	offset = stride - width * 4;
	unsigned char* pSrc = srcData;
	for(j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			gray = (pSrc[0] + pSrc[1] + pSrc[2]) / 3;
			gray = gray < T ? 0 : 255;
			pSrc[0] = gray;
			pSrc[1] = gray;
			pSrc[2] = gray;
			pSrc += 4;
		}
		pSrc += offset;
	}
	return ret;
}