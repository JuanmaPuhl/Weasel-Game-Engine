#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"

class ComponentCollisionBox : public Component
{
    public:
    ComponentCollisionBox();
    ComponentCollisionBox(float x, float y, float width, float height);
    ~ComponentCollisionBox();
    float getX();
    float getY();
    float getHeight();
    float getWidth();
    void setX(float x);
    void setY(float y);
    void setWidth(float width);
    void setHeight(float height);
    private:
    float x,y,width,height;
};