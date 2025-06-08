#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

#include "frame.hpp"
#include "../common/coordinate.hpp"
#include "../common/grid_size.hpp"

class AnimationController
{
private:
    // std::unordered_map<std::string, std::vector<Frame*>> m_animations;

    std::unordered_map<int, Frame*> m_frames;

    Frame* m_activeFrame;

    GridSize m_gridSize;

private:
    void init();

public:
    AnimationController(GridSize gridSize);
    ~AnimationController();

    Frame* getFrame(int frameIndex);

    Frame* getActiveFrame() const;
};

#endif