#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <map>
#include <vector>
#include <string>

#include "animation_controller.hpp"
#include "../common/grid_size.hpp"
#include "../common/scale.hpp"
#include "../../utils/vector_2d.hpp"

class Sprite
{
private:
    SDL_Texture* m_texture;
    
    GridSize m_sheetSize;
    Scale m_scale;
    SDL_Rect m_srcRect;

    AnimationController* m_animationController;

    std::map<int, std::pair<int, int>> framesMap;

    bool m_boundingBoxEnabled;
    SDL_Rect m_boundingRect;

private:
    void init();

public:
    Sprite(
        SDL_Texture* texture,
        GridSize sheetSize,
        Scale scale, 
        bool boundingBoxEnabled
    );
    ~Sprite();

    bool isBoundingBoxEnabled() const;
    void setBoundingBoxEnabled(bool enabled);

    Scale getScale() const;
    void setScale(Scale scale);

    AnimationController* getAnimationController();

    void playAnimation(const std::string& animationName);
    void pauseAnimation();
    void resumeAnimation();
    void stopAnimation();

    void render(SDL_Renderer* renderer, Vector2D position);

    void update();
};

#endif