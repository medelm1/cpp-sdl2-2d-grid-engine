#include "graphics/texture_manager.hpp"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager()
    :
    m_initialized(false), m_renderer(nullptr)
{

}

TextureManager::~TextureManager()
{
    // Clean up texture
    for (auto& [_, texture] : m_textures)
    {
        SDL_DestroyTexture(texture);
    }
    m_textures.clear();
}

TextureManager& TextureManager::getInstance()
{
    // Make sure to create the instance only once
    if (instance == nullptr)
    {
        instance = new TextureManager();
    }

    return *instance;
}

void TextureManager::init(SDL_Renderer* renderer)
{
    m_renderer = renderer;

    if (!m_renderer)
    {
        std::cerr << "[TextureManager] error: SDL_Renderer not initialized." << std::endl;
        return;
    }

    if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_JPG | IMG_INIT_JPG)) == 0)
    {
        std::cerr << "Error: SDL_image initialization failed. IMG Error: " << IMG_GetError() <<  std::endl;
        return;
    }

    m_initialized = true;
}

bool TextureManager::requireInitialization() const
{
    if (!m_initialized)
    {
        std::cerr << "[TextureManager] Error: TextureManager not initialized. Call init() first" << std::endl;
        return false;
    }
    return true;
}

void TextureManager::load(const std::string& label, const std::string& filename)
{
    if (!requireInitialization()) return;

    // Skip loading if texture already exists
    if (m_textures.find(label) != m_textures.end())
    {
        std::cerr << "[TextureManager] Warning: A texture with the label '" << label << "' is already loaded. "
        << "Use a unique label or unload the existing texture first." << std::endl;
        
        return;    
    }

    SDL_Surface* tmpSurface = IMG_Load(filename.c_str());

    if (tmpSurface == nullptr)
    {
        std::cerr << "[TextureManager] Error: Failed to load image file '" << filename << "' using SDL_image. "
            << "Reason: " << IMG_GetError() << std::endl;
        
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    if (texture == nullptr)
    {
        std::cerr << "[TextureManager] Error: Failed to create texture from surface for file '" << filename << "'. "
            << "Reason: " << SDL_GetError() << std::endl;
        
        return;
    }

    m_textures[label] = texture;
}

void TextureManager::unload(const std::string& label)
{
    auto it = m_textures.find(label);

    if (it == m_textures.end())
    {  
        std::cerr << "[TextureManager] Warning: Cannot unload texture. Label '" << label << "' not found." << std::endl;
        
        return;
    }

    SDL_DestroyTexture(it->second);
    m_textures.erase(it->first);

}

void TextureManager::unloadAll()
{
    for (auto [_, texture] : m_textures)
    {
        SDL_DestroyTexture(texture);
    }
    m_textures.clear();
}

SDL_Texture* TextureManager::getTexture(const std::string& label)
{
    if (!requireInitialization()) return nullptr;

    auto it = m_textures.find(label);

    if (it == m_textures.end())
    {
        std::cerr << "Error: Texture with label '" << label << "' not found" << std::endl;
        return nullptr;
    }

    return it->second;
}