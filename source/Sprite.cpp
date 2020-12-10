#include "Sprite.h"


Sprite::Sprite(const char* dir)
{
    //this->spriteImage = loadImage(dir,mode);
    this->spriteImage = imageFileManager::loadImage(dir);
}
    

Sprite::~Sprite()
{
    printf("ELIMINANDO SPRITE.\n");
}

unsigned int Sprite::getSpriteImage()
{
    return this->spriteImage;
}