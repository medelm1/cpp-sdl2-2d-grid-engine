#include "graphics/sprite/Sprite.hpp"

Sprite::Sprite(SDL_Texture* texture, GridSize sheetSize, Scale scale, bool boundingBoxEnabled)
    :
    m_texture(texture),
    m_sheetSize(sheetSize),
    m_scale(scale),
    m_boundingBoxEnabled(boundingBoxEnabled)
{
    m_animationController = new AnimationController(sheetSize);
}

bool Sprite::isBoundingBoxEnabled() const
{
    return m_boundingBoxEnabled;
}

void Sprite::setBoundingBoxEnabled(bool enabled)
{
    m_boundingBoxEnabled = enabled;
}

void Sprite::render(SDL_Renderer* renderer, Vector2D position)
{
    if (m_texture == nullptr) return;

    Frame* currentFrame = m_animationController->getCurrentFrame();

    // Set the src & dest rects dimentions
    m_boundingRect.w = m_srcRect.w = currentFrame->getSize().getWidth();
    m_boundingRect.h = m_srcRect.h = currentFrame->getSize().getHeight();

    // Scale sprite (to implement later)

    // Set src rect position (in texture)
    m_srcRect.x = currentFrame->getCoordinate().getCol() * currentFrame->getSize().getWidth();
    m_srcRect.y = currentFrame->getCoordinate().getRow() * currentFrame->getSize().getHeight();

    // Set dest rect position (in window) with offset
    m_boundingRect.x = position.getX();
    m_boundingRect.y = position.getY();

    SDL_RenderCopy(renderer, m_texture, &m_srcRect, &m_boundingRect);

    // Draw bouding rect
    if (m_boundingBoxEnabled)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawRect(renderer, &m_boundingRect);
    }
}

AnimationController* Sprite::getAnimationController()
{
    return m_animationController;
}

void Sprite::update()
{
    m_animationController->updateCurrentAnimation();
}

Scale Sprite::getScale() const
{
    return m_scale;
}

void Sprite::setScale(Scale scale)
{
    m_scale = scale;
}

void Sprite::playAnimation(const std::string& animationName)
{
    m_animationController->play(animationName);
}

void Sprite::pauseAnimation()
{
    m_animationController->pause();
}

void Sprite::resumeAnimation()
{
    m_animationController->resume();
}

void Sprite::stopAnimation()
{
    
}