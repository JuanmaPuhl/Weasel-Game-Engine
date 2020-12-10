#include "KeyboardControl.h"

KeyboardControl::KeyboardControl()
{
    this->keys = (bool*)malloc(sizeof(bool)*this->MAX_KEYS);
    for(int i = 0; i < this->MAX_KEYS; i++)
    {
        this->keys[i] = RELEASED;
    }
}

KeyboardControl::~KeyboardControl()
{
    free(this->keys);
}

void KeyboardControl::setKey(int key, bool action)
{
    if(key>=this->MAX_KEYS)
    {
        printf("KeyboardControl:: key greater than max_keys.\n");
    }
    else
    {
        this->keys[key] = action;
    }
    
    
}

bool KeyboardControl::isPressed(keyboard::Key key)
{
    if(key>=this->MAX_KEYS)
    {
        printf("KeyboardControl:: key greater than max_keys.\n");
        return false;
    }
    else
    {
        return this->keys[key];
    }
}