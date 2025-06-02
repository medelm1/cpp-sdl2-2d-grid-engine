#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SDL_mixer.h>
#include <string>
#include <map>
#include <iostream>
#include "manager.hpp"

class AudioManager : public Manager
{
public:
    enum Type
    {
        EFFECT,
        MUSIC
    };

private:
    static AudioManager* instance;
    std::map<std::string, Mix_Chunk*> effects;

private:
    AudioManager();
    ~AudioManager();

public:
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    static AudioManager& getInstance();

    void load(const std::string& filename, const std::string& key, AudioManager::Type type = AudioManager::Type::EFFECT);
    void play(const std::string& key);
};

#endif