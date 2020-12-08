#pragma once
#include "ScriptComponent.h"
#include "KeyboardControl.h"
#include "Config.h"
#include "stdio.h"
class Prueba : public ScriptComponent
{
      public: 
        void onCreate()
        {
          printf("ONCREATE.\n");
        }
        void onUpdate()
        {
          //printf("Hello World, I'm %d\n",this->id);
          if(kc->isPressed(keyboard::KEY_DOWN))
          {
            printf("HOLI.\n");
          }
        }
      private:
        int id = 0;
};

class EntityOriginal : public ScriptComponent
{
    public:
        void onCreate()
        {

        }
        void onUpdate()
        {
            if(kc->isPressed(keyboard::KEY_Q))
            {
                printf("Entity1::Hola.\n");
            }
        }
};