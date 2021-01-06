#include "Game.h"

GameData* gamedata =new GameData();
KeyboardControl* keyboardControl = new KeyboardControl();
void Game::init(int width, int height)
{
    gamedata->window = window::window_init(width,height);
    gamedata->shader = new Shader(DEFAULT_SHADER_FILE);
    Gui::init(gamedata->window);
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
        std::string str;
        //Gui::writeToLog("FPS: "+std::to_string(fps) + "\n");
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

void Game::loopFunction(double deltaTime)
{ 

    Game::onUpdate(deltaTime);
    Game::render(deltaTime);
    Gui::draw();
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

Sprite* Game::findSpriteByName(std::string name)
{
    std::vector<Sprite*>::iterator ptr;
    for(ptr = gamedata->sprites.begin(); ptr < gamedata->sprites.end(); ptr++)
    {
        Gui::writeToLog("BUSCANDING: " + name + " Encontrado: "+ (*(ptr))->getName().c_str()+ "\n");
        if(strcmp((*(ptr))->getName().c_str(),name.c_str())==0)
        {
            return (*(ptr));
        }
    }
    return NULL;
}

void Game::addSprite(Sprite* sprite)
{
    gamedata->sprites.push_back(sprite);
}