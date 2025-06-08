#include "sprite.hpp"

Sprite::Sprite(SDL_Texture* texture, GridSize sheetSize, Scale scale, bool boundingBoxEnabled)
    :
    m_texture(texture),
    m_sheetSize(sheetSize),
    m_scale(scale),
    m_boundingBoxEnabled(boundingBoxEnabled)
{
    init();

    m_animationController = new AnimationController(sheetSize);

    Frame* frame0 = m_animationController->getFrame(0);
    frame0->setSize(Size{32, 32}); 
    frame0->setDuration(100);

    // m_animationController->addAnimation(
    //     "walking_down",
    //     {
    //         Frame(0, Size{32, 32}, 100),
    //         Frame(1, Size{32, 32}, 100),
    //         Frame(3, Size{32, 32}, 100),
    //         Frame(4, Size{32, 32}, 100)
    //     }
    // );
    // m_animationController->addAnimation(
    //     "walking_up",
    //     {
    //         Frame(4, Size{32, 32}, 100),
    //         Frame(5, Size{32, 32}, 100),
    //         Frame(6, Size{32, 32}, 100),
    //         Frame(7, Size{32, 32}, 100)
    //     }
    // );
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

    Frame* activeFrame = m_animationController->getActiveFrame();

    // Set the src & dest rects dimentions
    m_boundingRect.w = m_srcRect.w = activeFrame->getSize().getWidth();
    m_boundingRect.h = m_srcRect.h = activeFrame->getSize().getHeight();

    // Scale sprite (to implement later)

    // Set src rect position (in texture)
    m_srcRect.x = activeFrame->getCoordinate().getCol() * activeFrame->getSize().getWidth();
    m_srcRect.y = activeFrame->getCoordinate().getRow() * activeFrame->getSize().getHeight();

    // Set dest rect position (in window) with offset
    m_boundingRect.x = position.getX() * activeFrame->getSize().getWidth();
    m_boundingRect.y = position.getY() * activeFrame->getSize().getHeight();

    SDL_RenderCopy(renderer, m_texture, &m_srcRect, &m_boundingRect);

    // Draw bouding rect
    if (m_boundingBoxEnabled)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawRect(renderer, &m_boundingRect);
    }
}

void Sprite::update()
{

}