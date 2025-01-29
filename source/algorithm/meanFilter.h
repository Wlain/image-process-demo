//
// Created by william on 2025/1/29.
//

#ifndef MEANFILTER_H
#define MEANFILTER_H

int meanFilter(unsigned char *srcData, int width, int height, int stride, int radius);

int fastMeanFilter(unsigned char* srcData, int width, int height ,int stride, int radius);


#endif //MEANFILTER_H
