#pragma once
#include "Component.h"
#include "irrklang/include/irrKlang.h"
class ComponentMusic : public Component
{
    public:
    ComponentMusic(irrklang::ISoundEngine* soundEngine);
    ~ComponentMusic();
    void onCreate();
    void onUpdate();
    Component* copy();
    void setMusic(std::string dir);
    std::string getMusic();
    void playMusic();
    void stopMusic();
    void pauseMusic();
    void setVolume(float volume);

    private:
    std::string music;
    irrklang::ISoundEngine *SoundEngine;
};