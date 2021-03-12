#include "ComponentMusic.h"

ComponentMusic::ComponentMusic(irrklang::ISoundEngine* soundEngine)
{
    this->setName("music");
    this->music = " ";
    this->SoundEngine = soundEngine;
    //this = (initialState*)malloc(sizeof(initialState));
    //initialState iniState{"","",1.0};
    //this = &iniStateAux;
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
    this->volume = volume;
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
    this->initial_visibleName = this->getVisibleName().c_str();
    this->initial_track = this->music.c_str();
    this->initial_volume = this->volume;
    if(this->isPlaying)
        this->SoundEngine->play2D(this->music.c_str(),this->isLooping);
    return true;
}
bool ComponentMusic::recoverInitialState()
{
    this->setVisibleName(this->initial_visibleName);
    this->music = this->initial_track;
    this->SoundEngine->stopAllSounds();
    return true;
}

bool ComponentMusic::getLoop()
{
    return this->isLooping;
}

void ComponentMusic::setLoop(bool loop)
{
    this->isLooping = loop;
}

bool ComponentMusic::getPlaying()
{
    return this->isPlaying;
}

void ComponentMusic::setPlaying(bool playing)
{
    this->isPlaying = playing;
}
