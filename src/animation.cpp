#include "animation.hpp"

Animation::Animation(const std::string& name, const std::vector<Frame*>& frames)
    :
    m_name(name),
    m_frames({}),
    m_isPlaying(false),
    m_isPaused(false),
    m_currentFrame(nullptr),
    m_currentFrameStartTime(-1)
{
    for (Frame* frame : frames)
    {
        if (frame)
        {
            m_frames.push_back(frame);
        }
    }
}

Animation::~Animation()
{
    m_frames.clear();
}

std::string Animation::getName() const
{
    return m_name;
}

void Animation::setName(const std::string& name)
{
    m_name = name;
}

void Animation::reset()
{
    m_isPlaying = false;
    m_isPaused = false;
    m_currentFrameStartTime = -1;
    m_currentFrame = nullptr;
}

void Animation::start()
{
    reset();

    if (!isEmpty())
    {
        m_currentFrame = m_frames.at(0);
        m_currentFrameStartTime = SDL_GetTicks();
        m_isPlaying = true;
    }
}

void Animation::pause()
{
    m_isPaused = true;
}

void Animation::resume()
{
    m_isPaused = false;
}

bool Animation::isPlaying() const
{
    return m_isPlaying;
}

bool Animation::isPaused() const
{
    return m_isPaused;
}

bool Animation::isEmpty() const
{
    return m_frames.empty();
}

void Animation::update()
{
    if (!m_isPlaying || m_frames.empty() || !m_currentFrame) return;

    Uint32 now = SDL_GetTicks();
    Uint32 elapsedTime = now - m_currentFrameStartTime;

    if (elapsedTime >= m_currentFrame->getDuration() && !m_isPaused)
    {
        // Advance to next frame in cycle
        auto it = std::find(m_frames.begin(), m_frames.end(), m_currentFrame);
    
        if (it != m_frames.end())
        {
            ++it;
            if (it == m_frames.end())
            {
                it = m_frames.begin();
            }

            m_currentFrame = *it;
            m_currentFrameStartTime = now;
        } 
    }
}

Frame* Animation::getCurrentFrame() const
{
    return m_currentFrame;
}