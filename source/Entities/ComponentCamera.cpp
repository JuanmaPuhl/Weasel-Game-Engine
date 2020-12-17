#include "ComponentCamera.h"
ComponentCamera::ComponentCamera(int width, int height)
{
    this->width = width;
    this->height = height;
    this->onCreate();
}

ComponentCamera::~ComponentCamera()
{
    
}
glm::mat4 ComponentCamera::getViewMatrix()
{
    return this->viewMatrix;
}

glm::mat4 ComponentCamera::getProjectionMatrix()
{
    return this->projectionMatrix;
}

void ComponentCamera::onCreate()
{
    this->up = glm::vec3(0.0f,1.0f,0.0f);
    this->direction = glm::vec3(0.0f,0.0f,0.0f);
    this->projectionMatrix = glm::ortho(-float(width/2), float(width/2), -float(height/2),float(height/2), -10.0f, 10.0f);
    this->position = glm::vec3(0.0f, 0.0f, 3.0f);
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    
    this->viewMatrix = glm::lookAt(this->position,this->position + this->front, this->up);
    this->cameraTarget = glm::normalize(this->position - this->direction);
    this->cameraRight = glm::normalize(glm::cross(this->up, this->cameraTarget));
    this->cameraUp = glm::cross(this->cameraTarget, this->cameraRight);
}

void ComponentCamera::onUpdate()
{
    float deltaTime = 0.02;
    this->viewMatrix = glm::lookAt(this->position,this->position + this->front, this->up);
    if(this->zoomOrder != 0)
    {
        if(this->zoomValue >=0.01f)
        {
            this->zoomValue -= this->zoomOrder*this->zoomVelocity*deltaTime;
            this->projectionMatrix = glm::ortho(
                -float(this->width/2)*this->zoomValue,
                float(this->width/2)*this->zoomValue,
                -float(this->height/2)*this->zoomValue,
                float(this->height/2)*this->zoomValue,
                -1.0f,
                10.0f
            );
        }
        else
        {
            this->zoomValue = 0.01f;
        }
    }
    if(this->movementDirection[0] != 0.0f || this->movementDirection[1] != 0.0f)
        this->position +=   this->movementDirection[0] * glm::normalize(
                            glm::cross(this->front,
                            this->cameraUp))
                            * this->velocity * deltaTime;
        this->position +=   glm::vec3(0.0f,this->movementDirection[1],0.0f)
                            * this->velocity * deltaTime;
}

void ComponentCamera::zoom(float factor)
{
    this->zoomOrder = factor;
}

void ComponentCamera::move(glm::vec2 dir)
{
  this->movementDirection = dir;

}

Component* ComponentCamera::copy()
{
    ComponentCamera* cc = new ComponentCamera(this->width,this->height);
    
}