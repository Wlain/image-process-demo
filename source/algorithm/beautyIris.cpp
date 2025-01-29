//
// Created by william on 2025/1/29.
//
#include "meanFilter.h"
#include "beautyIris.h"
#include <algorithm>
#include <rgb2yuv.h>

bool PNPolyOPT(int xPoint[],int yPoint[],int pointNum,int x, int y, int minX, int minY, int maxX, int maxY)
{
	if(x < minX || x > maxX || y < minY || y > maxY)
		return false;
	int i, j, c = 0;
	for(i = 0, j = pointNum - 1; i < pointNum; j = i++)
	{
		if((float)((yPoint[i] > y) != (yPoint[j] > y)) && (x < (float)(xPoint[j] - xPoint[i]) * (y - yPoint[i]) / (yPoint[j] - yPoint[i]) + xPoint[i]))
			c = !c;
	}
	return c;
}


bool PNPoly(int xPoint[],int yPoint[],int pointNum,int x, int y)
{
	int i, j, c = 0;
	for(i = 0, j = pointNum - 1; i < pointNum; j = i++)
	{
		if((float)((yPoint[i] > y) != (yPoint[j] > y)) && (x < (float)(xPoint[j] - xPoint[i]) * (y - yPoint[i]) / (yPoint[j] - yPoint[i]) + xPoint[i]))
			c = !c;
	}
	return c;
}

int beautyIris(unsigned char* srcData, int width, int height, int stride, int srcPoints[], unsigned char* maskData, int mWidth, int mHeight, int mStride, int maskPoints[], int ratio)
{
	int ret = 0;
	unsigned char* pSrc = srcData;
	int cenx = srcPoints[2 * 12];
	int ceny = srcPoints[2 * 12 + 1];
	//compute iris radius.
	int eyedistance = std::sqrt((float)(srcPoints[2 * 0] - srcPoints[2 * 6]) * (srcPoints[2 * 0] - srcPoints[2 * 6]) + (srcPoints[2 * 0 + 1] - srcPoints[2 * 6 + 1]) * (srcPoints[2 * 0 + 1] - srcPoints[2 * 6 + 1])) / 2;
	int irisRadius = eyedistance / 2;
	//compute the rectangle of eye area.
	int px = std::clamp(cenx - irisRadius, 0, width - 1);
	int py = std::clamp(ceny - irisRadius, 0, height - 1);
	int pmaxX = std::clamp(cenx + irisRadius, 0, width - 1);
	int pmaxY = std::clamp(ceny + irisRadius, 0, height - 1);
	int w = pmaxX - px;
	int h = pmaxY - py;
	const int pointNum = 12;
	int xPoints[pointNum];
	int yPoints[pointNum];
	int maxX = 0, minX = 100000, maxY = 0, minY = 100000;
	for(int i = 0; i < pointNum; i++)
	{
		xPoints[i] = srcPoints[2 * i];
		yPoints[i] = srcPoints[2 * i + 1];
		maxX = std::max(srcPoints[2 * i], maxX);
		maxY = std::max(srcPoints[2 * i + 1], maxY);
		minX = std::min(srcPoints[2 * i], minX);
		minY = std::min(srcPoints[2 * i + 1], minY);
	}
	//irisMask feather process
    unsigned char* irisMask = (unsigned char*)malloc(sizeof(unsigned char) * w * h * 4);
	unsigned char* pMask = irisMask;
	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < w; i++)
		{
			int dis = sqrt((float)(i - irisRadius) * (i - irisRadius) + (j - irisRadius) * (j - irisRadius));
			if(PNPolyOPT(xPoints, yPoints, pointNum, i + px, j + py, minX, minY, maxX, maxY) && dis < irisRadius-3)
				pMask[0] = pMask[1] = pMask[2] = 255;
			else
				pMask[0] = pMask[1] = pMask[2] = 0;
			pMask += 4;
		}
	}
	fastMeanFilter(irisMask, w, h, w * 4, 3);
	pMask = irisMask;
	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < w; i++)
		{
			if(pMask[0] > 128)
				pMask[0] = pMask[1] = pMask[2] = 255;
			else
				pMask[0] = pMask[1] = pMask[2] = 0;
			pMask += 4;
		}
	}
	fastMeanFilter(irisMask, w, h, w * 4, 3);
	//beauty iris process
	pMask = irisMask;
	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < w; i++)
		{
			if((pMask[0] + pMask[1] + pMask[2]) / 3 > 0)
			{
			    int pos_src = (px + i) * 4 + (py + j) * stride;
			    int mx = i * mWidth / w;
			    int my = j * mHeight / h;
			    int pos_mask = mx * 4 + my * mStride;
			    int r = srcData[pos_src + 2];
			    int g = srcData[pos_src + 1];
			    int b = srcData[pos_src];
			    int mr = maskData[pos_mask + 2];
			    int mg = maskData[pos_mask + 1];
			    int mb = maskData[pos_mask];
			    int Y, U, V, mY, mU, mV;
				//YUV
			    rgb2yuv(r, g, b,&Y, &U, &V);
			    rgb2yuv(mr, mg, mb, &mY, &mU, &mV);
			    unsigned char R, G, B;
			    yuv2rgb(Y, mU, mV, &R, &G, &B);
				//feather mask process
				int a = (pMask[0] + pMask[1] + pMask[2]) / 3;
				B = std::clamp((b * (255 - a) + B * a) >> 8, 0, 255);
				G = std::clamp((g * (255 - a) + G * a) >> 8, 0, 255);
				R = std::clamp((r * (255 - a) + R * a) >> 8, 0, 255);
				//YUV color correct
			    a = std::clamp((r + g + b) / 3 * 2, 0, 255);
				R = (R * a + r * (255 - a)) / 255;
				G = (G * a + g * (255 - a)) / 255;
				B = (B * a + b * (255 - a)) / 255;
				//ratio blending
				B = std::clamp((b * (100 - ratio) + B * ratio) / 100, 0, 255);
				G = std::clamp((g * (100 - ratio) + G * ratio) / 100, 0, 255);
				R = std::clamp((r * (100 - ratio) + R * ratio) / 100, 0, 255);

				srcData[pos_src]     = B;
				srcData[pos_src + 1] = G;
				srcData[pos_src + 2] = R;
			}
			pMask += 4;
		}
	}
	free(irisMask);
	return ret;
};