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
    bool registerInitialState();
    bool recoverInitialState();
    bool getLoop();
    bool getPlaying();
    void setLoop(bool loop);
    void setPlaying(bool playing);
    private:
    std::string music;
    irrklang::ISoundEngine *SoundEngine;
    std::string initial_visibleName;
    std::string initial_track;
    float initial_volume;

    float volume = 1.0f;
    bool isPlaying = false;
    bool isLooping = false;

};