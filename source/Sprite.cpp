#include "Sprite.h"


Sprite::Sprite(const char** dir,int size)
{
    this->spriteImage = (unsigned int*)malloc(sizeof(unsigned int)*20);
    this->size = size;
    
    //this->spriteImage = loadImage(dir,mode);
    for(int i = 0; i < size; i++)
    {
        this->spriteImage[i] = imageFileManager::loadImage(dir[i]);
    }
}
    
Sprite::Sprite(unsigned int* arr, int size)
{
    this->spriteImage = arr;
    this->size = size;
}


Sprite::~Sprite()
{
    printf("ELIMINANDO SPRITE.\n");
    free(this->spriteImage);
}

unsigned int Sprite::getSpriteImage(int index)
{
    return this->spriteImage[index];
}

int Sprite::getCurrentSprite(float deltaTime)
{
    this->index_aux += this->speed * (double)deltaTime;
    int aux = (int)this->index_aux;
    if(aux>=this->size)
    {
        aux = 0;
        index_aux = 0.0;
    }
    return aux;
}

void Sprite::setSpeed(double speed)
{
    this->speed = speed;
}

Sprite* Sprite::copy(Sprite* sprite)
{
    unsigned int* arr = sprite->getImages();
    int size = sprite->getSize();
    Sprite* spr = new Sprite(arr,size);
}

int Sprite::getSize()
{
    return this->size;
}

unsigned int* Sprite::getImages()
{
    return this->spriteImage;
}

double Sprite::getSpeed()
{
    return this->speed;
}