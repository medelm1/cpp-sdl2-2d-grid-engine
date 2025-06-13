#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

#include <SDL.h>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <string>

#include "frame.hpp"
#include "math/Coordinate.hpp"
#include "grid/GridSize.hpp"
#include "graphics/sprite/Animation.hpp"

class AnimationController
{
private:
    std::vector<Animation*> m_animations;

    std::unordered_map<int, Frame*> m_frames;

    Frame* m_activeFrame;
    std::string m_activeAnimationName;

    int m_activeFrameStartTime;

private:
    bool isFrameExists(Frame* frame) const;

    Animation* getAnimationByName(const std::string& name) const;
    Animation* getPlayingAnimation();
    Animation* getPausedAnimation();
    
    void stopAllAnimations();

public:
    AnimationController(GridSize gridSize);
    ~AnimationController();

    Frame* getFrame(int frameIndex);

    Frame* getCurrentFrame();

    std::unordered_map<int, Frame*> getFrames();

    void addAnimation(const std::string& name, const std::vector<Frame*>& frames);

    void play(const std::string& animationName);
    void pause();
    void resume();

    void updateCurrentAnimation();
};

#endif