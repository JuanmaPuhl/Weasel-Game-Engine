#include "ComponentCamera.h"
#include "stdio.h"
ComponentCamera::ComponentCamera(int width, int height)
{
    this->width = width;
    this->height = height;
    this->setName("camera");
    this->onCreate();
    this->iniState = (initialState*)malloc(sizeof(initialState));
}

ComponentCamera::~ComponentCamera()
{
    free(this->iniState);
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
    this->zoomValue = 1.0f;
    this->projectionMatrix = glm::ortho(-float(width/2)*this->zoomValue, float(width/2)*this->zoomValue, -float(height/2)*this->zoomValue,float(height/2)*this->zoomValue, -10.0f, 10.0f);
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
    float zoom = this->getZoom();
    this->projectionMatrix = glm::ortho(
        -float(this->width/2)*zoom,
        float(this->width/2)*zoom,
        -float(this->height/2)*zoom,
        float(this->height/2)*zoom,
        -10.0f,
        10.0f
    );
}

void ComponentCamera::zoom(float factor)
{
    this->zoomValue = factor;
}

void ComponentCamera::move(glm::vec3 dir)
{
  this->position = dir;

}

Component* ComponentCamera::copy()
{
    ComponentCamera* cc = new ComponentCamera(this->width,this->height);
    

}


float ComponentCamera::getZoom()
{
    return this->zoomValue;
}
glm::vec3 ComponentCamera::getPosition()
{

}
glm::vec3 ComponentCamera::getDirection()
{

}
glm::vec3 ComponentCamera::getCameraTarget()
{

}
glm::vec3 ComponentCamera::getFront()
{

}
glm::vec3 ComponentCamera::getCameraRight()
{

}
glm::vec3 ComponentCamera::getUp()
{

}
int ComponentCamera::getWidth()
{

}
int ComponentCamera::getHeight()
{

}
float ComponentCamera::getVelocity()
{

}

void ComponentCamera::save(std::ofstream& output)
{
    //Guardo el nombre para poder diferenciar el componente
    output << "\"name\" : \"" << this->getName().c_str() << "\" , ";
    output << "\"visible_name\" : \"" << this->getVisibleName().c_str() << "\" ";
    //output << "\"position\" : {" << "\"x\" : " << this->position.x << " , \"y\" : " << this->position.y << " , \"z\" : " << this->position.z << "} , ";
    //output << "\"direction\" : {" << "\"x\" : " << this->direction.x << " , \"y\" : " << this->direction.y << " , \"z\" : " << this->direction.z << "} , ";
    
    
}

bool ComponentCamera::registerInitialState()
{
    printf("Camera\n");
    //Hasta que no haga el refactor no voy a tocar nada
}
bool ComponentCamera::recoverInitialState()
{
    //Hasta que no haga el refactor no voy a tocar nada
}