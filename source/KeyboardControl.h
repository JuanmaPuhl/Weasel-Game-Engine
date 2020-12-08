#ifndef KEYBOARD_CONTROL_H
#define KEYBOARD_CONTROL_H
#include "Control.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace keyboard
{
    enum Key
    {
        KEY_UP = GLFW_KEY_UP,
        KEY_DOWN = GLFW_KEY_DOWN,
        KEY_LEFT = GLFW_KEY_LEFT,
        KEY_RIGHT = GLFW_KEY_RIGHT,
        KEY_Q = GLFW_KEY_Q,
        KEY_W = GLFW_KEY_W,
        KEY_E = GLFW_KEY_E,
        KEY_R = GLFW_KEY_R,
        KEY_T = GLFW_KEY_T,
        KEY_U = GLFW_KEY_U,
        KEY_I = GLFW_KEY_I,
        KEY_O = GLFW_KEY_O,
        KEY_P = GLFW_KEY_P,
        KEY_A = GLFW_KEY_A,
        KEY_S = GLFW_KEY_S,
        KEY_D = GLFW_KEY_D,
        KEY_F = GLFW_KEY_F,
        KEY_G = GLFW_KEY_G,
        KEY_H = GLFW_KEY_H,
        KEY_J = GLFW_KEY_J,
        KEY_K = GLFW_KEY_K,
        KEY_L = GLFW_KEY_L,
        KEY_Z = GLFW_KEY_Z,
        KEY_X = GLFW_KEY_X,
        KEY_C = GLFW_KEY_C,
        KEY_V = GLFW_KEY_V,
        KEY_B = GLFW_KEY_B,
        KEY_N = GLFW_KEY_N,
        KEY_M = GLFW_KEY_M
    };
}

class KeyboardControl : protected Control<keyboard::Key>
{
    
    public:
    
    KeyboardControl();
    ~KeyboardControl();
    void setKey(int key, bool action);
    bool isPressed(keyboard::Key key);
    private:
        const int MAX_KEYS = 1024;
};
#endif