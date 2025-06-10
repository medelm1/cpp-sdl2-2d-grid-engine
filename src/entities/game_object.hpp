#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>

#include "../systems/sprite-animation/sprite.hpp"
#include "../systems/sprite-animation/sprite_builder.hpp"
#include "../systems/texture/texture_manager.hpp"
#include "../utils/vector_2d.hpp"

class GameObject
{
private:
    Sprite* m_sprite;

public:
    GameObject();
    ~GameObject();

    void update();

    void render(SDL_Renderer* renderer, const Vector2D& currentPosition);
};

#endif