//
// Created by william on 2025/1/31.
//
#include "meanFilter.h"
#include <chrono>
#include <iostream>

int main()
{
    {
        Texture dog("dog.png");
        auto start = std::chrono::high_resolution_clock::now(); // 开始计时
        fastMeanFilter(dog, 5);
        auto end = std::chrono::high_resolution_clock::now();   // 结束计时
        std::chrono::duration<double> duration = end - start;
        std::cout << "fastMeanFilter time: " << duration.count() << " seconds\n";
        dog.save("dog_fastMeanFilter.png");
    }

    {
        Texture dog("dog.png");
        auto start = std::chrono::high_resolution_clock::now(); // 开始计时
        meanFilter(dog, 5);
        auto end = std::chrono::high_resolution_clock::now();   // 结束计时
        std::chrono::duration<double> duration = end - start;
        std::cout << "meanFilter time: " << duration.count() << " seconds\n";
        dog.save("dog_meanFilter.png");
    }

    return 0;
}