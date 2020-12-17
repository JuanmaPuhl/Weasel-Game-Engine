#include "SpriteAttribute.h"
SpriteAttribute::SpriteAttribute(Sprite* sprite)
{
    Sprite* a = new Sprite(sprite->getImages(),sprite->getSize());
    a->setSpeed(sprite->getSpeed());
    //sprite->copy(sprite);
    this->sprite = a;
}
SpriteAttribute::~SpriteAttribute()
{

}
void SpriteAttribute::passToShader(Shader* shader, double deltaTime)
{
    unsigned int img = this->sprite->getSpriteImage(this->sprite->getCurrentSprite(deltaTime));
    glBindTexture(GL_TEXTURE_2D, img);
    float transparency = this->sprite->getTransparency();
    shader->setUniform("transparency",&transparency);
}

void SpriteAttribute::setSprite(Sprite* sprite)
{
    Sprite* a = sprite->copy(sprite);
    this->sprite = a;
}

Sprite* SpriteAttribute::getSprite()
{
    return this->sprite;
}

GraphicAttribute* SpriteAttribute::copy()
{
    SpriteAttribute* a = new SpriteAttribute(this->sprite);
    return a;
}