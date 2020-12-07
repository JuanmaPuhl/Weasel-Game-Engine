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

void Level::render(Shader* shader)
{
    //Tengo que pasar la camara al shader
    
    shader->use();
    int projectionLocation = glGetUniformLocation(shader->getShaderProgram(),"projection");
    int viewLocation = glGetUniformLocation(shader->getShaderProgram(),"view");
    int modelLocation = glGetUniformLocation(shader->getShaderProgram(),"model");
    glUniformMatrix4fv(projectionLocation,1,GL_FALSE,glm::value_ptr(this->camera->getProjectionMatrix()));
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,glm::value_ptr(this->camera->getViewMatrix()));
    //Tengo que ciclar entre todas las entidades y renderizarlas
    std::vector<Entity*>::iterator ptr;
    for(ptr = this->entities.begin(); ptr<this->entities.end(); ptr++)
    {
        (*(ptr))->render(shader);
    }
}