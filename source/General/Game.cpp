#include "Game.h"
#include "../FileManagement/FileManager.h"
#include "nlohmann/json.hpp"
GameData* gamedata =new GameData();
unsigned int fbo;
unsigned int fbo2;
unsigned int tex,tex2;
int w,h;
KeyboardControl* keyboardControl = new KeyboardControl();
void Game::init(int width, int height,bool fullscr)
{
    
    gamedata->width = width;
    gamedata->height = height;
    gamedata->window = window::window_init(1920,1080,fullscr);
    gamedata->shader = new Shader(DEFAULT_SHADER_FILE);
    gamedata->shaderParticles = new Shader(PARTICLE_SHADER_FILE);
    gamedata->shaderGeneral = new Shader(GENERAL_SHADER_FILE);
    Gui::init(gamedata->window);
    gamedata->status = STOP;
    w = width;
    h = height;
    gamedata->generalQuad = new Quad();
    if(gamedata->exported)
    {
        w = 1920;
        h = 1080;
    }
    
    glGenFramebuffers(1,&fbo);
    
    glBindFramebuffer(GL_FRAMEBUFFER, fbo); 
    glEnable(GL_DEPTH_TEST);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("ERROR\n");
    }
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    glGenFramebuffers(1,&fbo2);
    glGenTextures(1, &tex2);
    glBindTexture(GL_TEXTURE_2D, tex2);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
    unsigned int rbo2;
    glGenRenderbuffers(1, &rbo2);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo2);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w,h);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo2); 

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex2, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo2);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("ERROR\n");
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER,0);
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
float last_time = 0.0f;
int fps = 0;
const int MAX_FPS = 120;
const double maxPeriod  =1.0/double(MAX_FPS);
double lastTime = 0.0f;
double lastTimeForSleep = 0.0;
double lastTimeForSleep2 = 0.0;
const int MAX_FRAMERATE = 120;

void Game::onUpdate(double deltaTime)
{
    if(gamedata->currentLevel != NULL)
        gamedata->currentLevel->onUpdate(deltaTime);
}

void Game::render(double deltaTime)
{
    int w,h;

    glfwGetFramebufferSize(gamedata->window, &w, &h);
        glViewport(0,0,1920,1080);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);   
    glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
    glClearColor(18.0f/255, 18.0f/255, 27.0f/255, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    gamedata->shader->use();
    while(glfwGetTime()<lastTimeForSleep+double(1.0/MAX_FRAMERATE))
    {
        //No hago nada. Limito fps.
    }
    lastTimeForSleep += 1.0/MAX_FRAMERATE; 
    if(gamedata->currentLevel != NULL)
        gamedata->currentLevel->render(gamedata->shader,deltaTime);
    
    glBindFramebuffer(GL_FRAMEBUFFER, fbo2);
    //glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    glClearColor(1.0f,1.0f,1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    gamedata->shaderGeneral->use();   
    
    glBindTexture(GL_TEXTURE_2D, tex);
    //glUniform1i(pixelizationLocation, b);
    glBindVertexArray(gamedata->generalQuad->getVAO());
    if(gamedata->currentLevel != NULL)
    {
        
        for(GraphicAttribute* attr : gamedata->currentLevel->getAttributes())
        {
            attr->passToShader(gamedata->shaderGeneral, gamedata->deltaTime);
        }
        if(gamedata->currentLevel->getGammaCorrection())
        {
            GLint gammaCorrectionLocalization = glGetUniformLocation(gamedata->shaderGeneral->getShaderProgram(), "gammaCorrection");
            glUniform1i(gammaCorrectionLocalization, 1);
        }
    }
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    if(gamedata->currentLevel != NULL)
    {
        for(GraphicAttribute* attr : gamedata->currentLevel->getAttributes())
        {
            attr->unbind(gamedata->shaderGeneral);
        }
        if(gamedata->currentLevel->getGammaCorrection())
        {
            GLint gammaCorrectionLocalization = glGetUniformLocation(gamedata->shaderGeneral->getShaderProgram(), "gammaCorrection");
            glUniform1i(gammaCorrectionLocalization, 0);
        }  
    }
    gamedata->texture = tex2;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    glClearColor(18.0f/255, 18.0f/255, 27.0f/255, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if(gamedata->exported)
    {
        int nwidth, nheight;
        glfwGetFramebufferSize(gamedata->window, &nwidth, &nheight);
        //glViewport(0,0,nwidth,nheight);
        glBindTexture(GL_TEXTURE_2D, tex2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

lua_State* Game::getLuaState()
{
    return gamedata->L;
}

Level* Game::getCurrentLevel()
{
    return gamedata->currentLevel;
}

void Game::setLevel(int level)
{
    if(level>=0 && level<gamedata->levels.size())
    {
        gamedata->currentLevel=gamedata->levels.at(level);
        gamedata->levels.at(level)->createAllScripts();
    }
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
    else
    {
        gamedata->deltaTime = 0.0;
        
    
    }
    Game::render(gamedata->deltaTime);
    gamedata->deltaTime = deltaTime;
    if(!gamedata->exported)
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
    if(gamedata->status == STOP)
    {
        if(gamedata->currentLevel != NULL)
            gamedata->currentLevel->registerInitialState();
    }
       
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
    gamedata->currentLevel->recoverInitialState();
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
    gamedata->status = STOP;
    
}

double Game::getDeltaTime()
{
    return gamedata->deltaTime;
}

Shader* Game::getParticleShader()
{
    return gamedata->shaderParticles;
}

void Game::save(std::ofstream& output)
{
    output << "\"width\" : " << gamedata->width <<" , \"height\": " << gamedata->height << " , "; //Con esto puedo restaurar ventana
    //Los shaders deberían crearse automaticamente desde el codigo.
     //Ahora vienen los sprites primero porque despues busco la referencia cuando cargo los componentes
    output << "\"cant_sprites\" : " << gamedata->sprites.size() << " , ";
    output << "\"sprites\" : [ ";
    int spr_index = 0;
    for(Sprite* spr : gamedata->sprites)
    {
        output << "{";
        spr->save(output);
        output << "} ";
        if(spr_index + 1 < gamedata->sprites.size())
            output << " , ";
        spr_index++;
    }
    output << "] , ";
    output << "\"cant_niveles\" : " << gamedata->levels.size() << " , ";
    //Ahora tengo que imprimir los niveles
    output << "\"niveles\" : [ ";
    int lv_index = 0;
    for(Level* lv : gamedata->levels)
    {
        output << "{";
        lv->save(output);
        output << "} ";
        if(lv_index + 1 < gamedata->levels.size())
            output << " , ";
        lv_index++;
    } 
    output << "] , ";
    output << "\"nivel_actual\" : ";
    //Busco el indice del nivel actual para meterlo en el json
    for(int i = 0; i < gamedata->levels.size(); i++)
    {
        if(gamedata->levels.at(i) == gamedata->currentLevel)
            output << i;
    }
    //Creo que ya está todo de Game
   
}

void Game::setLuaState(lua_State* L)
{
    gamedata->L = L;
}


void Game::loadProject(std::string input_dir)
{
    std::string input_dat = file_manager::read_file(input_dir);
    printf("El contenido del archivo es: %s\n",input_dat.c_str());
    nlohmann::json json = nlohmann::json::parse(input_dat.c_str())["Game"];
    //Tengo que cargar sprites
    int cant_sprites = json["cant_sprites"];
    for(int i = 0; i < cant_sprites; i++)
    {
        nlohmann::json sprite = json["sprites"][i];
        int cant_imagenes = sprite["cant_imagenes"];
        std::string name = sprite["name"];
        std::vector<std::string> images;
        for(int j = 0; j < cant_imagenes; j++)
        {
            //Tengo que retirar los quotes
            std::string str = (sprite["imagenes"][j]).dump();
            str.erase(std::remove(str.begin(), str.end(), '"'), str.end());
            images.push_back(str);
        }
        std::vector<const char*> cstrings;
        cstrings.reserve(images.size());
        for(size_t i = 0; i < images.size(); ++i)
            cstrings.push_back(const_cast<const char*>(images[i].c_str()));
        Sprite* spr = new Sprite(&cstrings[0],cant_imagenes,name); 
        spr->setSpeed(sprite["speed"]);
        spr->setTransparency(sprite["transparency"]);
        gamedata->sprites.push_back(spr);
    }
    
    //Ahora tengo que cargar los niveles
    int cant_niveles = json["cant_niveles"];
    for(int i = 0; i < cant_niveles; i++)
    {
        nlohmann::json level = json["niveles"][i];
        Level* l = Game::addLevel();
        l->loadProject(level);
    }
    int current_level = json["nivel_actual"];
    Game::setLevel(current_level);



}

void Game::exportedGame(bool e)
{
    gamedata->exported = e;
}