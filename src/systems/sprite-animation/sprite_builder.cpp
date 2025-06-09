#include "sprite_builder.hpp"

SpriteBuilder::SpriteBuilder(SDL_Texture* texture, GridSize sheetSize)
    :
    m_sprite(new Sprite(texture, sheetSize, Scale{1, 1}, false))
{

}
    
SpriteBuilder& SpriteBuilder::withScale(Scale scale)
{
    m_sprite->setScale(scale);
    return *this;
}

SpriteBuilder& SpriteBuilder::enableBoundingBox(bool enabled)
{
    m_sprite->setBoundingBoxEnabled(enabled);
    return *this;
}

SpriteBuilder& SpriteBuilder::setFrameSizes(const std::unordered_map<int, Size>& sizes)
{
    for (auto [index, size] : sizes)
    {
        Frame* frame = m_sprite->getAnimationController()->getFrame(index);
        
        if (frame)
        {
            frame->setSize(size);
        }
    }
    return *this;
}

SpriteBuilder& SpriteBuilder::setUniformFrameSize(const Size& size)
{
    for (auto [_, frame] : m_sprite->getAnimationController()->getFrames())
    {
        if (frame)
        {
            frame->setSize(size);
        }
    }
    return *this;
}

SpriteBuilder& SpriteBuilder::setFrameDurations(const std::unordered_map<int, int>& durations)
{
    for (auto [index, duration] : durations)
    {
        Frame* frame = m_sprite->getAnimationController()->getFrame(index);

        if (frame)
        {
            frame->setDuration(duration);
        }
    }
    return *this;
}

SpriteBuilder& SpriteBuilder::setUniformFrameDuration(int duration)
{
    for (auto [_, frame] : m_sprite->getAnimationController()->getFrames())
    {
        if (frame)
        {
            frame->setDuration(duration);
        }
    }
    return *this;
}

SpriteBuilder& SpriteBuilder::addAnimation(const std::string& name, const std::vector<int>& frameIndices)
{
    std::vector<Frame*> frames;

    for (int index : frameIndices)
    {
        frames.push_back(m_sprite->getAnimationController()->getFrame(index));
    }
    m_sprite->getAnimationController()->addAnimation(name, frames);
    
    return *this;
}

Sprite* SpriteBuilder::build()
{
    return m_sprite;
}