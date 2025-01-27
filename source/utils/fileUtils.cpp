//
// Created by william on 2025/1/28.
//

#include "fileUtils.h"

#include <sys/stat.h>

std::string getAssetDir(const char* name)
{
    std::string path = SOURCE_DIR;
    path.append("/resource/").append(name);
    return path;
}

bool fileExists(const char* fileName)
{
    struct stat buffer = {};
    if (stat(fileName, &buffer) == 0)
    {
        if (buffer.st_mode & S_IFDIR)
        {
            return false;
        }
        return buffer.st_size > 0;
    }
    return false;
}
