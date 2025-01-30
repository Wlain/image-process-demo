//
// Created by william on 2025/1/31.
//

#ifndef RGB2LAB_H
#define RGB2LAB_H

void rgb2lab(unsigned char R, unsigned char G, unsigned char B, int* L, int* a, int* b);
void lab2rgb(int L, int a, int b, unsigned char* R, unsigned char* G, unsigned char* B);

#endif //RGB2LAB_H
