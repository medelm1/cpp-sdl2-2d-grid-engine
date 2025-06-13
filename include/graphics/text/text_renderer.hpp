#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "game_interface.hpp"
#include "graphics/text/text_object.hpp"
#include "math/vector_2d.hpp"

class TextRenderer
{
private:
    static TextRenderer* instance;

    std::unordered_map<size_t, TTF_Font*> m_fontcache;
    std::string m_fontpath;

    SDL_Renderer* m_renderer;

    bool m_initialized = false;

private:
    TextRenderer();
    ~TextRenderer();

    bool requireInitialization() const;

    TTF_Font* getCachedFrontOrLoad(int fontsize);

public:
    TextRenderer(const TextRenderer&) = delete;
    TextRenderer& operator=(const TextRenderer&) = delete;

    static TextRenderer& getInstance();

    void init(SDL_Renderer* renderer, const std::string& fontpath);

    void render(TextObject text, Vector2D position);
    void renderAll(const std::vector<TextObject> texts, Vector2D position, Vector2D offset);
};

#endif