//
// Created by william on 2025/1/31.
//

#include "gray.h"
#include <algorithm>

int gray(const Texture& originTexture, int mode)
{
    auto& info = originTexture.getInfo();
    unsigned char* srcData = info.data;
    int width = info.width;
    int height = info.height;
    int stride = info.stride;
    
	int ret = 0;
	int offset = stride - width * 4;
	unsigned char* pSrc = srcData;
	switch(mode)
	{
	case 0://mean gray method
		for(int j = 0; j < height; ++j)
	    {
	    	for(int i = 0; i < width; ++i)
	    	{
	    		int gray = (pSrc[0] + pSrc[1] + pSrc[2]) / 3;
				pSrc[0] = gray;
				pSrc[1] = gray;
				pSrc[2] = gray;
				pSrc += 4;
	    	}
			pSrc += offset;
	    }
		break;
	case 1://classic gray method
		for(int j = 0; j < height; ++j)
	    {
	    	for(int i = 0; i < width; ++i)
	    	{
	    		int gray = (299 *  pSrc[2] + 587 * pSrc[1] + 114 * pSrc[0]) / 1000;
				pSrc[0] = gray;
				pSrc[1] = gray;
				pSrc[2] = gray;
				pSrc += 4;
	    	}
			pSrc += offset;
	    }
		break;
	case 2://photoshop gray method
		for(int j = 0; j < height; ++j)
	    {
	    	for(int i = 0; i < width; ++i)
	    	{
				int gray = (std::max(pSrc[0], std::max(pSrc[1], pSrc[2])) + std::min(pSrc[0], std::min(pSrc[1], pSrc[2]))) / 2;
	    		pSrc[0] = gray;
				pSrc[1] = gray;
				pSrc[2] = gray;
				pSrc += 4;
	    	}
			pSrc += offset;
	    }
		break;
	default:
		break;
	}
	return ret;
}