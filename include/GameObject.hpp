#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <functional>

#include "graphics/sprite/Sprite.hpp"
#include "graphics/sprite/SpriteBuilder.hpp"
#include "graphics/TextureManager.hpp"
#include "math/Vector2D.hpp"
#include "grid/GridCell.hpp"

class GridCell;

class GameObject
{
private:
    Sprite* m_sprite;

    GridCell* m_currentGridCell;

public:
    GameObject(GridCell* currentGridCell);
    ~GameObject();

    void buildSprite(std::function<void(Sprite** sprite)> func);

    void update();
    void render(SDL_Renderer* renderer);

    void move(Direction direction);
};

#endif