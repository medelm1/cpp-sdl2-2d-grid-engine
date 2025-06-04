#include "text_renderer.hpp"

TextRenderer* TextRenderer::instance = nullptr;

TextRenderer::TextRenderer()
{

}

TextRenderer::~TextRenderer()
{
    for (auto& pair : fontcache)
    {
        if (pair.second)
        {
            TTF_CloseFont(pair.second);
        }
    }
    TTF_Quit();
}

TextRenderer& TextRenderer::getInstance()
{
    if (instance == nullptr)
    {
        instance = new TextRenderer();
    }
    return *instance;
}

void TextRenderer::init(IGame* initGameCtx, const std::string& initFontpath)
{
    gameCtx = initGameCtx;
    fontpath = initFontpath;

    if (gameCtx == nullptr)
    {
        std::cerr << "[TextRenderer] Error: Game context not initialized." << std::endl;
        return;
    }

    if (fontpath.empty())
    {
        std::cerr << "[TextRenderer] Error: Font path is empty." << std::endl;
        return;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "[TextRenderer] TTF_Init Error: " << TTF_GetError() << std::endl;
        return;
    }

    initialized = true;
}

void TextRenderer::render(
    const std::string& text,
    TTF_Font* font,
    size_t fontsize,
    int x,
    int y,
    SDL_Renderer* renderer,
    SDL_Color fontcolor
)
{
    if (!initialized)
    {
        std::cerr << "[TextRenderer] Error: Not initialized" << std::endl;
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), fontcolor);

    if (!textSurface)
    {
        std::cerr << "[TextRenderer] TTF_RenderText_Blended Error: " << TTF_GetError() << std::endl;
        gameCtx->quit();
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    if (!textTexture)
    {
        std::cerr << "[TextRenderer] SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        gameCtx->quit();
        return;
    }

    SDL_Rect rect = {x, y, 0, 0};
    SDL_QueryTexture(textTexture, nullptr, nullptr, &rect.w, &rect.h);

    SDL_RenderCopy(renderer, textTexture, nullptr, &rect);
    SDL_DestroyTexture(textTexture);
}

void TextRenderer::write(
    const std::string& text,
    size_t fontsize,
    int x,
    int y,
    SDL_Renderer* renderer,
    SDL_Color fontcolor,
    SDL_Color shadowcolor
)
{
    if (!initialized)
    {
        std::cerr << "[TextRenderer] Error: Not initialized" << std::endl;
        return;
    }

    // Check if the font with the requested size is already cached
    TTF_Font* font = nullptr;

    if (fontcache.find(fontsize) == fontcache.end())
    {
        font = TTF_OpenFont(fontpath.c_str(), fontsize);
        if (!font)
        {
            std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
            gameCtx->quit();
            return;
        }
        fontcache[fontsize] = font;
    }
    else
    {
        font = fontcache[fontsize];
    }

    // Render shadow
    render(text, font, fontsize, x-1, y+1, renderer, shadowcolor);

    // Render text
    render(text, font, fontsize, x, y, renderer, fontcolor);
}