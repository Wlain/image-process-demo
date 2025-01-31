//
// Created by william on 2025/1/31.
//
#include "histagram.h"

int main()
{
    Texture dog("dog.png");
    std::vector<int> hist(256, 0);
    {
        hist.resize(256, 0);
        histagram(dog, hist.data(), 0);
        dog.saveHistogramImage(hist, "dog_histagram_gray.png");
    }
    {
        hist.resize(256, 0);
        histagram(dog, hist.data(), 1);
        dog.saveHistogramImage(hist, "dog_histagram_r.png");
    }
    {
        hist.resize(256, 0);
        histagram(dog, hist.data(), 2);
        dog.saveHistogramImage(hist, "dog_histagram_g.png");
    }
    {
        hist.resize(256, 0);
        histagram(dog, hist.data(), 3);
        dog.saveHistogramImage(hist, "dog_histagram_b.png");
    }
    return 0;
}