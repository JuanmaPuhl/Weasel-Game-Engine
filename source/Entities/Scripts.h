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
        //this->cameraComponent->zoom(0.0f);
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
      glm::vec3 position = this->cameraComponent->getPosition();
      float velocity = 32.0f;
      float deltaTime = 0.2f;
      if(this->direction[0] != 0.0f || this->direction[1] != 0.0f)
      {
        position +=   this->direction[0] * glm::normalize(
                            glm::cross(this->cameraComponent->getFront(),
                            this->cameraComponent->getUp()))
                            * velocity;
        position +=   glm::vec3(0.0f,this->direction[1],0.0f)
                            * velocity ;
        this->cameraComponent->move(position);
      }
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
  Sprite* spriteIdle;
  Sprite* spriteWalking;
  Sprite* spriteShooting;
  Sprite* spriteFire;
  Entity* fire;
  void onCreate()
  {
    
    printf("Player::OnCreate\n");
  }

  void onUpdate()
  {
    if(this->sprAttr==NULL)
      this->sprAttr = (SpriteAttribute*)(this->player->getAttribute(0));
    double time = glfwGetTime();
    double deltaTime = time-this->lasttime;
    double speed = 96.0f;
    this->lasttime = time;
    //glm::vec3 pos = player->getPosition();
    //fire->setPosition(pos+glm::vec3(36.0f,15.0f,0.0f));
    if(keyboardControl->isPressed(keyboard::KEY_RIGHT))
    {
      if(!this->walking)
      {
        this->sprAttr->setSprite(spriteWalking);
        this->walking = true;
      }
      if(this->status == -1)
      {
        this->status = 1;
        player->scale(glm::vec3(-1.0f,1.0f,1.0f));
        fire->setPosition(glm::vec3(0.0f));
        fire->scale(glm::vec3(-1.0f,1.0f,1.0f));
      }
      glm::vec3 pos = player->getPosition();
      player->translate(glm::vec3(speed*deltaTime,0.0,0.0));
      glm::vec3 newPos = pos+glm::vec3(36.0f,15.0f,0.0f);
      fire->setPosition(newPos);
    }
    if(keyboardControl->isPressed(keyboard::KEY_LEFT))
    {
      if(!this->walking)
      {
        this->sprAttr->setSprite(spriteWalking);
        this->walking = true;
      }
      if(this->status == 1)
      {
        this->status = -1;
        player->scale(glm::vec3(-1.0f,1.0f,1.0f));
        fire->setPosition(glm::vec3(0.0f));
        fire->scale(glm::vec3(-1.0f,1.0f,1.0f));
      }
      player->translate(glm::vec3(-speed*deltaTime,0.0,0.0));
      glm::vec3 pos = player->getPosition();
      glm::vec3 newPos = pos+glm::vec3(-36.0f,15.0f,0.0f);
      fire->setPosition(newPos);
    }
    if(!keyboardControl->isPressed(keyboard::KEY_RIGHT) && !keyboardControl->isPressed(keyboard::KEY_LEFT) && !keyboardControl->isPressed(keyboard::KEY_Z))
    {
      if(this->walking)
      {
        this->walking = false;
        this->sprAttr->setSprite(spriteIdle);
      }
      if(this->disparando)
      {
        this->disparando = false;
        this->sprAttr->setSprite(spriteIdle);
      }
    }

    if(keyboardControl->isPressed(keyboard::KEY_DOWN))
    {


      player->translate(glm::vec3(0.0,-speed*deltaTime,0.0));
    }
    if(keyboardControl->isPressed(keyboard::KEY_UP))
    {

      player->translate(glm::vec3(0.0,speed*deltaTime,0.0));
    }
    if(keyboardControl->isPressed(keyboard::KEY_Z))
    {
      if(!this->disparando)
      {
        SpriteAttribute* fireAttr = (SpriteAttribute*)fire->getAttribute(0);
        fireAttr->getSprite()->setTransparency(1.0f);
        this->disparando = true;
        this->sprAttr->setSprite(spriteShooting);
      }
    }
    else
      {
        SpriteAttribute* fireAttr = (SpriteAttribute*)fire->getAttribute(0);
        fireAttr->getSprite()->setTransparency(0.0f);
      }

    
  }
  private:
  bool disparando = false;
  int status = 1;
  SpriteAttribute* sprAttr = NULL;
  bool walking = false;
  double lasttime = 0.0;

};

class BirdMovement : public ScriptComponent
{
  public:
    Entity* bird;
    
    void onCreate()
    {
      printf("BIRD::Hello!\n");
      
    }

    void onUpdate()
    {
      double time = glfwGetTime();
      double deltaTime = time-this->lasttime;
      
      this->lasttime = time;
      glm::vec3 pos = bird->getPosition();
      
      //printf("BIRD::pos: x:%f y:%f z:%f\n",pos.x,pos.y,pos.z);
      
      bird->translate(glm::vec3(this->speed*deltaTime,0.0f,0.0f));
      if(pos.x<-2600)
      {
        printf("Cambie");
        bird->setPosition(glm::vec3(0.0f));
        bird->scale(glm::vec3(-1.0f,1.0f,1.0f));
        bird->setPosition(glm::vec3(-2600.0,pos.y,pos.z));
        this->speed = 48.0;
      }
      if(pos.x>=-2300)
      {
        printf("Cambie");
        bird->setPosition(glm::vec3(0.0f));
        bird->scale(glm::vec3(-1.0f,1.0f,1.0f));
        bird->setPosition(glm::vec3(-2300.0,pos.y,pos.z));
        this->speed = -48.0;
      }
      bird->translate(glm::vec3(this->speed*deltaTime,0.0,0.0));
    }
    private:
    double lasttime = 0.0;
    double speed = -48.0;

};