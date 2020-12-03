#ifndef ANIMATION_H
#define ANIMATION_H
#include "Sprite.h"
class Animation
{
    public:
        Animation(int size);
        Animation(int size, Sprite** spr);
        ~Animation();
        void setSpeed(double speed);
        void setSprites(Sprite** spr);
        double getSpeed();
        Sprite** getSprites();
        Sprite* getCurrentSprite(float deltaTime);

    private:
        double speed = 0.0;
        Sprite** sprites;
        int size;
        double index_aux = 0.0;

};
#endif