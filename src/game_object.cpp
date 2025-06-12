#include "game_object.hpp"

GameObject::GameObject(GridCell* currentGridCell)
    :
    m_currentGridCell(currentGridCell)
{
    
}

GameObject::~GameObject()
{
    
}

void GameObject::buildSprite(std::function<void(Sprite** sprite)> func)
{
    func(&m_sprite);
}

void GameObject::move(Direction direction)
{
    if (!m_currentGridCell) return;

    switch (direction)
    {
        case Direction::DIRECTION_UP:
        case Direction::DIRECTION_DOWN:
        case Direction::DIRECTION_LEFT:
        case Direction::DIRECTION_RIGHT:
            if (m_currentGridCell->hasNeighbor(direction))
            {
                m_currentGridCell = m_currentGridCell->getNextNeighbor(direction);
            }
            break;

        default:
            break;
    }
}


void GameObject::update()
{
    if (m_sprite)
    {
        m_sprite->update();
    }
}

void GameObject::render(SDL_Renderer* renderer)
{
    if (m_sprite && m_currentGridCell)
    {
        m_sprite->render(renderer, m_currentGridCell->getPixels());
    }
}