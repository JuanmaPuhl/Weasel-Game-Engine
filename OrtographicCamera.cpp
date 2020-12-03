#include "OrtographicCamera.h"
#include <stdio.h>
OrtographicCamera::OrtographicCamera(int width, int height)
{
    this->width = width;
    this->height = height;
    this->up = glm::vec3(0.0f,1.0f,0.0f);
    this->direction = glm::vec3(0.0f,0.0f,0.0f);
    this->projectionMatrix = glm::ortho(-float(width/2), float(width/2), -float(height/2),float(height/2), -1.0f, 10.0f);
    this->position = glm::vec3(0.0f, 0.0f, 3.0f);
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    
    this->viewMatrix = glm::lookAt(this->position,this->position + this->front, this->up);
    this->cameraTarget = glm::normalize(this->position - this->direction);
    this->cameraRight = glm::normalize(glm::cross(this->up, this->cameraTarget));
    this->cameraUp = glm::cross(this->cameraTarget, this->cameraRight);
}

OrtographicCamera::~OrtographicCamera()
{
    
}
glm::mat4 OrtographicCamera::getViewMatrix()
{
    return this->viewMatrix;
}

glm::mat4 OrtographicCamera::getProjectionMatrix()
{
    return this->projectionMatrix;
}

void OrtographicCamera::update(float deltaTime)
{
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
}

void OrtographicCamera::zoom(float factor)
{
    this->zoomOrder = factor;
}