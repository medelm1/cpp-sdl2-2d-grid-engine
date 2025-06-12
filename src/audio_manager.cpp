#include "audio_manager.hpp"

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager()
{
    
}

AudioManager::~AudioManager()
{
    cleanup();
}

void AudioManager::init(IGame* gameContext)
{
    gameCtx = gameContext;

    if (gameCtx == nullptr)
    {
        std::cerr << "[AudioManager] Error: Game context not initialized." << std::endl;
        return;
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_AllocateChannels(MAX_CHANNELS);

    initialized = true;
}

bool AudioManager::requireInitialization() const
{
    if (!initialized)
    {
        std::cerr << "[AudioManager] Error: AudioManager not initialized. Call init() first." << std::endl;
        return false;
    }
    return true;
}

void AudioManager::addChannel(const std::string& label)
{
    if (!requireInitialization()) return;

    if (channels.find(label) != channels.end())
    {
        std::cerr << "[AudioManager] Warning: Channel with label '" << label << "' already exists." << std::endl;
        return;
    }

    std::unordered_set<int> usedIndices;
    for (const auto& [_, index] : channels)
    {
        usedIndices.insert(index);
    }

    for (int idx = 0; idx < MAX_CHANNELS; ++idx)
    {
        if (usedIndices.find(idx) == usedIndices.end())
        {
            channels[label] = idx;
            return;
        }
    }

    std::cerr << "[AudioManager] Error: Cannot add channel '" << label
              << "'. Maximum of " << MAX_CHANNELS << " channels reached." << std::endl;
}

AudioManager& AudioManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new AudioManager();
    }

    return *instance;
}

void AudioManager::loadSound(const std::string& key, const std::string& filepath)
{
    if (!requireInitialization()) return;

    if (sounds.find(key) != sounds.end())
    {
        std::cerr << "[AudioManager] Warning: Key '" << key << "' already exists. Skipping load." << std::endl;
        return;
    }

    Mix_Chunk* sound = Mix_LoadWAV(filepath.c_str());

    if (sound == nullptr)
    {
        std::cerr << "[AudioManager] Error: Failed to load audio file '" << filepath << "' for key '" 
                    << key << "' as a sound. "
                    << "Reason: " << Mix_GetError() << std::endl;
        gameCtx->quit();
        return;
    }
    sounds[key] = sound;
}

void AudioManager::playSound(const std::string& key, const std::string& channelLabel, LoopMode lm)
{
    if (!requireInitialization()) return;

    // Attempt to find the specified channel by its label
    auto channel = channels.find(channelLabel);
    if (channel == channels.end())
    {
        std::cerr << "[AudioManager] Error: Channel with label '" << channelLabel << "' not found." << std::endl;
        gameCtx->quit();
        return;
    }

    // Attempt to find the sound effect by its key
    auto sound = sounds.find(key);
    if (sound == sounds.end())
    {
        std::cerr << "[AudioManager] Error: SFX with key '" << key 
                    << "' not found. Ensure the effect is loaded before attempting to play." 
                    << std::endl;
        gameCtx->quit();
        return;
    }

    // Retrieve the index of the channel and loop mode
    int channelIndex = static_cast<int>(channel->second);
    int loopMode = static_cast<int>(lm);

    // Free the channel if it is currently playing another sound
    stopSound(channel->second);

    // Attempt to play the sound effect on the specified channel
    if (Mix_PlayChannel(channelIndex, sound->second, loopMode) != channelIndex)
    {
        std::cerr << "[AudioManager] Error: Failed to play audio effect with key '" << key << "'. "
                    << "Reason: " << Mix_GetError() << std::endl;
        gameCtx->quit();
        return;
    }
}

void AudioManager::stopSound(const std::string& channelLabel)
{
    if (!requireInitialization()) return;

    auto channel = channels.find(channelLabel);

    if (channel == channels.end())
    {
        std::cerr << "[AudioManager] Warining: Channel '" << channelLabel << "' not found." << std::endl;
        return;
    }

    Mix_HaltChannel(channel->second);
}

void AudioManager::stopSound(int channelIndex)
{
    if (!requireInitialization()) return;

    if (Mix_Playing(channelIndex))
    {
        Mix_HaltChannel(channelIndex);
    }
}

void AudioManager::stopAllSounds()
{
    if (!requireInitialization()) return;

    if (Mix_Playing(-1))
    {
        Mix_HaltChannel(-1);
    }
}

bool AudioManager::isSoundPlaying(const std::string& channelLabel) const
{
    if (!requireInitialization()) return false;

    auto channel = channels.find(channelLabel);

    if (channel == channels.end())
    {
        std::cerr << "[AudioManager] Warining: Channel '" << channelLabel << "' not found." << std::endl;
        return false;
    }

    return Mix_Playing(channel->second) != 0;
}

void AudioManager::loadMusic(const std::string& key, const std::string& filepath)
{
    if (!requireInitialization()) return;

    if (tracks.find(key) != tracks.end())
    {
        std::cerr << "[AudioManager] Warning: Key '" << key << "' already exists. Skipping load." << std::endl;
        return;
    }

    Mix_Music* track = Mix_LoadMUS(filepath.c_str());

    if (track == nullptr)
    {
        std::cerr << "[AudioManager] Error: Failed to load audio file '" << filepath << "' for key '" 
                    << key << "' as a music track. "
                    << "Reason: " << Mix_GetError() << std::endl;
        gameCtx->quit();
        return;
    }
    tracks[key] = track;
}

void AudioManager::playMusic(const std::string& key, LoopMode lm)
{
    if (!requireInitialization()) return;

    // Find the music track
    auto track = tracks.find(key);
    if (track == tracks.end())
    {
        std::cerr << "[AudioManager] Error: Music track with key '" << key 
                  << "' not found. Ensure it is loaded before attempting to play." << std::endl;
        gameCtx->quit();
        return;
    }

    // Check if music is already playing and stop it
    stopMusic();

    int loopMode = static_cast<int>(lm);

    if (Mix_PlayMusic(track->second, loopMode) == -1)
    {
        std::cerr << "[AudioManager] Error: Failed to play music with key '" << key
                  << "'. Reason: " << Mix_GetError() << std::endl;
        gameCtx->quit();
        return;
    }
}

void AudioManager::pauseMusic()
{
    if (!requireInitialization()) return;

    if (isMusicPlaying())
    {
        Mix_PauseMusic();
    }
}

void AudioManager::resumeMusic()
{
    if (!requireInitialization()) return;

    if (isMusicPaused())
    {
        Mix_ResumeMusic();
    }
}

void AudioManager::stopMusic()
{
    if (!requireInitialization()) return;

    if (isMusicPlaying())
    {
        Mix_HaltMusic(); // stop current music
    }
}

bool AudioManager::isMusicPlaying() const
{
    if (!requireInitialization()) return false;

    return Mix_PlayingMusic();
}

bool AudioManager::isMusicPaused() const
{
    if (!requireInitialization()) return false;

    return Mix_PausedMusic();
}

void AudioManager::cleanup()
{
    if (!requireInitialization()) return;

    // Free all loaded sound effects
    for (auto& [_, sound] : sounds)
    {
        Mix_FreeChunk(sound);
    }
    sounds.clear();

    // Free all loaded music tracks
    for (auto& [_, track] : tracks)
    {
        Mix_FreeMusic(track);
    }
    tracks.clear();

    // Clear channel map
    channels.clear();

    // Cloase SDL_mixer
    Mix_CloseAudio();
    Mix_Quit();

    std::cout << "[AudioManager] Cleaned up all audio resources." << std::endl;
}