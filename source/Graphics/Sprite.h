#ifndef SPRITE_H
#define SPRITE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "../FileManagement/ImageFileManager.h"
enum Mode {normal, transparent};
class Sprite
{
    public:
    Sprite(const char** dir, int size);
    Sprite(unsigned int*, int size);
    ~Sprite();
    unsigned int getSpriteImage(int index);
    int getCurrentSprite(float deltaTime);
    void setSpeed(double speed);
    int getSize();
    unsigned int* getImages();
    float getTransparency();
    void setTransparency(float transparency);
    Sprite* copy(Sprite* sprite);
    double getSpeed();
    private:
    double speed = 0.0;
    int size;
    double index_aux = 0.0;
    unsigned int* spriteImage;
    float transparency = 1.0f;
};
#endif