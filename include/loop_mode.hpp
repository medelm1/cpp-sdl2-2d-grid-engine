#ifndef LOOP_MODE_H
#define LOOP_MODE_H

enum class LoopMode : int 
{
    PLAY_ONCE = 0,      // Play sound once, no repeats
    REPEAT_ONCE = 1,    // Play twice total (once + 1 repeat)
    REPEAT_TWICE = 2,   // Play three times total
    INFINITE = -1       // Loop forever
};

#endif