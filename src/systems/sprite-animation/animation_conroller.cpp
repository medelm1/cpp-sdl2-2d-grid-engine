#include "animation_controller.hpp"

AnimationController::AnimationController(GridSize gridSize)
{
    // Allocate sprite sheet frames
    int frameIndex = 0;

    for (int row = 0; row < gridSize.getRows(); row++)
    {
        for (int col = 0; col < gridSize.getCols(); col++)
        {
            m_frames[frameIndex] = new Frame{Coordinate{col, row}};

            frameIndex++;
        }
    }
}

AnimationController::~AnimationController()
{
    for (auto [_, frame] : m_frames)
    {
        delete frame;
    }
    m_frames.clear();
}

Frame* AnimationController::getFrame(int frameIndex)
{
    if (m_frames.find(frameIndex) != m_frames.end())
    {
        return m_frames[frameIndex];
    }

    return nullptr;
}

Frame* AnimationController::getCurrentFrame()
{
    Animation* animation = getPlayingAnimation();

    if (animation)
    {
        Frame* frame = animation->getCurrentFrame();

        if (frame)
        {
            return frame;
        }
    }

    return nullptr;
}

bool AnimationController::isFrameExists(Frame* frame) const
{
    for (const auto& [index, mappedFrame] : m_frames)
    {
        if (mappedFrame == frame)
        {
            return true;
        }
    }
    return false;
}

void AnimationController::addAnimation(const std::string& name, const std::vector<Frame*>& frames)
{
    for (const auto& animation : m_animations)
    {
        if (animation->getName() == name)
        {
            throw std::runtime_error("[AnimationController] Error: Animation name '" + name + "' already exists.");
        }
    }

    std::vector<Frame*> animationFrames;
    for (Frame* frame : frames)
    {
        if (!frame || !isFrameExists(frame))
        {
            std::ostringstream oss;
            oss << "[AnimationController] Error: Frame pointer not found: " << static_cast<const void*>(frame);
            throw std::runtime_error(oss.str());
        }
        animationFrames.push_back(frame);
    }

    m_animations.push_back(new Animation(name, animationFrames));
}

Animation* AnimationController::getAnimationByName(const std::string& name) const
{
    for (Animation* animation : m_animations)
    {
        if (animation->getName() == name)
        {
            return animation;
        }
    }

    return nullptr;
}

Animation* AnimationController::getPlayingAnimation()
{
    for (Animation* animation : m_animations)
    {
        if (animation->isPlaying())
        {
            return animation;
        }
    }

    return nullptr;
}
    
void AnimationController::stopAllAnimations()
{
    for (Animation* animation : m_animations)
    {
        animation->reset();
    }
}

void AnimationController::playAnimation(const std::string& name)
{
    Animation* animation = getAnimationByName(name);

    if (animation)
    {
        stopAllAnimations();
        animation->start();
    }
    else
    {
        std::ostringstream oss;
        oss << "[AnimationController] Error: Animation not found: " << name;
        throw std::runtime_error(oss.str());
    }
}

void AnimationController::updateCurrentAnimation()
{
    Animation* animation = getPlayingAnimation();

    if (animation)
    {
        animation->update();
    }
}