#include "Game.h"

GameData* gamedata =new GameData();
KeyboardControl* keyboardControl = new KeyboardControl();
void Game::init(int width, int height)
{
    gamedata->window = window::window_init(width,height);
    gamedata->shader = new Shader(DEFAULT_SHADER_FILE);
    gamedata->shaderParticles = new Shader(PARTICLE_SHADER_FILE);
    Gui::init(gamedata->window);
    gamedata->status = PLAY;
}

Level* Game::addLevel()
{
    Level* level = new Level();
    gamedata->levels.push_back(level);
    return level;
}

std::vector<Sprite*> Game::getSprites()
{
    return gamedata->sprites;
}


void Game::onUpdate(double deltaTime)
{
    if(gamedata->currentLevel != NULL)
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
    glClearColor(18.0f/255, 18.0f/255, 27.0f/255, 1.0f);
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
    if(gamedata->currentLevel != NULL)
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
    gamedata->deltaTime = deltaTime;
    if(gamedata->status == PLAY)
    {
        Game::onUpdate(deltaTime);
        
    }
    Game::render(deltaTime);
    Gui::draw(deltaTime);
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

Sprite* Game::findSystemSpriteByName(std::string name)
{
    std::vector<Sprite*>::iterator ptr;
    for(ptr = gamedata->system_sprites.begin(); ptr < gamedata->system_sprites.end(); ptr++)
    {
        Gui::writeToLog("[System] BUSCANDING: " + name + " Encontrado: "+ (*(ptr))->getName().c_str()+ "\n");
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

std::vector<Level*> Game::getLevels()
{
    return gamedata->levels;
}

std::vector<Sprite*> Game::getSystemSprites()
{
    return gamedata->system_sprites;
}

void Game::addSystemSprite(Sprite* sprite)
{
    gamedata->system_sprites.push_back(sprite);
}

void Game::playGame()
{
    GAME_STATUS status = gamedata->status;
    Gui::writeToLog("STATUS: "+status);
    if(status != PLAY)
    {
        gamedata->status = PLAY;
    }
}

void Game::pauseGame()
{
    
    GAME_STATUS status = gamedata->status;
    Gui::writeToLog("STATUS: "+status);
    if(status != PAUSE)
    {
        gamedata->status = PAUSE;
    }
}

void Game::stopGame()
{
    
    GAME_STATUS status = gamedata->status;
    Gui::writeToLog("STATUS: "+status);
    if(status != STOP)
    {
        gamedata->status = STOP;
    }

}

void Game::newGame()
{
    gamedata->levels.clear();
    gamedata->currentLevel = NULL;
    gamedata->sprites.clear();

}

double Game::getDeltaTime()
{
    return gamedata->deltaTime;
}

Shader* Game::getParticleShader()
{
    return gamedata->shaderParticles;
}
