//
// Created by william on 2025/1/25.
//

#ifndef COMMONDEFINE_H
#define COMMONDEFINE_H

#include <string>

std::string getAssetDir(const char* name)
{
    std::string path = SOURCE_DIR;
    path.append("/resource/").append(name);
    return path;
}

#endif // COMMONDEFINE_H
