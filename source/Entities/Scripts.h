#pragma once
#include "ScriptComponent.h"
#include "../Controls/KeyboardControl.h"
#include "../Config.h"
#include <stdio.h>
#include "../General/Game.h"
#include "OrtographicCamera.h"
#include <GL/GLU.h>
#include <GLFW/glfw3.h>
class Prueba : public ScriptComponent
{
      public: 
        Game* game;
        void onCreate()
        {
          printf("ONCREATE.\n");
        }
        void onUpdate()
        {
          //printf("Hello World, I'm %d\n",this->id);
          if(keyboardControl->isPressed(keyboard::KEY_DOWN))
          {
            printf("EntityGeneral::Hola.\n");
          }
        }
      private:
        int id = 0;
};

class EntityOriginal : public ScriptComponent
{
  public:
      Game* game;
      void onCreate()
      {

      }
      void onUpdate()
      {
          if(keyboardControl->isPressed(keyboard::KEY_Q))
          {
              printf("Entity1::Hola.\n");
              game->setLevel(1);
          }
      }
};

class CameraController : public ScriptComponent
{
  public:
    OrtographicCamera* camera;
    void onCreate()
    {
      printf("CameraController::OnCreate.\n");
      this->direction = glm::vec2(0.0f);
    }
    void onUpdate()
    {
      this->activado = false;
      if(keyboardControl->isPressed(keyboard::KEY_I))
      {
        printf("CameraController::Presionando I.\n");
        camera->zoom(1.0f);
      }
      if (keyboardControl->isPressed(keyboard::KEY_J))
      {
        printf("CameraController::Presionando J.\n");
        camera->zoom(-1.0f);
      }  
      if(!keyboardControl->isPressed(keyboard::KEY_I) && !keyboardControl->isPressed(keyboard::KEY_J))
      {
        camera->zoom(0.0f);
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
      camera->move(this->direction);
    }
  private:
    bool activado = false;
    glm::vec2 direction;
};