#ifndef GAME_H
#define GAME_H
#include "Level.h"
#include "../Graphics/Shader.h"
#include "../Config.h"
#include "../Graphics/window.h"
#include "../Graphics/Quad.h"
#include "../Config.h"
#include "../Controls/KeyboardControl.h"

struct GameData
    {
        GLFWwindow* window = NULL;
        std::vector<Level*> levels;
        Level* currentLevel = NULL;
        Shader* shader = NULL;
    };
    extern GameData* gamedata;
namespace Game
{
    void init(int width, int height);
    Level* addLevel();
    Level* getCurrentLevel();
    void setLevel(int level);
    void onUpdate(double deltaTime);
    void render(double deltaTime);
    GLFWwindow* getWindow();
    void loop();
    void close();
}
#endif