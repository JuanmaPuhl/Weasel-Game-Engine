#pragma once
#include "GraphicAttribute.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Shader.h"
class SpriteAttribute : public GraphicAttribute
{
    public:
    SpriteAttribute(Sprite* sprite);
    ~SpriteAttribute();
    void passToShader(Shader* shader, double deltaTime);
    Sprite* getSprite();
    void setSprite(Sprite* sprite);
    GraphicAttribute* copy();
    private:
    Sprite* sprite;

};