#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <functional>

#include "sprite.hpp"
#include "sprite_builder.hpp"
#include "texture_manager.hpp"
#include "vector_2d.hpp"

#include "grid_cell.hpp"

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