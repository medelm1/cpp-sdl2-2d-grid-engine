#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include "game_interface.hpp"
#include "loop_mode.hpp"

class AudioManager
{
private:
    static AudioManager* instance;

    IGame* gameCtx;
    bool initialized = false;

    std::map<std::string, Mix_Chunk*> sounds;
    std::map<std::string, Mix_Music*> tracks;

    std::unordered_map<std::string, int> channels;

    const int MAX_CHANNELS = 8;

private:
    AudioManager();
    ~AudioManager();

    bool requireInitialization() const;

public:
    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;

    void init(IGame* gameContext);

    static AudioManager& getInstance();

    // Sound Effects (SFX)
    void loadSound(const std::string& key, const std::string& filepath);
    void playSound(const std::string& key, const std::string& channelLabel, LoopMode lm);
    void stopSound(const std::string& channelLabel);
    void stopSound(int channelIndex);
    void stopAllSounds();
    bool isSoundPlaying(const std::string& channelLabel) const;

    // Sound Effects : Channel management
    void addChannel(const std::string& channelLabel);

    // Music Control
    void loadMusic(const std::string& key, const std::string& filepath);
    void playMusic(const std::string& key, LoopMode lm = LoopMode::INFINITE);
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    bool isMusicPlaying() const;
    bool isMusicPaused() const;

    void cleanup(); // Free music + sounds, quit SDL_mixer
};

#endif