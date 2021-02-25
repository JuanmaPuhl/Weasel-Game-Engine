#ifndef GAME_H
#define GAME_H
#include "Level.h"
#include "../Graphics/Shader.h"
#include "../Config.h"
#include "../Graphics/window.h"
#include "../Graphics/Quad.h"
#include "../Config.h"
#include "../Controls/KeyboardControl.h"
#include "../Graphics/Gui.h"
enum GAME_STATUS {PLAY, PAUSE, STOP};
struct GameData
    {
        GLFWwindow* window = NULL;
        std::vector<Level*> levels;
        Level* currentLevel = NULL;
        Shader* shader = NULL;
        Shader* shaderParticles = NULL;
        std::vector<Sprite*> sprites;
        std::vector<Sprite*> system_sprites;
        GAME_STATUS status;
        double deltaTime;
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
    std::vector<Level*> getLevels();
    void getGui();
    std::vector<Sprite*> getSprites();
    std::vector<Sprite*> getSystemSprites();
    Sprite* findSystemSpriteByName(std::string name);
    void addSystemSprite(Sprite* sprite);
    void close();
    void playGame();
    void pauseGame();
    void stopGame();
    void newGame();
    double getDeltaTime();
    Shader* getParticleShader();
}
#endif