//
// Created by william on 2025/1/27.
//

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
    struct Info
    {
        int width{};
        int height{};
        int channels{};
        int stride{};
        unsigned char* data{};
    };

    explicit Texture(const char* filename);
    ~Texture();
    bool save(const char* filename);
    [[nodiscard]] const Info& getInfo() const { return m_info; };

private:
    Info m_info;
};

#endif // TEXTURE_H
