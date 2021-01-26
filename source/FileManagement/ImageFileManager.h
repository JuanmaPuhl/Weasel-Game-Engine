#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

struct Image
{
    int height, width, nr_channels;
    const char* dir;
    unsigned int image;
};

namespace imageFileManager
{
    Image* loadImage(const char* dir);
};
