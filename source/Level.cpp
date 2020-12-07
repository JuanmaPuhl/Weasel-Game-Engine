#include "Level.h"

Level::Level()
{
}

Level::~Level()
{

}

void Level::addEntity(Entity* entity)
{
    this->entities.push_back(entity);
}

void Level::setCamera(OrtographicCamera* camera)
{
    this->camera = camera;
}

void Level::onUpdate()
{
    std::vector<Entity*>::iterator ptr;
    for(ptr = this->entities.begin(); ptr<this->entities.end(); ptr++)
    {
        (*(ptr))->onUpdate();
    }
}

void Level::render()
{
    //Tengo que pasar la camara al shader
    //Tengo que ciclar entre todas las entidades y renderizarlas
    std::vector<Entity*>::iterator ptr;
    for(ptr = this->entities.begin(); ptr<this->entities.end(); ptr++)
    {
        (*(ptr))->render();
    }
}