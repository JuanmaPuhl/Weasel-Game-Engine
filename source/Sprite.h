#ifndef SPRITE_H
#define SPRITE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "ImageFileManager.h"
enum Mode {normal, transparent};
class Sprite
{
    public:
    Sprite(const char* dir);
    ~Sprite();
    unsigned int getSpriteImage();
    private:
    unsigned int spriteImage;
};
#endif