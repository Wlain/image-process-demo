//
// Created by william on 2025/1/28.
//

#ifndef RGB2HSV_H
#define RGB2HSV_H

void RGB2HSV(unsigned char R, unsigned char G, unsigned char B, float *H, float *S, float *V);
void HSV2RGB(float H, float S, float V, unsigned char * R, unsigned char * G, unsigned char *B);

#endif //RGB2HSV_H
