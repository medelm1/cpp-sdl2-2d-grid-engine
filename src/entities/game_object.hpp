#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <functional>

#include "../systems/sprite-animation/sprite.hpp"
#include "../systems/sprite-animation/sprite_builder.hpp"
#include "../systems/texture/texture_manager.hpp"
#include "../utils/vector_2d.hpp"

#include "../systems/grid/grid_cell.hpp"

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