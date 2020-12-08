#ifndef KEYBOARD_CONTROL_H
#define KEYBOARD_CONTROL_H
#include "Control.h"
#include <stdlib.h>
#include <stdio.h>

class KeyboardControl : protected Control
{
    
    public:
    enum Key
    {
        KEY_UP = 265,
        KEY_DOWN = 264,
        KEY_LEFT = 263,
        KEY_RIGHT = 262
    };
    KeyboardControl();
    ~KeyboardControl();
    void setKey(int key, bool action);
    bool isPressed(int key);
    private:
        const int MAX_KEYS = 1024;
};
#endif