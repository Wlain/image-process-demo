//
// Created by william on 2025/1/29.
//

#ifndef RGB2YUV_H
#define RGB2YUV_H

void rgb2yuv(unsigned char R, unsigned char G, unsigned char B, int *Y, int* U, int*V);

void yuv2rgb(int Y, int U, int V, unsigned char * R, unsigned char * G, unsigned char *B);

#endif //RGB2YUV_H
