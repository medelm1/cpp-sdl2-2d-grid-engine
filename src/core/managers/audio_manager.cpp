#include "audio_manager.hpp"

AudioManager* AudioManager::instance = nullptr;

AudioManager::AudioManager()
    :
    Manager::Manager()
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

AudioManager::~AudioManager()
{
    for (auto& effect : effects)
    {
        Mix_FreeChunk(effect.second);
    }
    effects.clear();

    // Free music resources here if MUSIC type is implemented.
}

AudioManager& AudioManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new AudioManager();
    }

    return *instance;
}

void AudioManager::load(const std::string& filename, const std::string& key, AudioManager::Type type)
{
    if (initialized)
    {
        if (type == AudioManager::Type::EFFECT)
        {
            Mix_Chunk* effect = Mix_LoadWAV(filename.c_str());

            if (effect == nullptr)
            {
                std::cerr << "Error: Failed to load audio file '" << filename << "' for key '" 
                          << key << "' as an effect. "
                          << "Reason: " << Mix_GetError() << std::endl;
                gameCtx->quit();
                return;
            }
            effects[key] = effect;

        } 
        else if (type == AudioManager::Type::MUSIC)
        {
            // Load music here (to be implemented later)
            std::cerr << "Error: MUSIC type loading is not implemented yet for file '" 
                    << filename << "' and key '" << key << "'." << std::endl;
        }
    }
    else
    {
        std::cerr << "AudioManager Error: Not initialized" << std::endl;
    }  
}

void AudioManager::play(const std::string& key)
{
    if (initialized)
    {
        if (Mix_Playing(-1))
        {
            std::cout << "AudioManager: A sound is already playing. Skipping '" << key << "'." << std::endl;
            return;
        }

        // Search & play effect
        auto it = effects.find(key);

        if (it == effects.end())
        {
            std::cerr << "Error: Audio effect with key '" << key 
                      << "' not found. Ensure the effect is loaded before attempting to play." 
                      << std::endl;
            gameCtx->quit();
            return;
        }

        if (Mix_PlayChannel(-1, it->second, 0) == -1)
        {
            std::cerr << "Error: Failed to play audio effect with key '" << key << "'. "
                      << "Reason: " << Mix_GetError() << std::endl;
            gameCtx->quit();
            return;
        }

        // Search & play music (to be implemented later)
    }
    else
    {
        std::cerr << "AudioManager Error: Not initialized" << std::endl;
    }
}