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
    printf("La nueva direccion es: %s\n",this->music.c_str());
}

std::string ComponentMusic::getMusic()
{
    printf("La direccion actual es: %s\n",this->music.c_str());
    return this->music;
}

void ComponentMusic::playMusic(bool loop)
{
    this->SoundEngine->play2D(this->music.c_str(), loop);
}   

void ComponentMusic::stopMusic()
{
    this->SoundEngine->stopAllSounds();
}

void ComponentMusic::pauseMusic()
{
    this->SoundEngine->setAllSoundsPaused(true);
}

void ComponentMusic::setVolume(float volume)
{
    if(volume<=1.0f && volume >=0.0f)
        this->SoundEngine->setSoundVolume(volume);
}


