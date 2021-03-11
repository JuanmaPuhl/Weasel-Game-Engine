#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.h"
#include "Entity.h"
#include "vector"
#include "../General/Game.h"
#include "../General/Level.h"

class ComponentCollisionBox : public Component
{
    public:
    ComponentCollisionBox(Entity* entity);
    ComponentCollisionBox(float x, float y, float width, float height, Entity* entity);
    ~ComponentCollisionBox();
    float getX();
    float getY();
    float getHeight();
    float getWidth();
    void onCreate();
    void onUpdate();
    void setX(float x);
    void setY(float y);
    void save(std::ofstream& output_dir);
    void setWidth(float width);
    void setHeight(float height);
    bool checkCollision(ComponentCollisionBox* b);
    Component* copy();
    private:
    float x,y,width,height;
    std::vector<Entity*> list;
    Entity* entity;
};