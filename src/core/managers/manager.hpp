#ifndef MANAGER_H
#define MANAGER_H

#include "../interfaces/game_interface.hpp"

class Manager
{
protected:
    IGame* gameCtx;
    bool initialized;

public:
    Manager();
    ~Manager();

    void init(IGame* gameContext);
};

#endif