//
// Created by william on 2025/1/30.
//

#include "affineTransfrom.h"
#include <algorithm>

void affinetransformMetrixCompute(float x1, float y1, float x2, float y2, float x3, float y3, float tx1, float ty1, float tx2, float ty2, float tx3, float ty3, float hMatrix[6])
{
    //求行列式|A|
    float detA;
    detA = tx1 * ty2 + tx2 * ty3 + tx3 * ty1 - tx3 * ty2 - tx1 * ty3 - tx2 * ty1;
    // 求伴随矩阵A*
    float A11, A12, A13, A21, A22, A23, A31, A32, A33;
    A11 = ty2 - ty3;
    A21 = -(ty1 - ty3);
    A31 = ty1 - ty2;
    A12 = -(tx2 - tx3);
    A22 = tx1 - tx3;
    A32 = -(tx1 - tx2);
    A13 = tx2 * ty3 - tx3 * ty2;
    A23 = -(tx1 * ty3 - tx3 * ty1);
    A33 = tx1 * ty2 - tx2 * ty1;
    //求变换矩阵H=A*/|A|  
    //float texMatrix[6]={0};
    hMatrix[0] = (x1 * A11 + x2 * A21 + x3 * A31) / detA;
    hMatrix[1] = (x1 * A12 + x2 * A22 + x3 * A32) / detA;
    hMatrix[2] = (x1 * A13 + x2 * A23 + x3 * A33) / detA;
    hMatrix[3] = (y1 * A11 + y2 * A21 + y3 * A31) / detA;
    hMatrix[4] = (y1 * A12 + y2 * A22 + y3 * A32) / detA;
    hMatrix[5] = (y1 * A13 + y2 * A23 + y3 * A33) / detA;
}

void getWHFromHMatrix(int width, int height, float H[6], int wh[2])
{
	int x0 = (H[0] * 0 + H[1] * 0 + H[2] + 0.5);
	int y0 = (H[3] * 0 + H[4] * 0 + H[5] + 0.5);
	int x1 = (H[0] * (float)(width - 1) + H[1] * (float)(height - 1) + H[2] + 0.5);
	int y1 = (H[3] * (float)(width - 1) + H[4] * (float)(height - 1) + H[5] + 0.5);
	int x2 = (H[0] * (float)(width - 1) + H[1] * 0 + H[2] + 0.5);
	int y2 = (H[3] * (float)(width - 1) + H[4] * 0 + H[5] + 0.5);
	int x3 = (H[0] * 0 + H[1] * (float)(height - 1) + H[2] + 0.5);
	int y3 = (H[3] * 0 + H[4] * (float)(height - 1) + H[5] + 0.5);
	wh[0] = std::max(x0, std::max(x1, std::max(x2, x3))) - std::min(x0, std::min(x1, std::min(x2, x3)));
	wh[1] = std::max(y0, std::max(y1, std::max(y2, y3))) - std::min(y0, std::min(y1, std::min(y2, y3)));
}

int affineTransform(const Texture& texture, float H[6], unsigned char* dstData, int dWidth, int dHeight, int dStride)
{
    auto& info = texture.getInfo();
    unsigned char* srcData = info.data;
    int width = info.width;
    int height = info.height;
    int stride = info.stride;

	int ret = 0;
	unsigned char* pSrc = dstData;
	int tx, ty, pos;
	int offset[2];
    offset[0] = ((dWidth/2.0) - (H[0]*(width/2.0) + H[1]*(height/2.0) + H[2]) + 0.5);
    offset[1] = ((dHeight/2.0) - (H[3]*(width/2.0) + H[4]*(height/2.0) + H[5]) + 0.5);
    H[2] += offset[0];
    H[5] += offset[1];
	pSrc = srcData;
	for(int j = 0; j < height; j++)
	{
		for(int i = 0; i < width; i++)
		{
		    tx = std::clamp(((H[0] * (float)(i) + H[1] * (float)(j) + H[2])), 0.0f, dWidth - 1.0f);
            ty = std::clamp(((H[3] * (float)(i) + H[4] * (float)(j) + H[5])), 0.0f, dHeight - 1.0f);
		    pos = (tx << 2) + ty * dStride;
			dstData[pos]     = pSrc[0];
			dstData[pos + 1] = pSrc[1];
			dstData[pos + 2] = pSrc[2];
			dstData[pos + 3] = 255;
			pSrc += 4;
		}
	}
	return ret;
}