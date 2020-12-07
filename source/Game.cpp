#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

int Game::addLevel(Level* level)
{
    this->levels.push_back(level);
    return this->levels.size()-1;
}

void Game::onUpdate()
{
    this->currentLevel->onUpdate();
}

void Game::render(Shader* shader,double deltaTime)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    this->currentLevel->render(shader,deltaTime);
}

Level* Game::getCurrentLevel()
{
    return this->currentLevel;
}

void Game::setLevel(int level)
{
    this->currentLevel=this->levels.at(level);
}