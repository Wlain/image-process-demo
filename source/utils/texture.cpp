//
// Created by william on 2025/1/27.
//

#include "texture.h"

#include "fileUtils.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

Texture::Texture(const char* filename)
{
    const auto realPath = getAssetDir(filename);
    assert(fileExists(realPath.c_str()));
    m_info.data = stbi_load(realPath.c_str(), &m_info.width, &m_info.height, &m_info.channels, 4);
    m_info.stride = m_info.width * 4;
}

Texture::~Texture()
{
    stbi_image_free(m_info.data);
}

bool Texture::save(const char* filename)
{
    std::string path = SOURCE_DIR;
    path.append("/result/").append(filename);
    if (!stbi_write_png(path.c_str(), m_info.width, m_info.height, 4, m_info.data, m_info.stride))
    {
        printf("Failed to write image!\n");
        return false;
    }
    return true;
}

void Texture::saveHistogramImage(const std::vector<int>& hist, const char* filename)
{
    const int width = 512;
    const int height = 256;
    const int maxBarHeight = height - 20; // 留白区域

    std::vector<unsigned char> pixels(width * height * 3, 255); // 初始化为白色背景

    // 计算直方图的最大值（用于归一化条形高度）
    int maxCount = *std::max_element(hist.begin(), hist.end());
    if (maxCount == 0) maxCount = 1; // 避免除以零

    // 绘制直方图条形
    for (int i = 0; i < hist.size(); ++i) {
        int barHeight = static_cast<int>((hist[i] / static_cast<float>(maxCount)) * maxBarHeight);
        int startX = i * (width / 256); // 每个灰度级对应一个条形

        // 绘制条形（黑色）
        for (int y = height - 1; y >= height - barHeight; --y) {
            for (int x = startX; x < startX + (width / 256); ++x) {
                if (x < width && y >= 0) {
                    int index = (y * width + x) * 3;
                    pixels[index] = 0;     // R
                    pixels[index + 1] = 0; // G
                    pixels[index + 2] = 0; // B
                }
            }
        }
    }

    // 保存为PNG
    std::string path = SOURCE_DIR;
    path.append("/result/").append(filename);
    stbi_write_png(path.c_str(), width, height, 3, pixels.data(), width * 3);
}
