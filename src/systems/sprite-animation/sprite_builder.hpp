#ifndef SPRITE_BUILDER_H
#define SPRITE_BUILDER_H

#include <vector>
#include <string>

#include "SDL.h"
#include "sprite.hpp"

class SpriteBuilder
{
private:
    Sprite* m_sprite;

public:
    SpriteBuilder(SDL_Texture* texture, GridSize sheetSize);
    
    SpriteBuilder& withScale(Scale scale);

    SpriteBuilder& enableBoundingBox(bool enabled = true);

    SpriteBuilder& setFrameSizes(const std::unordered_map<int, Size>& sizes);

    SpriteBuilder& setUniformFrameSize(const Size& size);

    SpriteBuilder& setFrameDurations(const std::unordered_map<int, int>& durations);

    SpriteBuilder& setUniformFrameDuration(int duration);

    SpriteBuilder& addAnimation(const std::string& name, const std::vector<int>& frameIndices);
    
    Sprite* build();
};

#endif