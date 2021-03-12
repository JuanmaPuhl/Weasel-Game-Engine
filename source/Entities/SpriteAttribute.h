#pragma once
#include "GraphicAttribute.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Shader.h"
class SpriteAttribute : public GraphicAttribute
{
    public:
    SpriteAttribute(Sprite* sprite);
    SpriteAttribute();
    ~SpriteAttribute();
    void passToShader(Shader* shader, double deltaTime);
    Sprite* getSprite();
    void setSprite(Sprite* sprite);
    GraphicAttribute* copy();
    void unbind(Shader* shader);
    void save(std::ofstream& output_dir);
    bool registerInitialState();
    bool recoverInitialState();
    private:
    Sprite* sprite;
    Sprite* initial_sprite;


};