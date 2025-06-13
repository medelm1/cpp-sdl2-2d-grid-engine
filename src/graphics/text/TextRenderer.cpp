#include "graphics/text/TextRenderer.hpp"

TextRenderer* TextRenderer::instance = nullptr;

TextRenderer::TextRenderer()
{

}

TextRenderer::~TextRenderer()
{
    for (auto& pair : m_fontcache)
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

void TextRenderer::init(SDL_Renderer* renderer, const std::string& fontpath)
{
    if (m_initialized) return;

    m_renderer = renderer;
    m_fontpath = fontpath;

    if (m_renderer == nullptr)
    {
        std::cerr << "[TextRenderer] Error: SDL renderer not initialized." << std::endl;
        return;
    }

    if (m_fontpath.empty())
    {
        std::cerr << "[TextRenderer] Error: Font path is empty." << std::endl;
        return;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "[TextRenderer] TTF_Init Error: " << TTF_GetError() << std::endl;
        return;
    }

    m_initialized = true;
}

bool TextRenderer::requireInitialization() const
{
    if (!m_initialized)
    {
        std::cerr << "[TextRenderer] Error: TextRenderer not initialized. Call init() first" << std::endl;
        return false;
    }
    return true;
}

TTF_Font* TextRenderer::getCachedFrontOrLoad(int fontsize)
{
    if (m_fontcache.find(fontsize) == m_fontcache.end())
    {
        TTF_Font* font = TTF_OpenFont(m_fontpath.c_str(), fontsize);

        if (!font)
        {
            std::cerr << "[TextRenderer] TTF_OpenFont Error: " << TTF_GetError() << std::endl;
            return nullptr;
        }
        m_fontcache[fontsize] = font;

        return font;
    }
    else
    {
        return m_fontcache[fontsize];
    }
}

void TextRenderer::render(TextObject text, Vector2D position)
{
    requireInitialization();

    TTF_Font* font = getCachedFrontOrLoad(text.getStyle().getFontsize());
    if (!font) return;

    // Render both the main text and its shadow:
    // The shadow is slightly offset to give a depth effect, improving readability.
    // Both are created as textures from surfaces, then drawn in order: shadow first, then text.

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.getText().c_str(), text.getStyle().getTextColor());
    SDL_Surface* shadowSurface = TTF_RenderText_Blended(font, text.getText().c_str(), text.getStyle().getShadowColor());

    if (!textSurface || !shadowSurface)
    {
        std::cerr << "[TextRenderer] TTF_RenderText_Blended Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    SDL_Texture* shadowTexture = SDL_CreateTextureFromSurface(m_renderer, shadowSurface);
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(shadowSurface);

    if (!textTexture || !shadowTexture)
    {
        std::cerr << "[TextRenderer] SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect textRect = {(int)position.getX(), (int)position.getY(), 0, 0};
    SDL_Rect shadowRect = {(int)position.getX()-1, (int)position.getY()+1, 0, 0};

    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
    SDL_QueryTexture(shadowTexture, nullptr, nullptr, &shadowRect.w, &shadowRect.h);

    SDL_RenderCopy(m_renderer, shadowTexture, nullptr, &shadowRect);
    SDL_RenderCopy(m_renderer, textTexture, nullptr, &textRect);

    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(shadowTexture);
}

void TextRenderer::renderAll(const std::vector<TextObject> texts, Vector2D position, Vector2D offset)
{
    int itemCount = 0;

    for (auto& text : texts)
    {
        render(text, position + offset*itemCount);
        itemCount++;
    }
}