#include "ComponentMusic.h"

ComponentMusic::ComponentMusic(irrklang::ISoundEngine* soundEngine)
{
    this->setName("music");
    this->music = " ";
    this->SoundEngine = soundEngine;
    this->iniState = (initialState*)malloc(sizeof(initialState));
}

ComponentMusic::~ComponentMusic()
{
    free(this->iniState);
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

void ComponentMusic::save(std::ofstream& output)
{
    output << "\"name\" : \"" << this->getName() << "\" , ";
    output << "\"visible_name\" : \"" << this->getVisibleName() << "\" , ";
    output << "\"track\" : \"" << this->music << "\"";
}

bool ComponentMusic::registerInitialState()
{
    printf("Music\n");
    this->iniState->initial_visibleName = this->getVisibleName().c_str();
    printf("Music1\n");
    this->iniState->initial_track = this->music.c_str();
    printf("Music2\n");
    //this->iniState->initial_volume = this->volume;
    return true;
}
bool ComponentMusic::recoverInitialState()
{
    this->setVisibleName(this->iniState->initial_visibleName);
    this->music = this->iniState->initial_track;
    return true;
}
