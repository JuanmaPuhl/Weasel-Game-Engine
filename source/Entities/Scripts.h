#pragma once
#include "ScriptComponent.h"
#include "../Controls/KeyboardControl.h"
#include "../Config.h"
#include <stdio.h>
#include "../General/Game.h"
#include <GL/GLU.h>
#include <GLFW/glfw3.h>
#include "ComponentCamera.h"
#include <glm/glm.hpp>


class CameraController : public ScriptComponent
{
  public:
    Entity* camera;
    void onCreate()
    {
      this->direction = glm::vec2(0.0f);
      this->cameraComponent = (ComponentCamera*)(camera->getComponent(0));
    }
    void onUpdate()
    {
      this->activado = false;
      if(keyboardControl->isPressed(keyboard::KEY_I))
      {
        this->cameraComponent->zoom(1.0f);
      }
      if (keyboardControl->isPressed(keyboard::KEY_J))
      {
        this->cameraComponent->zoom(-1.0f);
      }  
      if(!keyboardControl->isPressed(keyboard::KEY_I) && !keyboardControl->isPressed(keyboard::KEY_J))
      {
        this->cameraComponent->zoom(0.0f);
      }
      if(keyboardControl->isPressed(keyboard::KEY_UP))
      {
        this->direction+=glm::vec2(0.0f,1.0f);
        this->activado = true;
      }
      if(keyboardControl->isPressed(keyboard::KEY_DOWN))
      {
        this->direction+=glm::vec2(0.0f,-1.0f);
        this->activado = true;
      }
      if(keyboardControl->isPressed(keyboard::KEY_LEFT))
      {
        this->direction+=glm::vec2(-1.0f,0.0f);
        this->activado = true;
      }
      if(keyboardControl->isPressed(keyboard::KEY_RIGHT))
      {
        this->direction+=glm::vec2(1.0f,0.0f);
        this->activado = true;
      }
      if(!this->activado)
      {
        this->direction=glm::vec2(0.0f);
      }
      if(this->direction.x >=1.0f) 
        this->direction.x = 1.0f;
      if(this->direction.x <= -1.0f)
        this->direction.x = -1.0f;
      if(this->direction.y >= 1.0f)
        this->direction.y = 1.0f;
      if(this->direction.y <= -1.0f)
        this->direction.y = -1.0f;
      this->cameraComponent->move(this->direction);
    }
  private:
    bool activado = false;
    glm::vec2 direction;
    ComponentCamera* cameraComponent = NULL;
};

class PlayerMovement : public ScriptComponent
{
  public:
  Entity* player;
  void onCreate()
  {
    printf("Player::OnCreate");
  }

  void onUpdate()
  {
    double time = glfwGetTime();
    double deltaTime = time-this->lasttime;
    double speed = 64.0f;
    this->lasttime = time;
    if(keyboardControl->isPressed(keyboard::KEY_RIGHT))
    {
      player->translate(glm::vec3(speed*deltaTime,0.0f,0.0f));
    }
    if(keyboardControl->isPressed(keyboard::KEY_LEFT))
    {
      player->translate(glm::vec3(-speed*deltaTime,0.0f,0.0f));
    }
    
  }
  private:
  double lasttime = 0.0;

};