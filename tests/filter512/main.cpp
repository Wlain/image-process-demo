#include "filter512.h"

#include "texture.h"

int main()
{
    Texture dog("dog.png");
    const Texture lut("lookup.png");
    filter512(dog, lut);
    dog.save("dog_lookup.png");
    return 0;
}
