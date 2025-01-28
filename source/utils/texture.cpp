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
    if (!stbi_write_png(filename, m_info.width, m_info.height, 4, m_info.data, m_info.stride))
    {
        printf("Failed to write image!\n");
        return false;
    }
    return true;
}