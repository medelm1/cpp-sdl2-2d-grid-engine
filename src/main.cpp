#include "./core/game.hpp"

int main(int argc, char* argv[])
{
    if (Game::getInstance().init())
    {
        Game::getInstance().run();
    }

    return 0;
}