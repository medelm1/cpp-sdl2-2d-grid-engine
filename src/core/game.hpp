#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "interfaces/game_interface.hpp"
#include "input_handler.hpp"
#include "managers/audio_manager.hpp"

class Game : public IGame
{
private:
    static Game* instance;
    const int FPS = 60;
    const int DELAY_TIME = 1000.0f / FPS;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

private:
    Game();
    void update();
    void render();
    void clean();

    void initManagers();
    void loadAssets();

public:
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    static Game& getInstance();

    bool init();
    void run();
    void quit();
};

#endif