//
// Created by william on 2025/1/28.
//

#ifndef rgb2hsv_H
#define rgb2hsv_H

void rgb2hsv(unsigned char R, unsigned char G, unsigned char B, float *H, float *S, float *V);
void hsv2rgb(float H, float S, float V, unsigned char * R, unsigned char * G, unsigned char *B);

#endif //rgb2hsv_H
