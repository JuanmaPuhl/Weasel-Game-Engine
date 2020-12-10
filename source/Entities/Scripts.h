#pragma once
#include "ScriptComponent.h"
#include "../Controls/KeyboardControl.h"
#include "../Config.h"
#include <stdio.h>
#include "../General/Game.h"
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