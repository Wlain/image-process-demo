//
// Created by william on 2025/1/31.
//

#include "gaussFilter.h"

int fastGaussFilter(const Texture& originTexture, float r)
{
    auto& info = originTexture.getInfo();
    unsigned char* srcData = info.data;
    int width = info.width;
    int height = info.height;
    int stride = info.stride;
    return fastGaussFilter(srcData, width, height, stride, r);
}

int fastGaussFilter(unsigned char* srcData,int width, int height,int stride,float r)
{
    int ret = 0;
	int radius = (int)r;
	if(r == 0)
		return ret;
	auto* dstData = (unsigned char*)malloc(sizeof(unsigned char)*height*stride);
    auto* tempData = (unsigned char*)malloc(sizeof(unsigned char)*height*stride);
	memset(dstData, 255, sizeof(unsigned char) * height * stride);
    int totalWei = 0;
    int i,j,k;
    float sigma = r;   
    auto *kernel = (unsigned char *)malloc(2*radius+1);
    for (i = -radius; i <= radius; i++)
    {        
        kernel[i+radius] = (unsigned char) (exp(-(float)i*i/(2*sigma*sigma))*128);
        totalWei += kernel[i+radius];
    }
    int tempR = 0, tempG = 0, tempB = 0;
    int v = 0;
    int K = 0;
    int rem = 0;
    int t = 0;
	int offset = stride - width * 4;
    for ( j = 0; j < height; j++)
    {
        for ( i = 0; i < width; i++)
        {
            tempR = 0; tempG = 0; tempB = 0;
            for ( k = -radius; k <= radius; k++)
            {
                rem = (abs(i + k) % width);
                t = rem * 4 + j * stride;
                K = kernel[k + radius];
                tempB += srcData[t] * K;
                tempG += srcData[t + 1] * K;
                tempR += srcData[t + 2] * K;
            }
            v = i * 4 + j * stride;
            tempData[v] = tempB / totalWei;
            tempData[v + 1] = tempG / totalWei;
            tempData[v + 2] = tempR / totalWei;
        }
    }
    for ( i = 0; i < width; i++)
    {
        for ( j = 0; j < height; j++)
        {
            tempR = 0; tempG = 0; tempB = 0;
            for ( k = -radius; k <= radius; k++)
            {
                rem = (abs(j + k) % height);
                t = rem * stride + i * 4;
                K = kernel[k + radius];
                tempB += tempData[t] * K;
                tempG += tempData[t + 1] * K;
                tempR += tempData[t + 2] * K;
            }
            v = i * 4 + j * stride;
            dstData[v] = tempB/totalWei;
            dstData[v + 1] = tempG/totalWei;
            dstData[v + 2] = tempR/totalWei;
        }
    }
	memcpy(srcData, dstData, sizeof(unsigned char) * height * stride);
	free(dstData);
    free(tempData);
    return ret;
}