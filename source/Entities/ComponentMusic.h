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
    void playMusic(bool loop);
    void stopMusic();
    void pauseMusic();
    void setVolume(float volume);
    void save(std::ofstream& output_dir);

    private:
    std::string music;
    irrklang::ISoundEngine *SoundEngine;
};