#include "Game.h"

GameData* gamedata =new GameData();
KeyboardControl* keyboardControl = new KeyboardControl();
void Game::init(int width, int height)
{
    gamedata->window = window::window_init(width,height);
    gamedata->shader = new Shader(DEFAULT_SHADER_FILE);
}

Level* Game::addLevel()
{
    Level* level = new Level();
    gamedata->levels.push_back(level);
    return level;
}

void Game::onUpdate(double deltaTime)
{
    gamedata->currentLevel->onUpdate(deltaTime);
}
float last_time = 0.0f;
int fps = 0;
const int MAX_FPS = 120;
const double maxPeriod  =1.0/double(MAX_FPS);
double lastTime = 0.0f;
double lastTimeForSleep = 0.0;
const int MAX_FRAMERATE = 120;
void Game::render(double deltaTime)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    float current = glfwGetTime();
    double delta = current - lastTime;
    lastTime = current;
    fps++;
    if(current - last_time >=1.0f)
    {
        double fpsCount = 1000.0/double(fps);
        printf("FPS: %d\n",fps);
        fps = 0;
        last_time++;
    }
    while(glfwGetTime()<lastTimeForSleep+double(1.0/MAX_FRAMERATE))
    {
        //No hago nada. Limito fps.
    }
    lastTimeForSleep += 1.0/MAX_FRAMERATE; 
    gamedata->currentLevel->render(gamedata->shader,deltaTime);
}

Level* Game::getCurrentLevel()
{
    return gamedata->currentLevel;
}

void Game::setLevel(int level)
{
    if(level>=0 && level<gamedata->levels.capacity())
        gamedata->currentLevel=gamedata->levels.at(level);
    else
    {
        printf("ERROR: Nivel invalido.\n");
    }
    
    
}

GLFWwindow* Game::getWindow()
{
    return gamedata->window;
}
void loopFunction(double deltaTime)
{
    Game::onUpdate(deltaTime);
    Game::render(deltaTime);
}    
void Game::loop()
{
    window::window_loop(gamedata->window,loopFunction);
}

void Game::close()
{
    free(gamedata);
    free(keyboardControl);
}