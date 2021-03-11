#include "SpriteAttribute.h"
SpriteAttribute::SpriteAttribute(Sprite* sprite)
{
    Sprite* a = new Sprite(sprite->getImages(),sprite->getSize(),sprite->getName());
    a->setSpeed(sprite->getSpeed());
    //sprite->copy(sprite);
    this->sprite = a;
    this->setName("sprite");
    this->iniState = (initialState*)malloc(sizeof(initialState));
}
SpriteAttribute::~SpriteAttribute()
{
    free(this->iniState);
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

void SpriteAttribute::unbind(Shader* shader)
{
    glBindTexture(GL_TEXTURE_2D, 0);
    float transparency = 1.0f;
    shader->setUniform("transparency",&(transparency));
}

void SpriteAttribute::save(std::ofstream& output)
{
    output << "\"name\" : \"sprite\" , ";
    output << "\"sprite\" : \"" << this->sprite->getName().c_str() << "\""; 
}

bool SpriteAttribute::registerInitialState()
{
    this->sprite->registerInitialState();
    this->initial_sprite = this->sprite;
}
bool SpriteAttribute::recoverInitialState()
{
    this->sprite = this->initial_sprite;
    this->sprite->recoverInitialState();
}