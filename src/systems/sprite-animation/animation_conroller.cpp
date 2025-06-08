#include "animation_controller.hpp"

AnimationController::AnimationController(GridSize gridSize)
    :
    m_gridSize(gridSize)
{
    init();

    m_activeFrame = m_frames[0];
}

AnimationController::~AnimationController()
{
    for (auto [_, frame] : m_frames)
    {
        delete frame;
    }
    m_frames.clear();
}

void AnimationController::init()
{
    int frameIndex = 0;

    for (int row = 0; row < m_gridSize.getRows(); row++)
    {
        for (int col = 0; col < m_gridSize.getCols(); col++)
        {
            m_frames[frameIndex] = new Frame{Coordinate{col, row}};

            frameIndex++;
        }
    }
}

Frame* AnimationController::getFrame(int frameIndex)
{
    if (m_frames.find(frameIndex) != m_frames.end())
    {
        return m_frames[frameIndex];
    }

    return nullptr;
}

Frame* AnimationController::getActiveFrame() const
{
    return m_activeFrame;
}