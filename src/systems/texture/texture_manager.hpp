#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <string>
#include <iostream>

#include "../../game/game_interface.hpp"

class TextureManager
{
private:
    static TextureManager* instance;

    std::map<std::string, SDL_Texture*> m_textures;
    SDL_Renderer* m_renderer;
    bool m_initialized;

private:
    TextureManager();
    ~TextureManager();

    bool requireInitialization() const; 

public:
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    static TextureManager& getInstance();

    void init(SDL_Renderer* renderer);

    void load(const std::string& label, const std::string& filename);
    void unload(const std::string& label);
    void unloadAll();
    
    SDL_Texture* getTexture(const std::string& label);

};

#endif