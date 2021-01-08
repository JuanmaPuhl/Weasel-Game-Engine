#include "Level.h"
#include "../Entities/ComponentCamera.h"
Level::Level()
{
}

Level::~Level()
{   
    std::vector<Entity*>::iterator ptr;
    for(ptr = this->entities.begin(); ptr<this->entities.end(); ptr++)
    {
        delete((*(ptr)));
    }
}

Entity* Level::addEntity()
{
    Entity* entity = new Entity();
    this->entities.push_back(entity);
    return entity;
}

Entity* Level::addEntityCamera(int width, int height)
{
    Entity* entity = new Entity();
    entity->addComponent(new ComponentCamera(width,height));
    this->cameraEntity = entity;
    return entity;
}

void Level::onUpdate(double deltaTime)
{
    if(this->cameraEntity !=NULL)
        this->cameraEntity->onUpdate();
    std::vector<Entity*>::iterator ptr;
    for(ptr = this->entities.begin(); ptr<this->entities.end(); ptr++)
    {
        (*(ptr))->onUpdate();
    }
}

void Level::render(Shader* shader, double deltaTime)
{
    //Tengo que pasar la camara al shader
    
    shader->use();
    if(this->cameraEntity!=NULL)
    {
        shader->setUniform("projection",glm::value_ptr(((ComponentCamera*)(this->cameraEntity->getComponent(0)))->getProjectionMatrix()));
        shader->setUniform("view",glm::value_ptr(((ComponentCamera*)(this->cameraEntity->getComponent(0)))->getViewMatrix()));
    }
    //Tengo que ciclar entre todas las entidades y renderizarlas
    std::vector<Entity*>::iterator ptr;
    for(ptr = this->entities.begin(); ptr<this->entities.end(); ptr++)
    {
        (*(ptr))->render(shader,deltaTime);
    }
}

std::vector<Entity*> Level::getEntities()
{
    return this->entities;
}

bool Level::removeEntity(int entity)
{
    this->entities.erase(this->entities.begin()+entity);
    return false;
}