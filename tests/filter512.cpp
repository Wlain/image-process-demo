#include "texture.h"

/**
 *
 * brief:Lev Zelensky Lut 算法
 * Lut 本质上是一个3D的Lut查找表，通过展平的方式将3D图变换为2D图，进而Lut图由8 x 8 个宽高为64的正方形组成，其x坐标代表像素的R值，y 代表像素的G值。
 * 步骤1.从64个小方格定位是哪个小方格
 *
 * @return
 */
static int filter512(unsigned char* srcData, int width, int height, int stride, unsigned char* lut)
{
    int pos, nx, ny, k;
    unsigned char* pSrc = srcData;
    // 处理行对齐
    int offset = stride - (width * 4);
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            int r = pSrc[0];
            int g = pSrc[1];
            int b = pSrc[2];
            k = b / 256.0f * 64;
            nx = (r / 256.0f * 64) + (k - (k / 8) * 8) * 64;
            ny = (k / 8 * (512 / 8)) + (g / 256.0f * 64);
            pos = nx * 4 + ny * 512 * 4;
            pSrc[0] = lut[pos];
            pSrc[1] = lut[pos + 1];
            pSrc[2] = lut[pos + 2];
            pSrc += 4;
        }
        pSrc += offset;
    }
    return 0;
}

int main()
{
    Texture dog("dog.png");
    const Texture lut("lookup.png");
    auto& info = dog.getInfo();
    int result = filter512(info.data, info.width, info.height, info.stride, lut.getInfo().data);
    dog.save("dog_lookup.png");
    return 0;
}
