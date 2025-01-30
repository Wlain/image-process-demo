//
// Created by william on 2025/1/30.
//

#ifndef FILTER512_H
#define FILTER512_H
#include "texture.h"
/**
 *
 * brief:Lev Zelensky Lut 算法
 * Lut 本质上是一个3D的Lut查找表，通过展平的方式将3D图变换为2D图，进而Lut图由8 x 8 个宽高为64的正方形组成，其x坐标代表像素的R值，y 代表像素的G值。
 * 步骤1.从64个小方格定位是哪个小方格
 * 步骤2.根据Lut查找表，找到对应的RGB值
 * 步骤3.将RGB值写入到目标图像中
 * @return
 */
void filter512(const Texture& originTexture, const Texture& lutTexture);

#endif //FILTER512_H
