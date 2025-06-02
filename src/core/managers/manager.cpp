#include "manager.hpp"

Manager::Manager()
    :
    gameCtx(nullptr),
    initialized(false)
{

}

Manager::~Manager()
{
    delete gameCtx;
    gameCtx = nullptr;
    initialized = false;
}

void Manager::init(IGame* gameContext)
{
    gameCtx = gameContext;

    if (gameCtx != nullptr)
    {
        initialized = true;
    }
}