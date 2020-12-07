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

void Game::render()
{
    this->currentLevel->render();
}

Level* Game::getCurrentLevel()
{
    return this->currentLevel;
}

void Game::setLevel(int level)
{
    this->currentLevel=this->levels.at(level);
}