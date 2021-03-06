#include "ComponentMusic.h"

ComponentMusic::ComponentMusic(irrklang::ISoundEngine* soundEngine)
{
    this->setName("music");
    this->SoundEngine = soundEngine;
}

ComponentMusic::~ComponentMusic()
{
    
}

void ComponentMusic::onCreate()
{

}

void ComponentMusic::onUpdate()
{

}

Component* ComponentMusic::copy()
{
    return new ComponentMusic(this->SoundEngine);
}

void ComponentMusic::setMusic(std::string dir)
{
    this->music = dir;
}

std::string ComponentMusic::getMusic()
{
    return this->music;
}

void ComponentMusic::playMusic()
{
    this->SoundEngine->play2D(this->music.c_str(), true);
}   

void ComponentMusic::stopMusic()
{
    this->SoundEngine->stopAllSounds();
}

void ComponentMusic::pauseMusic()
{
    this->SoundEngine->setAllSoundsPaused(true);
}


