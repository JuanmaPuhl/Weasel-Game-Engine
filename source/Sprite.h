#ifndef SPRITE_H
#define SPRITE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <string>
enum Mode {normal, transparent};
class Sprite
{
    public:
    Sprite(const char* dir, Mode mode);
    ~Sprite();
    unsigned int getSpriteImage();
    private:
    unsigned int spriteImage;
};
#endif