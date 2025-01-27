#include "texture.h"

static int filter512(unsigned char* srcData, int width, int height, int stride, unsigned char* Map)
{
    int i, j, r, g, b, pos, nx, ny, k;
    unsigned char* pSrc = srcData;
    int offset = stride - (width * 4);
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            b = pSrc[0];
            g = pSrc[1];
            r = pSrc[2];
            k = (b >> 2);
            nx = (int)(r >> 2) + ((k - ((k >> 3) << 3)) << 6);
            ny = (int)(((b >> 5) << 6) + (g >> 2));
            pos = (nx * 4) + (ny * 512 * 4);
            pSrc[0] = Map[pos];
            pSrc[1] = Map[pos + 1];
            pSrc[2] = Map[pos + 2];
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
