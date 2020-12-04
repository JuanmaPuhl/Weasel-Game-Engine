#include "Animation.h"

Animation::Animation(int size)
{
    this->size = size;
    this->sprites = (Sprite**)malloc(sizeof(Sprite)*size);
}
Animation::Animation(int size, Sprite** spr)
{
    this->size = size;
    this->sprites = spr;
}

Animation::~Animation()
{
    free(this->sprites);
}

void Animation::setSprites(Sprite** spr)
{
    this->sprites = spr;
}

Sprite** Animation::getSprites()
{
    return this->sprites;
}

double Animation::getSpeed()
{
    return this->speed;
}

Sprite* Animation::getCurrentSprite(float deltaTime)
{
    this->index_aux += this->speed * (double)deltaTime;
    int aux = (int)this->index_aux;
    if(aux>=this->size)
    {
        aux = 0;
        index_aux = 0.0;
    }
    return this->sprites[aux];
}

void Animation::setSpeed(double speed)
{
    this->speed = speed;
}

int Animation::getSize()
{
    return this->size;
}