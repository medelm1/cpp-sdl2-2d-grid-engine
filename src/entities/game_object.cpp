#include "game_object.hpp"

GameObject::GameObject()
{
    m_sprite = SpriteBuilder(TextureManager::getInstance().getTexture("bee"), GridSize{3, 4})
        .withScale(Scale{1, 1})
        .enableBoundingBox(false)
        .setUniformFrameSize(Size{32, 32})
        .setUniformFrameDuration(90)
        .addAnimation("flying_up", {0, 1, 2})
        .addAnimation("flying_left", {3, 4, 5})
        .addAnimation("flying_down", {6, 7, 8})
        .addAnimation("flying_right", {9, 10, 11})
        .build();

    m_sprite->playAnimation("flying_down");
}

GameObject::~GameObject()
{
    
}

void GameObject::update()
{
    if (m_sprite)
    {
        m_sprite->update();
    }
}

void GameObject::render(SDL_Renderer* renderer, const Vector2D& currentPosition)
{
    if (m_sprite)
    {
        m_sprite->render(renderer, currentPosition);
    }
}