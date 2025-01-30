//
// Created by william on 2025/1/31.
//

#include "rgb2lab.h"

#include <algorithm>

constexpr float T0 = 0.008856f; // 216.0f / 24389.0f;
constexpr float T1 = 7.78704f;  // 841.0f / (3.0f * 36.0f);
constexpr float T2 = 0.13793f;  // 4.0f / 29.0f;
constexpr float T3 = 0.20690f;  // 6.0f / 29.0f;
constexpr float T4 = 0.12842f;  // 3.0f * 36.0f / 841.0f;
constexpr float T = 0.00392f;   // 1.0f / 255.0f;
constexpr float T5 = 1.05213f;  // 1.0f / 0.950456f;
constexpr float T6 = 0.91848f;  // 1.0f / 1.088754f;
constexpr float T7 = 0.39216f;  // 100.0f / 255.0f;
constexpr float T8 = 0.00862f;  // 1.0f / 116.0f;
constexpr float T9 = 0.002f;    // 1.0f / 500.0f;
constexpr float T10 = 0.005f;   // 1.0f / 200.0f;

inline float ft(float t)
{
    return t > T0 ? pow(t, 1.0f / 3.0f) : T1 * t + T2;
}

inline float Sft(float t)
{
    return t > T3 ? pow(t, 3) : T4 * (t - T2);
}

void rgb2lab(unsigned char R, unsigned char G, unsigned char B, int* L, int* a, int* b)
{
    float X, Y, Z;
    X = 0.412453f * R + 0.357580f * G + 0.180423f * B;
    Y = 0.212761f * R + 0.715160f * G + 0.072169f * B;
    Z = 0.019334f * R + 0.119193f * G + 0.950227f * B;
    X = X * T;
    Y = Y * T;
    Z = Z * T;
    *L = std::clamp(116.0f * ft(Y) - 16.0f, 0.0f, 100.0f);
    *a = std::clamp(500.0f * (ft(X * T5) - ft(Y)), -128.0f, 127.0f);
    *b = std::clamp(200.0f * (ft(Y) - ft(Z * T6)), -128.0f, 127.0f);
    *L = *L * 2.55f;
    *a = *a + 128;
    *b = *b + 128;
}

void lab2rgb(int L, int a, int b, unsigned char* R, unsigned char* G, unsigned char* B)
{
    float X, Y, Z;
    L = L * T7;
    a = a - 128;
    b = b - 128;
    X = Sft((L + 16.0f) * T8);
    Y = 0.950456f * Sft((L + 16.0f) * T8 + a * T9);
    Z = 1.088754f * Sft((L + 16.0f) * T8 - b * T10);
    *R = std::clamp(3.240479f * X - 1.537150f * Y - 0.498535f * Z, 0.0f, 255.0f);
    *G = std::clamp(-0.969256f * X + 1.875992f * Y + 0.041556f * Z, 0.0f, 255.0f);
    *B = std::clamp(0.055648F * X - 0.204043f * Y + 1.057311f * Z, 0.0f, 255.0f);
}