#include "Level.h"

Level::Level()
{
}

Level::~Level()
{   
    delete(this->camera);
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

void Level::setCamera(OrtographicCamera* camera)
{
    this->camera = camera;
}

void Level::onUpdate(double deltaTime)
{
    this->camera->update(deltaTime);
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
    
    shader->setUniform("projection",glm::value_ptr(this->camera->getProjectionMatrix()));
    shader->setUniform("view",glm::value_ptr(this->camera->getViewMatrix()));
    //Tengo que ciclar entre todas las entidades y renderizarlas
    std::vector<Entity*>::iterator ptr;
    for(ptr = this->entities.begin(); ptr<this->entities.end(); ptr++)
    {
        (*(ptr))->render(shader,deltaTime);
    }
}