#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <string>
#include <vector>
#include <algorithm>

#include "frame.hpp"

class Animation
{
private:
    std::string m_name;
    std::vector<Frame*> m_frames;

    bool m_isPlaying;

    Frame* m_currentFrame;
    int m_currentFrameStartTime;
    

public:
    Animation(const std::string& name, const std::vector<Frame*>& frames);
    ~Animation();

    std::string getName() const;
    void setName(const std::string& name);

    void start();
    void reset();
    void update();

    bool isPlaying() const;
    bool isEmpty() const;

    Frame* getCurrentFrame() const;
};


#endif