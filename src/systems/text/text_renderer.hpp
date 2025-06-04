#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>
#include <iostream>

#include "../../game/game_interface.hpp"

class TextRenderer
{
private:
    static TextRenderer* instance;

    std::unordered_map<size_t, TTF_Font*> fontcache;
    std::string fontpath;

    IGame* gameCtx;
    bool initialized = false;

private:
    TextRenderer();
    ~TextRenderer();

    void render(
        const std::string& text,
        TTF_Font* font,
        size_t fontsize,
        int x,
        int y,
        SDL_Renderer* renderer,
        SDL_Color fontcolor
    );

public:
    TextRenderer(const TextRenderer&) = delete;
    TextRenderer& operator=(const TextRenderer&) = delete;

    static TextRenderer& getInstance();

    void init(IGame* initGameCtx, const std::string& initFontpath);

    void write(
        const std::string& text,
        size_t fontsize,
        int x,
        int y,
        SDL_Renderer* renderer,
        SDL_Color fontcolor = {0xFF, 0xFF, 0xFF, 0xFF},
        SDL_Color shadowcolor = {0xFF, 0xFF, 0xFF, 0xFF}
    );
};

#endif