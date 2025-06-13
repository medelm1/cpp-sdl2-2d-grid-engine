#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <functional>

#include "graphics/sprite/sprite.hpp"
#include "graphics/sprite/sprite_builder.hpp"
#include "graphics/texture_manager.hpp"
#include "math/vector_2d.hpp"

#include "grid/grid_cell.hpp"

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