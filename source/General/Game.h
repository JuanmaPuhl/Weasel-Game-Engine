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
        std::vector<Sprite*> sprites;
    };
    extern GameData* gamedata;
namespace Game
{
    void init(int width, int height);
    Level* addLevel();
    Level* getCurrentLevel();
    void addSprite(Sprite* sprite);
    void setLevel(int level);
    void onUpdate(double deltaTime);
    Sprite* findSpriteByName(std::string name);
    void render(double deltaTime);
    GLFWwindow* getWindow();
    void loop();
    void loopFunction(double deltaTime);
    void close();
}
#endif